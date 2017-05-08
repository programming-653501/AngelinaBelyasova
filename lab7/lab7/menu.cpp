#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include "check.h"
#include "menu.h"
#include "projects.h"
using namespace std;

#define Lchoice 4

//user's reference
void Help()
{
	system("cls");
	cout << "Hello! Welcome to BProject!\n";
	cout << "It is the soft that is designed to simplify your life\
 and help you schedule your projects in a more perceivable and demonstrative way.\n\
It offers an easy-to-use interface. You can travel over menu and work with your projects\
 or create new ones.\nEvery discarded information is being preserved in the archive that you can then look in.\n\
After altering any info all the changes are recorded.\n\
Be clever and use the program with accordance to its purpose.\n\
Best of luck!";
	cout << endl;
	system("pause");
}
//function that showcases the inside of the archive
void Archive()
{
	system("cls");
	FILE *archive;
	fopen_s(&archive, "archive.txt", "r");
	if (!archive)
	{
		cout << "File doesn't exist yet.\n";
		return;
	}
	fseek(archive, 0, SEEK_END);
	int size = ftell(archive);
	rewind(archive);
	char *content = new char[size + 1];
	memset(content, 0, size + 1);
	fread(content, size, 1, archive);
	cout << content;
	cout << endl;
	fclose(archive);
	system("pause");
}

void AddProjectMenu(Projects *projectGroup)
{
	system("cls");
	while (true)
	{
		cout << "Main menu -> Add Project\n";
		cout << "Choose:\n";
		cout << "1.Add Project\n";
		cout << "2.Return to main menu\n";
		char choice[Lchoice];
		cout << "Enter your choice:\n";
		fgets(choice, Lchoice, stdin);
		fseek(stdin, 0, SEEK_END);
		choice[strlen(choice) - 1] = '\0';
		if (checkInt(choice))
		{
			switch (atoi(choice))
			{
			case 1: AddProject(projectGroup); break;
			case 2: return;
			default: cout << "No such option.\n"; system("pause"); break;
			}
		}
		else
		{
			cout << "Wrong input!!!\n";
			system("pause");
		}
		system("cls");
	}
}

//the first menu you face in the application
void mainMenu()
{
	Projects *projects = new Projects();
	projects->ReadFromFile();
	while (true)
	{
		cout << "BProject Menu:\n";
		cout << "1.Add project\n";
		cout << "2.Work with existing projects\n";
		cout << "3.View the archive\n";
		cout << "4.Help\n";
		cout << "5.Exit\n";
		char choice[Lchoice];
		cout << "Enter your choice:\n";
		fgets(choice, Lchoice, stdin);
		fseek(stdin, 0, SEEK_END);
		choice[strlen(choice) - 1] = '\0';
		if (checkInt(choice))
		{
			switch (atoi(choice))
			{
			case 1: AddProjectMenu(projects); projects->SaveToFile(); break;
			case 2: WorkWithExistingMenu(projects); projects->SaveToFile();break;
			case 3: Archive(); break;
			case 4: Help(); break;
			case 5: projects->SaveToFile(); delete projects; return;
			default: cout << "No such option.\n"; system("pause"); break;
			}
		}
		else
		{
			cout << "Wrong input!!!\n";
			system("pause");
		}
		system("cls");
	}
}

void AddProject(Projects *project)
{
	system("cls");
	cout << "Enter your project's name:\n";
	char name[nameLength];
	fgets(name, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	name[strlen(name) - 1] = '\0';
	project->Add(name);
	system("pause");
	system("cls");
	AddTaskMenu(project, name);
}
void AddTaskMenu(Projects *projects, char *name)
{
	while (true)
	{
		cout << "Add Task Menu\n";
		cout << "Choose:\n";
		cout << "1.Add Task\n";
		cout << "2.Return\n";
		char choice[Lchoice];
		cout << "Enter your choice:\n";
		fgets(choice, Lchoice, stdin);
		fseek(stdin, 0, SEEK_END);
		choice[strlen(choice) - 1] = '\0';
		if (checkInt(choice))
		{
			switch (atoi(choice))
			{
			case 1: AddTask(projects->Find(name)->tasks); break;
			case 2: return;
			default: cout << "No such option.\n"; system("pause"); break;
			}
		}
		else
		{
			cout << "Wrong input!!!\n";
			system("pause");
		}
		system("cls");
	}
}
void AddTask(Project *project)
{
	DateCheck *start = new DateCheck(), *finish = new DateCheck();
	while (true)
	{
		char day[] = "Enter the day of the start date:\n";
		int d = inputInt(day);
		char month[] = "Enter the month of the start date:\n";
		int m = inputInt(month);
		char year[] = "Enter the year of the start date:\n";
		int y = inputInt(year);
		start->Initialize(d, m, y);
		system("pause");
		if (start->IsInitialized()) break;
	}
	while (true)
	{
		char day[] = "Enter the day of the finish date:\n";
		int d = inputInt(day);
		char month[] = "Enter the month of the finish date:\n";
		int m = inputInt(month);
		char year[] = "Enter the year of the finish date:\n";
		int y = inputInt(year);
		finish->Initialize(d, m, y);
		system("pause");
		if (finish->IsInitialized()) break;
	}
	system("cls");
	cout << "Enter your task's name:\n";
	char name[nameLength];
	fgets(name, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	name[strlen(name) - 1] = '\0';
	project->AddTask(start, finish, name);
	Task *task = project->Find(name);
	if (task) SpecifyMenu(task, project);
	else
	{
		cout << "Addition attempt failed.\n";
		system("pause");
	}
	delete start;
	delete finish;
}
int inputInt(char *string)
{
	while (true)
	{
		system("cls");
		char input[9];
		cout << string;
		fgets(input, 9, stdin);
		fseek(stdin, 0, SEEK_END);
		input[strlen(input) - 1] = '\0';
		if (checkInt(input)) return atoi(input);
	}
}
void SpecifyMenu(Task *task, Project *project)
{
	system("cls");
	while (true)
	{
		cout << "Add Task -> Specify\n";
		cout << "Choose:\n";
		cout << "1.Add definition of a task\n";
		cout << "2.Allot money\n";
		cout << "3.Assign people\n";
		cout << "4.Go back\n";
		char choice[Lchoice];
		cout << "Enter your choice:\n";
		fgets(choice, Lchoice, stdin);
		fseek(stdin, 0, SEEK_END);
		choice[strlen(choice) - 1] = '\0';
		if (checkInt(choice))
		{
			switch (atoi(choice))
			{
			case 1: AddDefinition(task, project); break;
			case 2: AllotMoney(task, project); break;
			case 3: AssignPeople(task, project); break;
			case 4: return;
			default: cout << "No such option.\n"; system("pause"); break;
			}
		}
		else
		{
			cout << "Wrong input!!!\n";
			system("pause");
		}
		system("cls");
	}
}
void AllotMoney(Task *task, Project *project)
{
	system("cls");
	while (true)
	{
		char money[15];
		cout << "Enter money you want to contribute(+)/withdraw(-) for a task in BYN:\n";
		fgets(money, 15, stdin);
		fseek(stdin, 0, SEEK_END);
		money[strlen(money) - 1] = '\0';
		if (CheckForFloat(money))
		{
			project->AllotMoney(task, (float)atof(money));
			return;
		}
		system("cls");
	}
}

void AddDefinition(Task *task, Project *project)
{
	project->AddDefinition(task);
}
void AssignPeople(Task *task, Project *project)
{
	project->AssignPeople(task);
}
void WorkWithExistingMenu(Projects *projects)
{
	system("cls");
	while (true)
	{
		cout << "Main menu -> Work with existing projects menu";
		projects->Show();
		cout << "Choose:\n";
		cout << "1.View\n";
		cout << "2.Alter\n";
		cout << "3.Erase project\n";
		cout << "4.Get terms of a project\n";
		cout << "5.Get the ultimate way\n";
		cout << "6.Get time reserve\n";
		cout << "7.Get parallel tasks\n";
		cout << "8.Go back\n";
		char choice[Lchoice];
		cout << "Enter your choice:\n";
		fgets(choice, Lchoice, stdin);
		fseek(stdin, 0, SEEK_END);
		choice[strlen(choice) - 1] = '\0';
		if (checkInt(choice))
		{
			switch (atoi(choice))
			{
			case 1: View(projects); break;
			case 2: AlterMenu(projects); break;
			case 3: EraseProject(projects); break;
			case 4: GetTerms(projects); break;
			case 5: GetUltimateWay(projects); break;
			case 6: GetTimeReserveMenu(projects); break;
			case 7: GetParallelTasks(projects); break;
			case 8: return;
			default: cout << "No such option.\n"; system("pause"); break;
			}
		}
		else
		{
			cout << "Wrong input!!!\n";
			system("pause");
		}
		system("cls");
	}
}
void View(Projects *projects)
{
	system("cls");
	projects->Show();
	cout << "Enter the name of a project to view:\n";
	char choice[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	ProjectStruct *found = projects->Find(choice);
	if (!found)
	{
		cout << "A project with such name isn't found.\n";
		system("pause");
		return;
	}
	projects->Show(found);
	system("pause");
}
void EraseProject(Projects *projects)
{
	system("cls");
	projects->Show();
	cout << "Enter the name of a project to erase:\n";
	char choice[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	projects->Delete(choice);
	system("pause");
}
void GetTerms(Projects *projects)
{
	system("cls");
	projects->Show();
	cout << "Enter the name of a project to view terms of:\n";
	char choice[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	ProjectStruct *found = projects->Find(choice);
	if (!found)
	{
		cout << "A project with such name isn't found.\n";
		system("pause");
		return;
	}
	Project *project = found->tasks;
	project->GetTerm();
	system("pause");
}
void GetUltimateWay(Projects *projects)
{
	system("cls");
	projects->Show();
	cout << "Enter the name of a project to get ultimate way of:\n";
	char choice[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	ProjectStruct *found = projects->Find(choice);
	if (!found)
	{
		cout << "A project with such name isn't found.\n";
		system("pause");
		return;
	}
	Project *project = found->tasks;
	project->UltimateWay();
	system("pause");
}
void GetParallelTasks(Projects *projects)
{
	system("cls");
	projects->Show();
	cout << "Enter the name of a project to get parallel tasks of:\n";
	char choice[nameLength], task[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	ProjectStruct *found = projects->Find(choice);
	if (!found)
	{
		cout << "A project with such name isn't found.\n";
		system("pause");
		return;
	}
	Project *project = found->tasks;
	system("cls");
	project->UltimateWay();
	cout << "Enter the name of a task to get others that are parallel to it:\n";
	fgets(task, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	task[strlen(task) - 1] = '\0';
	cout << endl;
	project->GetParallel(task);
	system("pause");
}
void GetTimeReserveMenu(Projects *projects)
{
	system("cls");
	projects->Show();
	cout << "Enter the name of a project to get parallel tasks of:\n";
	char choice[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	ProjectStruct *found = projects->Find(choice);
	if (!found)
	{
		cout << "A project with such name isn't found.\n";
		system("pause");
		return;
	}
	DateCheck *now = new DateCheck();
	while (true)
	{
		system("cls");
		char day[] = "Enter the day of now:\n";
		int d = inputInt(day);
		char month[] = "Enter the month of now:\n";
		int m = inputInt(month);
		char year[] = "Enter the year of now:\n";
		int y = inputInt(year);
		now->Initialize(d, m, y);
		system("pause");
		if (now->IsInitialized()) break;
	}
	system("cls");
	while (true)
	{
		cout << "Main menu -> Work with existing projects menu -> Get Time Reserve Menu";
		projects->Show();
		cout << "Choose:\n";
		cout << "1.For a task\n";
		cout << "2.For the project\n";
		cout << "3.Return\n";
		char choice[Lchoice];
		cout << "Enter your choice:\n";
		fgets(choice, Lchoice, stdin);
		fseek(stdin, 0, SEEK_END);
		choice[strlen(choice) - 1] = '\0';
		if (checkInt(choice))
		{
			switch (atoi(choice))
			{
			case 1: GetTimeReserveForTask(found->tasks, now); break;
			case 2: found->tasks->GetReserve(now, found->tasks->FindLast()->name); system("pause"); break;
			case 3: return;
			default: cout << "No such option.\n"; system("pause"); break;
			}
		}
		else
		{
			cout << "Wrong input!!!\n";
			system("pause");
		}
		system("cls");
	}
}
void GetTimeReserveForTask(Project *project, DateCheck *now)
{
	system("cls");
	project->UltimateWay();
	cout << "Enter the name of a task to get reserve for:\n";
	char task[nameLength];
	fgets(task, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	task[strlen(task) - 1] = '\0';
	cout << endl;
	project->GetReserve(now, task);
	system("pause");
}
void AlterMenu(Projects* projects)
{
	system("cls");
	projects->Show();
	cout << "Enter the name of a project to alter:\n";
	char choice[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	ProjectStruct *found = projects->Find(choice);
	if (!found)
	{
		cout << "A project with such name isn't found.\n";
		system("pause");
		return;
	}
	system("cls");
	while (true)
	{
		cout << "Main menu -> Work with existing projects menu -> Alter Menu";
		projects->Show();
		cout << "Choose:\n";
		cout << "1.Add Task Menu\n";
		cout << "2.Alter Task Menu\n";
		cout << "3.Change project's name\n";
		cout << "4.Go back\n";
		char choice[Lchoice];
		cout << "Enter your choice:\n";
		fgets(choice, Lchoice, stdin);
		fseek(stdin, 0, SEEK_END);
		choice[strlen(choice) - 1] = '\0';
		if (checkInt(choice))
		{
			switch (atoi(choice))
			{
			case 1: AddTaskMenu(projects, found->name); break;
			case 2: EditTaskMenu(found->tasks); break;
			case 3: EditName(projects, found->name); break;
			case 4: return;
			default: cout << "No such option.\n"; system("pause"); break;
			}
		}
		else
		{
			cout << "Wrong input!!!\n";
			system("pause");
		}
		system("cls");
	}
}
void EditName(Projects *projects, char *name)
{
	cout << "Enter new name for the project:\n";
	char choice[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	projects->Change(name, choice);
	system("pause");
}
void EditTaskMenu(Project *project)
{
	system("cls");
	project->Show();
	cout << "Enter the name of a task to alter:\n";
	char choice[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	Task *found = project->Find(choice);
	if (!found)
	{
		cout << "A task with such name isn't found.\n";
		system("pause");
		return;
	}
	system("cls");
	while (true)
	{
		cout << "Main menu -> Work with existing projects menu -> Alter Menu -> Alter Task Menu\n";
		project->Show(found);
		cout << "Choose:\n";
		cout << "1.Delete\n";
		cout << "2.Allot money\n";
		cout << "3.Change description\n";
		cout << "4.Assign people\n";
		cout << "5.Dismiss people\n";
		cout << "6.Change start date\n";
		cout << "7.Change finish date\n";
		cout << "8.Change task's name\n";
		cout << "9.Go back\n";
		char choice[Lchoice];
		cout << "Enter your choice:\n";
		fgets(choice, Lchoice, stdin);
		fseek(stdin, 0, SEEK_END);
		choice[strlen(choice) - 1] = '\0';
		DateCheck *change = new DateCheck();
		if (checkInt(choice))
		{
			switch (atoi(choice))
			{
			case 1: project->DeleteTask(found->name); break;
			case 2: AllotMoney(found, project); break;
			case 3: project->AddDefinition(found); break;
			case 4: project->AssignPeople(found); break;
			case 5: project->Dismiss(found); break;
			case 6: EnterDate("Enter new start date.\n", change); project->ChangeStart(change, found->name); project->Sort(); break;
			case 7: EnterDate("Enter new finish date.\n", change); project->ChangeFinish(change, found->name); project->Sort(); break;
			case 8: ChangeTaskName(project, found->name); break;
			case 9: return;
			default: cout << "No such option.\n"; system("pause"); break;
			}
		}
		else
		{
			cout << "Wrong input!!!\n";
			system("pause");
		}
		system("cls");
		delete change;
	}
}
void ChangeTaskName(Project *project, char *name)
{
	cout << "Enter new name for the task:\n";
	char choice[nameLength];
	fgets(choice, nameLength, stdin);
	fseek(stdin, 0, SEEK_END);
	choice[strlen(choice) - 1] = '\0';
	cout << endl;
	project->ChangeName(name, choice);
	system("pause");
}
void EnterDate(char *output, DateCheck *date)
{
	cout << output;
	system("pause");
	while (true)
	{
		system("cls");
		char day[] = "Enter new day:\n";
		int d = inputInt(day);
		char month[] = "Enter new month:\n";
		int m = inputInt(month);
		char year[] = "Enter new year:\n";
		int y = inputInt(year);
		date->Initialize(d, m, y);
		system("pause");
		if (date->IsInitialized()) break;
	}
}
