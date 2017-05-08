#include "stdafx.h"
#include <iostream>
using namespace std;
//checks integers for correct input
bool checkInt(char *number)		
{
	int length = (int)strlen(number);
	for (int i = 0; i < length; i++)
	{
		if (i == 0 && number[i] == '-') continue;
		if (number[i] > '9' || number[i] < '0') return false;
	}
	return true;
}
bool CheckForFloat(char *s)
{
	int count1 = 0, count2 = 0;
	for (int i = 0; i < (int)strlen(s); i++)
	{
		if (s[i] == '.') count1++;
		if (s[i] == '-') count2++;
		if ((s[i] < '0' || s[i] > '9') && s[i] != '.' && s[i] != '-') return false;

	}
	if (count2 > 1 || (count2 == 1 && s[0] != '-')) return false;
	if (count1 > 1) return false;
	else if (s[0] == '.' || (s[0] == '-' && s[1] == '.')) return false;
	return true;
}