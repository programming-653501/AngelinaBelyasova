// lab2task1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void Menu()
{
	printf("You've got options. Choose. Menu:\n1.New input of a and b\n2.Output of a-and-b-quotient\n");
	printf("3.Sum of a and b\n4.Subtraction of a and b\n5.Multiplication of a and b\n");
	printf("6.Division of a and b\n7.Harmonic Mean\n8.Info about program version and its maker\n9.Exit\nYour option - ");
}

int CheckForFloat(char *s)
{
	int count1 = 0, count2 = 0;
	for (int i = 0; i < (int)strlen(s); i++)
	{
		if (s[i] == '.') count1++;
		if (s[i] == '-') count2++;
		if ((s[i] < '0' || s[i] > '9') && s[i] != '.' && s[i] != '-') return 0;

	}
	if (count2 > 1 || (count2 == 1 && s[0] != '-')) return 0;
	if (count1 > 1) return 0;
	else if (s[0] == '.' || (s[0] == '-' && s[1] == '.')) return 0;
	return 1;
}

void Input(float *n1, float *n2)
{
	bool cond = true;
	while (cond)
	{
		printf("Please, enter two float numbers a and b: ");
		char str1[20], str2[20];
		cin >> str1;
		cin >> str2;
		int check;
		check = CheckForFloat(str1) + CheckForFloat(str2);
		if (check == 2)
		{
			*n1 = (float)atof(str1);
			*n2 = (float)atof(str2);
			cond = false;
		}
	}
}

void Ratio(float a, float b)
{
	if (a == 0 || b == 0) printf("No fraction possible while a or b equals 0.\n");
	else printf("Two fractions: a / b = %f / %f, b / a = %f / %f\n", a , b, b, a);
}

void Sum(float a, float b)
{
	printf("a + b = %f\n", a + b);
}

void Subt(float a, float b)
{
	printf("a - b = %f, b - a = %f\n", a - b, b - a);
}

void Multi(float a, float b)
{
	printf("a * b = %f\n", a * b);
}

void Delet(float a, float b)
{
	if (a == 0 && b != 0) printf("a / b = %f (a = 0)\n", a / b);
	else if (b == 0 && a != 0) printf("b / a = %f (b = 0)\n", b / a);
	else if (b == 0 && a == 0) printf("a = 0 and b = 0.\n");
	else printf("a / b = %f, b / a = %f\n", a / b, b / a);
}

void Harm(float a, float b)
{
	if (a != 0 && b != 0) printf("Harmonic mean is %f\n", 2 / ((1 / a) + (1 / b)));
	else printf("a or b can't be zero values.\n");
}

void Info()
{
	printf("This is the realization of task 1(lab2). The author is Angelina Belyasova.\nAll rights reserved.\n");
}

int CheckForInt(char *s)
{
	for (int i = 0; i < (int)strlen(s); i++)
	{
		if (s[i] < '0' || s[i] > '9') return -1;
	}
	return atoi(s);
}


int main()
{
	float a, b;
	bool cond = true;
	while (cond)
	{
		printf("Please, enter two float numbers a and b: ");
		char str1[20], str2[20];
		cin >> str1;
		cin >> str2;
		int check;
		check = CheckForFloat(str1) + CheckForFloat(str2);
		if (check == 2)
		{
			a = (float)atof(str1);
			b = (float)atof(str2);
			cond = false;
		}
	}
	int option;
	do
	{
		cond = true;
		while (cond)
		{
			Menu();
			char substr[20];
			cin >> substr;
			option = CheckForInt(substr);
			if (option != -1) cond = false;
		}
		switch (option)
		{
		case 1: Input(&a, &b); break;
		case 2: Ratio(a, b); break;
		case 3: Sum(a, b); break;
		case 4: Subt(a, b); break;
		case 5: Multi(a, b); break;
		case 6: Delet(a, b); break;
		case 7: Harm(a, b); break;
		case 8: Info(); break;
		case 9: break;
		default: printf("Wrong input\n");
		}
		printf("Press any key to continue.\n");
		_getch();
		system("cls");
	} while (option != 9);
    return 0;
}

