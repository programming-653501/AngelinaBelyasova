#pragma once
#include "projects.h"
void mainMenu();
void Help();
void Archive();
void AddProjectMenu(Projects *projectGroup);
void AddTaskMenu(Projects *projectGroup, char *name);
void AddProject(Projects *projectGroup);
void AddTask(Project *project);
int inputInt(char *string);
void SpecifyMenu(Task *task, Project *project);
void AllotMoney(Task *task, Project *project);
void AddDefinition(Task *task, Project *project);
void AssignPeople(Task *task, Project *project);
void WorkWithExistingMenu(Projects *projects);
void View(Projects *projects);
void AlterMenu(Projects *projects);
void EraseProject(Projects *projects);
void GetTerms(Projects *projects);
void GetUltimateWay(Projects *projects);
void GetTimeReserveMenu(Projects *projects);
void GetTimeReserveForTask(Project *project, DateCheck *now);
void GetParallelTasks(Projects *projects);
void EditName(Projects *projects, char *name);
void EditTaskMenu(Project *project);
void ChangeTaskName(Project *project, char *name);
void EnterDate(char *output, DateCheck *date);