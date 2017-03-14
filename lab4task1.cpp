// lab4task1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

int check(char *s)
{
	for (int i = 0; i < (int)strlen(s); i++)
	{
		if (s[i] < '0' || s[i] > '9') return -1;
	}
	return atoi(s);
}

void get_input(int *a,const char *s)
{
	bool cond = true;
	while (cond)
	{
		cout << s;
		char substr[100];
		cin >> substr;
		*a = check(substr);
		if (*a > 0) cond = false;
	}
}

void get_array(char **text, int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << "Enter your " << i + 1 << " string(max length - 30 characters, \'~\' - to stop input):\n";
		text[i] = (char*)malloc(sizeof(char) * 30);
		int count = 0;
		while (count < 29)
		{
			text[i][count] = _getche();
			if (text[i][count] == '~')
			{
				text[i][count] = '\0';
				count = 30;
				cout << endl;
			}
			count++;
		}
		if (count == 29)
		{
			text[i][count] = '\0';
			cout << '\n';
		}
	}
}

void show_first_letters(char **text, int N)
{
	cout << "The first mentions of your text letters: ";
	int alphabet[26] = { 0 };
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; text[i][j] != '\0'; j++)
		{
			if (text[i][j] <= 'z' && text[i][j] >= 'a')
			{
				if (++alphabet[text[i][j] - 'a'] == 1) cout << text[i][j];
			}
			else if (text[i][j] <= 'Z' && text[i][j] >= 'A')
			{
				if (++alphabet[text[i][j] - 'A'] == 1) cout << text[i][j];
			}
		}
		int count = 0;
		for (int j = 0; j < 26; j++)
		{
			if (alphabet[j] != 0) count++;
		}
		if (count == 26) i = N;
	}
	cout << endl;
}

void display_words(char **text, int N)
{
	cout << "Your looped words:\n";
	int begin, end;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; text[i][j] != '\0'; j++)
		{
			if (j == 0 || (text[i][j] != ' ' && text[i][j - 1] == ' '))
			{
				begin = j;
			}
			if (text[i][j + 1] == '\0' || (text[i][j + 1] == ' ' && text[i][j] != ' '))
			{
				end = j;
				if (text[i][begin] == text[i][end])
				{
					for (int k = begin; k < end + 1; k++) cout << text[i][k];
					cout << endl;
				}
			}
		}
	}
}

int main()
{
	int repeat;
	do
	{
		system("cls");
		int N;
		get_input(&N, "Please, set the number of strings in your text:\n");
		char **text;
		text = (char**)malloc(sizeof(char*) * N);

		get_array(text, N);

		show_first_letters(text, N);

		display_words(text, N);

		get_input(&repeat, "Do you want to run once more? (Yes - 1, any other number - no)\n");
	} while (repeat == 1);
    return 0;
}

