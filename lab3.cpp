// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

char * coder(char *s, int size);
char * decoder(char *s, int size);
int check(char *s);
void runarray(char *s, char **arr, int size, void(*fn)(char *a, char *b));
void f1(char *a, char *b);
void f2(char *a, char *b);
void f3(char *a, char *b);

int main()
{
	int docontinue;
	do
	{
		int n;
		bool cond = true;
		while (cond)
		{
			cout << "Please, set the approximate size of your string:\n";
			char substr[20];
			cin >> substr;
			n = check(substr);
			if (n > 0) cond = false;
		}
		cout << "Please, enter the string you'd like to operate with:\n";
		char *script = new char[n];
		cin >> script;
		int size_array = (int)ceil(sqrt(strlen(script)));
		cond = true;
		int choice;
		while (cond)
		{
			cout << "1.encrypt\n2.decrypt\n";
			char substr[20];
			cin >> substr;
			choice = check(substr);
			if (choice != -1) cond = false;
		}
		switch (choice)
		{
		case 1: script = coder(script, size_array); cout << "The encrypted string - " << script << endl; break;
		case 2: script = decoder(script, size_array); cout << "The decrypted string - " << script << endl; break;
		default: cout << "Wrong input...\n";
		}
		cond = true;
		while (cond)
		{
			cout << "Do you want to carry on?\n1.Yes 2.No\n";
			char substr[20];
			cin >> substr;
			docontinue = check(substr);
			if (docontinue == 1 || docontinue == 2) cond = false;
		}
	} while (docontinue == 1);
	return 0;
}

char * coder(char *s, int size)
{
	char **arr = new char*[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = new char[size];
		memset(arr[i], '\0', size);
	}
	runarray(s, arr, size, f1);
	int ind = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] != '\0')
			{
				s[ind] = arr[i][j];
				ind++;
			}
		}
	}
	return s;
}

char * decoder(char *s, int size)
{
	char **arr = new char*[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = new char[size];
		memset(arr[i], '\0', size);
	}
	runarray(s, arr, size, f3);
	int ind = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (arr[i][j] == 1)
			{
				arr[i][j] = s[ind];
				ind++;
			}
		}
	}
	ind = 0;
	runarray(s, arr, size, f2);
	return s;
}

void runarray(char *s, char ** arr, int size, void(*fn)(char *a, char *b))
{
	int beg = 0, end = size - 1;
	int ind = 0;
	int len = (int)strlen(s);
	for (int k = 0; ind < len; k++)
	{
		int j = beg, i = beg;
		for (; j <= end && ind < len; j++)
		{
			(*fn)(&arr[j][i], &s[ind]);
			ind++;
		}
		i++;
		j--;
		for (; i <= end && ind < len; i++)
		{
			(*fn)(&arr[j][i], &s[ind]);
			ind++;
		}
		j--;
		i--;
		for (; j >= beg && ind < len; j--)
		{
			(*fn)(&arr[j][i], &s[ind]);
			ind++;
		}
		i--;
		j++;
		for (; i > beg && ind < len; i--)
		{
			(*fn)(&arr[j][i], &s[ind]);
			ind++;
		}
		end--;
		beg++;
	}
}

void f1(char *a, char *b)
{
	*a = *b;
}

void f2(char *a, char *b)
{
	*b = *a;
}

void f3(char *a, char *b)
{
	*a = 1;
}

int check(char *s)
{
	for (int i = 0; i < (int)strlen(s); i++)
	{
		if (s[i] < '0' || s[i] > '9') return -1;
	}
	return atoi(s);
}
