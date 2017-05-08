#include "stdafx.h"
#include "projects.h"

//swaps two tasks without shifting the structure
void SwapTasks(Task *task1, Task *task2)
{
	float resources = task1->resources;
	task1->resources = task2->resources;
	task2->resources = resources;
	DateCheck buffer = task1->start;
	task1->start = task2->start;
	task2->start = buffer;
	buffer = task1->finish;
	task1->finish = task2->finish;
	task2->finish = buffer;
	People *buffer2 = task1->people;
	task1->people = task2->people;
	task2->people = buffer2;
	char name[nameLength], define[definition];
	strcpy_s(name, nameLength, task1->name);
	strcpy_s(task1->name, nameLength, task2->name);
	strcpy_s(task2->name, nameLength, name);
	strcpy_s(define, definition, task1->define);
	strcpy_s(task1->define, definition, task2->define);
	strcpy_s(task2->define, definition, define);
}
People::People()
{
	personnel = NULL;
}
People::~People()
{
	while (personnel != NULL)
	{
		Person *temporary = personnel;
		personnel = personnel->next;
		delete temporary;
	}
}
//"assigns" a person for a task
void People::Assign(char *name, char *surname)
{
	Person *seekEnd = personnel, *previous = NULL;
	while (seekEnd != NULL)								//seeks the end of the list
	{
		previous = seekEnd;
		seekEnd = seekEnd->next;
	}
	seekEnd = new Person;								//creates new team_member
	strncpy_s(seekEnd->name, name, nameLength);
	strncpy_s(seekEnd->surname, surname, surnameLength);
	seekEnd->previous = previous;
	seekEnd->next = NULL;
	if (personnel == NULL) personnel = seekEnd;
	if (previous != NULL)
	{
		previous->next = seekEnd;
	}
}
//displays the personnel
void People::Show()
{
	Person *show = personnel;
	while (show != NULL)
	{
		cout << show->name << " " << show->surname << endl;
		show = show->next;
	}
}
//"suspends" a person from a task
void People::Discharge(char *name)
{
	Person *discharge = SeekByName(name);
	if (discharge == NULL)
	{
		cout << "Element is not found.\n";
		return;
	}
	if (discharge->previous != NULL) discharge->previous->next = discharge->next;
	if (discharge->next != NULL) discharge->next->previous = discharge->previous;
	if (discharge == personnel) personnel = personnel->next;
	delete discharge;
}
//seeks by name
Person * People::SeekByName(char *name)
{
	Person *seek = personnel;
	if (seek == NULL) return NULL;
	while (seek != NULL && strcmp(seek->name, name))
	{
		seek = seek->next;
	}
	if (seek == NULL) return SeekBySurname(name);						//if not found seeks by surname
	return seek;
}
Person * People::SeekBySurname(char *surname)
{
	Person *seek = personnel;
	if (seek == NULL) return NULL;
	while (seek != NULL && strcmp(seek->surname, surname))
	{
		seek = seek->next;
	}
	return seek;
}

Project::Project()
{
	listOfTasks = NULL;
}
Project::~Project()
{
	while (listOfTasks != NULL)
	{
		Task *temporary = listOfTasks;
		listOfTasks = listOfTasks->next;
		delete temporary->people;
		delete temporary;
	}
}
void Project::AddTask(DateCheck *start, DateCheck *finish, char *name)
{
	Task *seekEnd = listOfTasks, *previous = NULL;
	if (start->Compare(finish) == 1)											//checks if start goes before finish
	{
		cout << "You can not start after you finish.\n";
		return;
	}
	while (seekEnd != NULL)								//seeks the end of the list
	{
		previous = seekEnd;
		if (!strcmp(name, seekEnd->name))							//doesn't add a task if there is another with the same name
		{
			cout << "A task with such name already exists.\n";
			return;
		}
		seekEnd = seekEnd->next;
	}
	seekEnd = new Task;								//creates new team_member
	seekEnd->start = *start;
	seekEnd->finish = *finish;
	strncpy_s(seekEnd->name, name, nameLength);
	seekEnd->people = new People();
	seekEnd->previous = previous;
	seekEnd->next = NULL;
	memset(seekEnd->define, 0, definition);
	seekEnd->resources = 0;
	if (listOfTasks == NULL) listOfTasks = seekEnd;
	if (previous != NULL)
	{
		previous->next = seekEnd;
	}
	cout << "A task is added.\n";
	Sort();
}
//searches a task in the list
Task * Project::Find(char *name)
{
	Task *search = listOfTasks;
	while (search != NULL && strcmp(name, search->name))
	{
		search = search->next;
	}
	return search;
}
void Project::DeleteTask(char *name)
{
	Task *found = Find(name);
	if (!found)
	{
		cout << "A task with such name doesn't exist.\n";
		return;
	}
	FILE *file;
	fopen_s(&file, "archive.txt", "a");
	SaveToFile(file);
	fclose(file);
	if (found->previous != NULL) found->previous->next = found->next;
	if (found->next != NULL) found->next->previous = found->previous;
	if (found == listOfTasks) listOfTasks = listOfTasks->next;
	delete found->people;
	delete found;
}
//displays the list
void Project::Show()
{
	Task *show = listOfTasks;
	while (show != NULL)
	{
		cout << show->name << endl;
		if (strlen(show->define)) cout << "Definition: " << show->define << endl;
		cout << "Start: " << (&(show->start))->Show();
		cout << endl;
		cout << "Finish: " << (&(show->finish))->Show();
		cout << endl;
		cout << "Money: " << show->resources << endl;
		cout << "People:\n";
		show->people->Show(); 
		show = show->next;
		cout << endl;
	}
}
void Project::Show(Task *show)
{
	cout << show->name << endl;
	if (strlen(show->define)) cout << "Definition: " << show->define << endl;
	cout << "Start: " << (&(show->start))->Show();
	cout << endl;
	cout << "Finish: " << (&(show->finish))->Show();
	cout << endl;
	cout << "Money: " << show->resources << endl;
	cout << "People:\n";
	show->people->Show();
	show = show->next;
	cout << endl;
}
void Project::AllotMoney(Task *task, float resources)
{
	if (task != NULL) task->resources += resources;
}
void Project::AssignPeople(Task *task)
{
	if (task)
	{
		char choice;
		do
		{
			system("cls");
			cout << "You've got the following people assigned:\n";
			task->people->Show();
			char name[nameLength], surname[surnameLength];
			while (true)
			{
				cout << "Enter a name of a person to assign:\n";
				fgets(name, nameLength, stdin);
				fseek(stdin, 0, SEEK_END);
				name[strlen(name) - 1] = '\0';
				if (!strcmp(name, "/")) cout << "You can not give a person such a name. Sorry.\n";
				else break;
			}
			cout << "Enter a surname of a person to assign:\n";
			fgets(surname, surnameLength + 1, stdin);
			fseek(stdin, 0, SEEK_END);
			surname[strlen(surname) - 1] = '\0';
			task->people->Assign(name, surname);
			do
			{
				cout << "Do you want to assign one more person?(Enter - yes / Esc - no)\n";
				choice = _getche();
			} while (choice != 13 && choice != 27);
		} while (choice == 13);
	}
}
void Project::Dismiss(Task *task)
{
	if (task)
	{
		char choice;
		do
		{
			system("cls");
			cout << "You've got the following people assigned:\n";
			task->people->Show();
			char name[nameLength];
			cout << "Enter the name of who you want to suspend:\n";
			fgets(name, nameLength, stdin);
			fseek(stdin, 0, SEEK_END);
			name[strlen(name) - 1] = '\0';
			task->people->Discharge(name);
			do
			{
				cout << "Do you want to suspend one more person?(Enter - yes / Esc - no)\n";
				choice = _getche();
			} while (choice != 13 && choice != 27);
		} while (choice == 13);
	}
}
void Project::AddDefinition(Task *task)
{
	system("cls");
	if (task)
	{
		cout << "Enter the explicit description of the task:\n";
		fgets(task->define, definition, stdin);
		fseek(stdin, 0, SEEK_END);
		task->define[strlen(task->define) - 1] = '\0';
	}
}
//sorts the list of tasks increasingly by the starting date
void Project::Sort()
{
	Task *offset = listOfTasks;
	if (!offset) return;
	while (offset->next)
	{
		offset = offset->next;
	}
	while (offset != listOfTasks)
	{
		Task *check = listOfTasks;
		while (check != offset)
		{
			if ((check->start).Compare(&(check->next->start)) == 1)
			{
				SwapTasks(check, check->next);
			}
			check = check->next;
		}
		offset = offset->previous;
	}
}
//calculates projects resources
float Project::GetResources()
{
	Task *head = listOfTasks;
	float sum = 0;
	while (head != NULL)
	{
		sum += head->resources;
		head = head->next;
	}
	return sum;
}
//alters the starting date
void Project::ChangeStart(DateCheck *newdate, char *name)
{
	Task *found = Find(name);
	if (found && newdate->Compare(&(found->finish)) != 1)
	{
		found->start = *newdate;
	}
}
//alters the final date
void Project::ChangeFinish(DateCheck *newdate, char *name)
{
	Task *found = Find(name);
	if (found && newdate->Compare(&(found->start)) != -1)
	{
		found->finish = *newdate;
	}
}
//alters the name of a task
void Project::ChangeName(char *name, char *newname)
{
	Task *found = Find(name);
	if (found) strcpy_s(name, nameLength, newname);
}
Projects::Projects()
{
	listOfProjects = NULL;
}
Projects::~Projects()
{
	while (listOfProjects != NULL)
	{
		ProjectStruct *temporary = listOfProjects;
		listOfProjects = listOfProjects->next;
		delete temporary->tasks;
		delete temporary;
	}
}
//add project
void Projects::Add(char *name)
{
	ProjectStruct *seekEnd = listOfProjects, *previous = NULL;
	while (seekEnd != NULL)								//seeks the end of the list
	{
		previous = seekEnd;
		if (!strcmp(name, seekEnd->name))							//doesn't add a task if there is another with the same name
		{
			cout << "A project with such name already exists.\n";
			return;
		}
		seekEnd = seekEnd->next;
	}
	seekEnd = new ProjectStruct;
	strncpy_s(seekEnd->name, name, nameLength);
	seekEnd->tasks = new Project();
	seekEnd->previous = previous;
	seekEnd->next = NULL;
	if (listOfProjects == NULL) listOfProjects = seekEnd;
	if (previous != NULL)
	{
		previous->next = seekEnd;
	}
	cout << "A project is added.\n";
}
void Projects::Delete(char *name)
{
	ProjectStruct *found = Find(name);
	if (!found)
	{
		cout << "A project with such name doesn't exist.\n";
		return;
	}
	SaveToFile();
	if (found->previous != NULL) found->previous->next = found->next;
	if (found->next != NULL) found->next->previous = found->previous;
	if (found == listOfProjects) listOfProjects = listOfProjects->next;
	delete found->tasks;
	delete found;
}
ProjectStruct * Projects::Find(char *name)
{
	ProjectStruct *search = listOfProjects;
	while (search != NULL && strcmp(name, search->name))
	{
		search = search->next;
	}
	return search;
}
void Projects::Change(char *oldname, char *newname)
{
	ProjectStruct *found = Find(oldname);
	if (!found)
	{
		cout << "Project is not found.\n";
		return;
	}
	strncpy_s(found->name, newname, nameLength);
}
void Projects::Show()
{
	cout << endl << "Your projects:\n";
	ProjectStruct *temporary = listOfProjects;
	while (temporary)
	{
		cout << temporary->name << endl;
		temporary = temporary->next;
	}
}
void Projects::Show(ProjectStruct *project)
{
	if (!project)
	{
		cout << "Project is not found.\n";
		return;
	}
	cout << project->name << endl << endl;
	project->tasks->Show();
}
void Project::GetTerm()
{
	Task *last = listOfTasks;
	if (!last)
	{
		cout << "No tasks in the project.\n";
		return;
	}
	while (last->next)
	{
		last = last->next;
	}
	cout << "The term for the project is " <<
	listOfTasks->start.Difference(&(last->finish)) << " days.\n";
	cout << "Start: " << listOfTasks->start.Show();
	cout << endl;
	cout << "Finish: " << FindLast()->finish.Show();
	cout << endl;
}
Task * Project::FindLast()
{
	DateCheck *max = &(listOfTasks->finish);
	Task *temporary = listOfTasks, *maximum = listOfTasks;
	while (temporary)
	{
		if (temporary->finish.Compare(max) == 1)
		{
			max = &(temporary->finish);
			maximum = temporary;
		}
		temporary = temporary->next;
	}
	return maximum;
}
void Project::GetReserve(DateCheck *now, char *taskname)
{
	Task *task = Find(taskname);
	if (task == NULL) 
	{
		cout << "Task is not found.\n";
		return;
	}
	if (now->Compare(&(task->finish)) == 1)
	{
		cout << "You have no time left for this task.\n";
		return;
	}
	cout << "You have " << now->Difference(&(task->finish)) << " days left.\n";
}
void Project::GetParallel(char *name)
{
	Task *task = Find(name);
	if (!task)
	{
		cout << "Task is not found.\n";
		return;
	}
	Task *check = listOfTasks;
	cout << "Tasks that are parallel to " << name << endl;
	while (check != task)
	{
		if (check->finish.Compare(&(task->start)) == 1) cout << check->name << endl;
		check = check->next;
	}
	check = check->next;
	while (check)
	{
		if (check->start.Compare(&(task->finish)) == -1) cout << check->name << endl;
		else return;
		check = check->next;
	}
}
void Project::UltimateWay()
{
	cout << "Here is how your tasks follow each other:\n";
	Task *show = listOfTasks;
	while (show != NULL)
	{
		cout << show->name << endl;
		show = show->next;
		cout << endl;
	}
}
void Projects::SaveToFile()
{
	FILE *file;
	fopen_s(&file, "databases.txt", "w");
	ProjectStruct *run = listOfProjects;
	while (run)
	{
		fputs("project", file);
		fputc('\n', file);
		fputs(run->name, file);
		fputc('\n', file);
		run->tasks->SaveToFile(file);
		run = run->next;
	}
	fclose(file);
}
void Project::SaveToFile(FILE *file)
{
	Task *run = listOfTasks;
	while (run)
	{
		fputs("task", file);
		fputc('\n', file);
		fputs(run->name, file);
		fputc('\n', file);
		fputs(run->start.Show(), file);
		fputc('\n', file);
		fputs(run->finish.Show(), file);
		fputc('\n', file);
		fputs(run->define, file);
		fputc('\n', file);
		char resources[20];
		sprintf_s(resources, "%f", run->resources);
		fputs(resources, file);
		fputc('\n', file);
		run->people->SaveToFile(file);
		run = run->next;
	}
}
void People::SaveToFile(FILE *file)
{
	fputc('/', file);
	fputc('\n', file);
	Person *run = personnel;
	while (run)
	{
		fputs(run->name, file);
		fputc('\n', file);
		fputs(run->surname, file);
		fputc('\n', file);
		run = run->next;
	}
	fputc('/', file);
	fputc('\n', file);
}
void Projects::ReadFromFile()
{
	FILE *file;
	fopen_s(&file, "databases.txt", "r");
	char *buffer = new char[definition];
	char projectName[nameLength], taskName[nameLength];
	DateCheck *startDate = new DateCheck(), *finishDate = new DateCheck();
	char start[11], finish[11];
	if (!file) return;
	if (feof(file))
	{
		cout << "File is empty.\n";
		return;
	}
	fgets(buffer, definition, file);
	buffer[strlen(buffer) - 1] = '\0';  //reads "project"

	while (!feof(file))
	{
		fgets(buffer, definition, file);			//reads project's name
		buffer[strlen(buffer) - 1] = '\0';
		strcpy_s(projectName, nameLength, buffer);
		Add(projectName);    //adds project


		if (feof(file)) break;		//it could be the end

		fgets(buffer, definition, file);
		buffer[strlen(buffer) - 1] = '\0';		//reads "task" or "project"


		if (!strcmp(buffer, "project")) break;		//if "project" starts again
		
		
		Project *project = Find(projectName)->tasks;
		while (strcmp(buffer, "project") && !feof(file))		//while new project or the end of file
		{
			fgets(buffer, definition, file);
			buffer[strlen(buffer) - 1] = '\0';
			strcpy_s(taskName, nameLength, buffer);		//reads task's name


			fgets(buffer, definition, file);
			buffer[strlen(buffer) - 1] = '\0';
			strcpy_s(start, 11, buffer);
			fgets(buffer, definition, file);
			buffer[strlen(buffer) - 1] = '\0';
			strcpy_s(finish, 11, buffer);				//reads dates


			startDate->Initialize(start);
			finishDate->Initialize(finish);				//initializes dates


			project->AddTask(startDate, finishDate, taskName);			//adds task


			Task *task = project->Find(taskName); 
			fgets(buffer, definition, file);
			buffer[strlen(buffer) - 1] = '\0';					//writes tasks's definition
			strncpy_s(task->define, buffer, definition);


			fgets(buffer, 100, file);
			buffer[strlen(buffer) - 1] = '\0';			//writes resources
			float money = (float)atof(buffer);
			task->resources = money;



			fgets(buffer, definition, file);
			buffer[strlen(buffer) - 1] = '\0';		//reads "/"
			bool end = false;
			while (!end)			//till meets "/"
			{
				fgets(buffer, definition, file);		//reads till "/"
				buffer[strlen(buffer) - 1] = '\0';
				char name[nameLength];
				strncpy_s(name, buffer, definition);
				if (strcmp(buffer, "/") != 0)		//if not "/"
				{
					fgets(buffer, definition, file);
					buffer[strlen(buffer) - 1] = '\0';		//assigns a person
					task->people->Assign(name, buffer);
				}
				else end = true;
			}
			if (!feof(file))
			{
				fgets(buffer, definition, file);			//if the end of file
				buffer[strlen(buffer) - 1] = '\0';
			}
		}

	}
	delete startDate;
	delete finishDate;
	delete buffer;
	fclose(file);
}