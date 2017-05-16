import telebot
from telebot import types
import config
import redis
import texts

#initializes bot with its token
bot = telebot.TeleBot(config.token)

#creates an instance of local database client
database = redis.StrictRedis(host='localhost', port=6379, db=0)


@bot.message_handler(commands=['start'])
def handle_start(message):

    bot.send_message(message.chat.id, "Hello, {name}!\n".format(name=message.from_user.first_name) +
                                      "For more info, feel free to use /help command")

    #adds a user's id to the database if it's there yet
    if database.sismember("users", message.from_user.id) == 0:
        database.sadd("users", message.from_user.id)
        database.save()


@bot.message_handler(commands=['help'])
def handle_help(message):

    bot.send_message(message.chat.id, texts.help_message)


@bot.message_handler(commands=['test'])
def handle_test(message):

    #shaping custom inline keyboard
    inline_markup = types.InlineKeyboardMarkup()
    buttn1 = types.InlineKeyboardButton("A", callback_data="A")
    buttn2 = types.InlineKeyboardButton("B", callback_data="B")
    buttn3 = types.InlineKeyboardButton("C", callback_data="C")
    inline_markup.add(buttn1, buttn2, buttn3)

    text = "Before you start specify the level of English you want to prove."
    bot.send_message(message.chat.id, text, reply_markup=inline_markup)


@bot.message_handler(commands=['stop'])
def handle_stop(message):

    #erases question and current score info from database if testing is suspended
    database.delete("{user_id}.question".format(user_id=message.from_user.id))
    database.delete("{user_id}.score".format(user_id=message.from_user.id))
    database.save()

    bot.send_message(message.chat.id, "The testing is stopped.", reply_markup=types.ReplyKeyboardRemove(selective=False))


@bot.message_handler(commands=['previous'])
def handle_previous(message):

    #if there is no info about passed tests
    if len(database.hgetall(message.from_user.id)) == 0:
        bot.send_message(message.chat.id, "You've not passed a test yet.")

    #gets all not-empty fields containing previous results and forms a string to send
    levels = ["A", "B", "C"]
    score = ""
    for level in levels:
        result = database.hget("{user_id}".format(user_id=message.from_user.id), level)
        if result is not None:
            score += level + " - " + "*{} correct answers.*".format(result.decode()) + '\n'

    bot.send_message(message.chat.id, score, parse_mode="Markdown")


@bot.message_handler(func=lambda message: True)
def handle_message(message):

    #if a user is answering a question
    if database.get("{user_id}.question".format(user_id=message.from_user.id)) is not None:

        question_number = int(database.get("{user_id}.question".format(user_id=message.from_user.id)))
        question_level = database.get("{user_id}.level".format(user_id=message.from_user.id)).decode()

        #check for correct answer
        answers = decode_answers(database.hgetall(config.answers.format(level=question_level, number=question_number)))
        if message.text not in answers:
            bot.send_message(message.chat.id, "Wrong input. Once more, please.")
            return

        #saves user's answers
        user_answers = "{user_id}.answers".format(user_id=message.from_user.id)
        database.hset(user_answers, question_level + str(question_number), message.text)

        correct_answer_key = config.correct_answer.format(level=question_level, number=question_number)
        correct_answer = database.get(correct_answer_key).decode()
        if message.text == correct_answer:
            database.incr("{user_id}.score".format(user_id=message.from_user.id))

        #getting next question's number
        question_number += 1
        if question_number <= 20:
            send_question(message.chat.id, question_level, question_number)
            database.incr("{user_id}.question".format(user_id=message.from_user.id))
        #if the end of the test
        else:
            #getting final score
            score = int(database.get("{user_id}.score".format(user_id=message.from_user.id)))
            percentage = score * 100 / 20

            #sending result
            deduction = "You are *{}{}*.".format(question_level, 1 if percentage < 50 else 2)
            text = texts.result.format(score, percentage, deduction)
            keyboard = types.ReplyKeyboardRemove(selective=False)
            bot.send_message(message.chat.id, text, reply_markup=keyboard, parse_mode="Markdown")

            #saving result
            database.hset("{user_id}".format(user_id=message.from_user.id), question_level, score)

            #suggesting answers
            inline_markup = types.InlineKeyboardMarkup()
            callback_data = "answers{}".format(question_level)
            get_answers = types.InlineKeyboardButton("Get correct answers", callback_data=callback_data)
            inline_markup.add(get_answers)
            bot.send_message(message.chat.id, texts.correct_answers, reply_markup=inline_markup)

            #erasing question and current score info as the test is over
            database.delete("{user_id}.question".format(user_id=message.from_user.id))
            database.delete("{user_id}.score".format(user_id=message.from_user.id))
    database.save()


@bot.callback_query_handler(func=lambda call: "answers" in call.data)
def get_answers_handler(call):

    #getting level
    level = call.data.strip("answers")

    i = 0
    text = ""
    while i < 20:
        i += 1
        correct = database.get(config.correct_answer.format(level=level, number=i))
        text += "{}. ".format(i) + database.hget(config.answers.format(level=level, number=i), correct).decode() + "\n"

    bot.send_message(call.message.chat.id, text)


@bot.callback_query_handler(func=lambda call: True)
def call_handler(call):

    #announcing test's start
    bot.send_message(call.message.chat.id, "Ok. Here we go!")

    #getting some helpful buffers on the go and sending the first question of the test (level)
    database.set("{user_id}.question".format(user_id=call.from_user.id), 1)
    database.set("{user_id}.level".format(user_id=call.from_user.id), call.data)
    database.set("{user_id}.score".format(user_id=call.from_user.id), 0)
    send_question(call.message.chat.id, call.data)
    database.save()


#sends question (level, number) to the chat
def send_question(chat_id, level, number=1):

    #gets answers for a question to send
    answers = database.hgetall(config.answers.format(level=level, number=number))

    answers_str = decode_answers(answers)

    #wording a message
    question = database.get(config.question.format(level=level, number=number)).decode()
    message_text = "{}. ".format(number) + question + "\n"
    for key in answers_str.keys():
        message_text += key + ". " + answers_str[key] + "\n"

    #shaping reply keyboard depending on the capacity of answers' list
    keyboard_markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    i = 0
    while i != len(answers_str):
        keyboard_markup.add(types.KeyboardButton("{}".format((i + 1))))
        i += 1

    bot.send_message(chat_id, message_text, reply_markup=keyboard_markup)


def decode_answers(answers):
    answers_str = {}
    for key in answers.keys():
        answers_str[key.decode()] = answers[key].decode()
    return answers_str


bot.polling(none_stop=True)
