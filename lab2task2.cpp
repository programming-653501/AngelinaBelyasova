// lab2task2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <math.h>

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
		printf("Set the precision (0, 1): ");
		scanf_s("%lf", e);
	} while (*e >= 1 || *e <= 0);
}

int main()
{
	int option;
	do
	{
		double x;
		do
		{
			printf("Enter x in radians (it is advised to input number from this segment [-2.0, 2.0] (convergence): ");
			scanf_s("%lf", &x);
		} while (x > 2. || x < -2.);
		printf("sin(%lf) = %lf\n", x, sin(x));
		double e;
		SetPrecision(&e);
		int opt2;
		do
		{
			printf("Select the way to calculate sin(x): 1.recursive 2.iterational(plus number at which we stop) 3.set new precision\n");
			int choice;
			scanf_s("%d", &choice);
			switch (choice)
			{
			case 1: printf("sin(x) through recursive Maclaurin is %lf.\n", Recursive(x, e, 1, 0)); break;
			case 2: Iterational(x, e); break;
			case 3: SetPrecision(&e); break;
			default: printf("Wrong input!\n");
			}
			printf("In case you receive suspicious result try some bigger precision.\n");
			printf("Anything else with this number? 1.Yes 2.No\n");
			scanf_s("%d", &opt2);
		} while (opt2 == 1);
		printf("You want to carry on: 1.Yes 2.No\n");
		scanf_s("%d", &option);
	} while (option == 1);
	return 0;
}

