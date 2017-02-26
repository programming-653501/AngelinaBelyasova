// lab2task1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void Input(float * n1, float * n2)
{
	scanf_s("%f %f", n1, n2);
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

int main()
{
	printf("Please, enter two float numbers a and b: ");
	float a, b;
	scanf_s("%f %f", &a, &b);
	int option;
	do
	{
		printf("You've got options. Choose. Menu:\n1.New input of a and b\n2.Output of a-and-b-quotient\n");
		printf("3.Sum of a and b\n4.Subtraction of a and b\n5.Multiplication of a and b\n");
		printf("6.Division of a and b\n7.Harmonic Mean\n8.Info about program version and its maker\n9.Exit\nYour option - ");
		scanf_s("%d", &option);
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

