#pragma once
#include "date.h"
#include <conio.h>
#include <iostream>
using namespace std;

#define nameLength 50
#define surnameLength 50
#define definition 200

struct Person
{
	char name[nameLength];
	char surname[surnameLength];
	Person *next;
	Person *previous;
};

class People
{
private:
	Person *personnel;
public:
	People();
	~People();
	void Assign(char *name, char *surname);
	void Discharge(char *name);
	void Show();
	Person * SeekByName(char *name);
	Person * SeekBySurname(char *surname);
	Person * GetFirst() { return personnel; }
	void SaveToFile(FILE *file);
};

struct Task
{
	DateCheck start;
	DateCheck finish;
	float resources;
	People *people;
	Task *previous;
	Task *next;
	char name[nameLength];
	char define[definition];
};

class Project
{
private:
	Task *listOfTasks;
public:
	Project();
	void AddTask(DateCheck *start, DateCheck *finish, char *name);
	void DeleteTask(char *name);
	Task * Find(char *name);
	void Show();
	void Show(Task *task);
	void UltimateWay();
	void AllotMoney(Task *task, float resources);
	void AssignPeople(Task *task); 
	void Dismiss(Task *task);
	void AddDefinition(Task *task);
	void ChangeStart(DateCheck *newdate, char *name);
	void ChangeFinish(DateCheck *newdate, char *name);
	void ChangeName(char *name, char *newname);
	void Sort();
	float GetResources();
	void GetTerm();
	Task * FindLast();
	void GetParallel(char *name);
	void GetReserve(DateCheck *now, char *taskname);
	void SaveToFile(FILE *file);
	~Project();
};

struct ProjectStruct
{
	Project *tasks;
	char name[nameLength];
	ProjectStruct *next;
	ProjectStruct *previous;
};

class Projects
{
private:
	ProjectStruct *listOfProjects;
public:
	Projects();
	~Projects();
	void Add(char *name);
	void Delete(char *name);
	void Change(char *oldname, char *newname);
	ProjectStruct * Find(char *name);
	void Show();
	void Show(ProjectStruct *project);
	void SaveToFile();
	void ReadFromFile();
};
