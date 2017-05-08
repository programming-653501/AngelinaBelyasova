#pragma once
struct Date
{
	int day;
	int month;
	int year;
};

class DateCheck
{
private:
	Date date;
	bool initialized;
public:
	DateCheck();
	void Initialize(int d, int m, int y);
	bool FirstCheck(int a, int m, int y);
	int GetMaxDay(int month, int year);
	int Compare(DateCheck *other);
	bool IsLeap(int year);
	bool IsInitialized();
	void Initialize(char *date);
	char * Show();
	int Difference(DateCheck *other);
	~DateCheck();
};