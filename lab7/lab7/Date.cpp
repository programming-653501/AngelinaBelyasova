#include "stdafx.h"
#include "date.h"
#include <iostream>
using namespace std;
#define CurrentYear (2017 + 5)
DateCheck::DateCheck()
{
	initialized = false;
}
void DateCheck::Initialize(int d, int m, int y)
{
	if (FirstCheck(d, m, y))
	{
		date.day = d;
		date.month = m;
		date.year = y;
		initialized = true;
	}
}
bool DateCheck::FirstCheck(int d, int m, int y)
{
	int limit = GetMaxDay(m, y);
	if (y <= CurrentYear && m <= 12 && m >= 1 && d >= 1 && d <= limit) return true;
	if (y > CurrentYear) cout << "Wrong year!\n";
	if (m > 12 || m < 1) cout << "Wrong month!\n";
	if (d > limit || d < 1) cout << "Wrong day!\n";
	return false;
}
int DateCheck::GetMaxDay(int month, int year)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: return 31;
	case 4:
	case 6:
	case 9:
	case 11: return 30;
	case 2: return IsLeap(year) ? 29 : 28;
	default: return 31;
	}
}
bool DateCheck::IsLeap(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) return true;
	return false;
}
DateCheck::~DateCheck()
{
	initialized = false;
}
int DateCheck::Compare(DateCheck *other)
{
	if (this->date.year == other->date.year &&
		this->date.day == other->date.day &&
		this->date.month == other->date.month)	return 0;
	if (this->date.year > other->date.year) return 1;
	if (this->date.year < other->date.year) return -1;
	if (this->date.month > other->date.month) return 1;
	if (this->date.month < other->date.month) return -1;
	if (this->date.day > other->date.day) return 1;
	if (this->date.day < other->date.day) return -1;
	return 0;
}
bool DateCheck::IsInitialized()
{
	return initialized ? true : false;
}
char * DateCheck::Show()
{
	if (!IsInitialized()) return "";
	int size = 11;
	char *dataInString = new char[size];
	memset(dataInString, 0, size);
	char intermediate[5];
	_itoa_s(date.day, intermediate, 10);
	strcat_s(dataInString, size, intermediate);
	strcat_s(dataInString, size, ".");
	_itoa_s(date.month, intermediate, 10);
	strcat_s(dataInString, size, intermediate);
	strcat_s(dataInString, size, ".");
	_itoa_s(date.year, intermediate, 10);
	strcat_s(dataInString, size, intermediate);
	return dataInString;
}
int DateCheck::Difference(DateCheck *other)
{
	if (this->date.year - other->date.year > 15)
	{
		cout << "more than ";
		return 15 * 365;
	}
	if (this->Compare(other) == 0) return 0;
	DateCheck *first = other, *second = this;
	if (this->Compare(other) == -1)
	{
		first = this;
		second = other;
	}
	int days1 = first->date.day;
	int month = first->date.month;
	for (int i = 1; i < month; i++)
	{
		days1 += GetMaxDay(i, first->date.year);
	}
	int days2 = second->date.day;
	month = second->date.month;
	for (int i = 1; i < month; i++)
	{
		days2 += GetMaxDay(i, second->date.year);
	}
	for (int i = first->date.year; i < second->date.year; i++)
	{
		if (IsLeap(i)) days2 += 366;
		else days2 += 365;
	}
	days2 -= days1;
	return days2;
}
void DateCheck::Initialize(char *dateString)
{
	char date[11];
	strcpy_s(date, 11, dateString);
	int day, month, year;
	char *token, *next_token;
	char separators[] = ".";
	token = strtok_s(date, separators, &next_token);
	day = atoi(token);
	token = strtok_s(NULL, separators, &next_token);
	month = atoi(token);
	token = strtok_s(NULL, separators, &next_token);
	year = atoi(token);
	(DateCheck::date).day = day;
	(DateCheck::date).month = month;
	(DateCheck::date).year = year;
	initialized = true;
}