// lab2task2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

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

int CheckForInt(char *s)
{
	for (int i = 0; i < (int)strlen(s); i++)
	{
		if (s[i] < '0' || s[i] > '9') return -1;
	}
	return atoi(s);
}

int Fact(unsigned int n)
{
	return n == 0 ? 1 : n * Fact(n - 1);
}

double Recursive(double x, double e, int n, double s)
{
	if (n % 2 == 1)
	{
		s += pow(x, 2 * n - 1) / Fact(2 * n - 1);
	}
	else
	{
		s -= pow(x, 2 * n - 1) / Fact(2 * n - 1);
	}
	n++;
	return fabs(s - sin(x)) > e ? Recursive(x, e, n, s) : s;

}

void Iterational(double x, double e)
{
	int n = 1;
	double s = 0;
	do
	{
		if (n % 2 == 1)
		{
			s = s + pow(x, (double)(2 * n - 1)) / (double)Fact(2 * n - 1);
		}
		else
		{
			s = s - pow(x, (double)(2 * n - 1)) / (double)Fact(2 * n - 1);
		}
		n++;
	} while (fabs(s - sin(x)) > e);
	printf("sin(x) through iterational Maclaurin is %lf at number %d.\n", s, n--);
}

void SetPrecision(double * e)
{
	do
	{
		bool cond = true;
		while (cond)
		{
			printf("Set the precision (0, 1): ");
			char str[20];
			cin >> str;
			int check;
			check = CheckForFloat(str);
			if (check == 1)
			{
				*e = (float)atof(str);
				cond = false;
			}
		}
	} while (*e >= 1 || *e <= 0);
}

int main()
{
	int option;
	bool cond = true;
	do
	{
		double x;
		do
		{
			cond = true;
			while (cond)
			{
				printf("Enter x in radians (it is advised to input number from this segment [-2.0, 2.0] (convergence): ");
				char str[20];
				cin >> str;
				int check;
				check = CheckForFloat(str);
				if (check == 1)
				{
					x = (float)atof(str);
					cond = false;
				}
			}
		} while (x > 2. || x < -2.);
		printf("sin(%lf) = %lf\n", x, sin(x));
		double e;
		SetPrecision(&e);
		int opt2;
		do
		{
			int choice;
			cond = true;
			while (cond)
			{
				printf("Select the way to calculate sin(x): 1.recursive 2.iterational(plus number at which we stop) 3.set new precision\n");
				char substr[20];
				cin >> substr;
				choice = CheckForInt(substr);
				if (choice != -1) cond = false;
			}
			switch (choice)
			{
			case 1: printf("sin(x) through recursive Maclaurin is %lf.\n", Recursive(x, e, 1, 0)); break;
			case 2: Iterational(x, e); break;
			case 3: printf("In case you receive suspicious result try some bigger precision.\n"); SetPrecision(&e); break;
			default: printf("Wrong input!\n");
			}
			cond = true;
			while (cond)
			{
				printf("Anything else with this number? 1.Yes 2(or smth else positive than 1).No\n");
				char substr[20];
				cin >> substr;
				opt2 = CheckForInt(substr);
				if (opt2 != -1) cond = false;
			}
		} while (opt2 == 1);
		cond = true;
		while (cond)
		{
			printf("You want to carry on: 1.Yes 2(or smth else positive than 1).No\n");
			char substr[20];
			cin >> substr;
			option = CheckForInt(substr);
			if (option != -1) cond = false;
		}
	} while (option == 1);
	return 0;
}

