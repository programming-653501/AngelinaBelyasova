// lab5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

struct numberStorage
{
	numberStorage *next = NULL;
	numberStorage *previous = NULL;
	int figure = 0;
};

struct stackOfResidues
{
	stackOfResidues * next = NULL;
	int residue = 0;
} *top = NULL;

bool check(string number);
numberStorage * parse(string number);
void deleteListFrom(numberStorage *head);
void toOctal(numberStorage *head);
void addToStack(int residue);
void showResidues();

int main()
{
	string number, choice;
	do
	{
		do
		{
			cout << "Enter your number:\n";
			cin >> number;
		} while (!check(number));

		numberStorage *head;
		head = parse(number);

		toOctal(head);
		cout << "Your number in octal radix:\n";
		showResidues();
		cout << endl;

		deleteListFrom(head);
		head = NULL;

		do
		{
			cout << "Do you want to repeat? (y/n)\n";
			cin >> choice;
		} while (choice != "y" && choice != "n");

	} while (choice == "y");
    return 0;
}

bool check(string number)
{
	int length = number.length();
	for (int i = 0; i < length; i++)
	{
		if (number[i] < '0' || number[i] > '9')
		{
			return false;
		}
	}
	return true;
}

numberStorage * parse(string number)
{
	numberStorage *head = NULL, *current, *end = NULL;
	int length = number.length();
	for (int i = 0; i < length; i++)
	{
		current = new numberStorage;
		current->previous = end;
		current->figure = number[i] - 48;
		if (i == 0) head = current;
			else end->next = current;
		end = current;
	}
	return head;
}

void deleteListFrom(numberStorage *item)
{
	numberStorage *temp;
	if (item == NULL) return;
	if (item->previous != NULL)
	{
		item->previous->next = NULL;
	}
	while (item != NULL)
	{
		temp = item;
		item = item->next;
		delete temp;
	}
}

void toOctal(numberStorage *head)
{
	int medium = 0;
	numberStorage *current, *record;
	current = head;
	record = head;
	while (current != NULL)
	{
		medium = current->figure + medium * 10;
		if (medium < 8 && current == head)
		{
			if (current->next == NULL)
			{
				addToStack(medium);
				return;
			}
			current = current->next;
			continue;
		}
		current = current->next;
		record->figure = medium / 8;
		medium = medium % 8;
		record = record->next;
	}
	deleteListFrom(record);
	addToStack(medium);
	toOctal(head);
}

void addToStack(int residue)
{
	stackOfResidues *temp = new stackOfResidues;
	temp->next = top;
	temp->residue = residue;
	top = temp;
}

void showResidues()
{
	stackOfResidues *temp;
	while (top != NULL)
	{
		cout << top->residue;
		temp = top;
		top = top->next;
		delete temp;
	}
}
