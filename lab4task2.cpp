// lab4task2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <windows.h>

int numberSize(char *text, int position)
{
	return (text[position + 1] <= '9' && text[position + 1] >= '0') ? numberSize(text, position + 1) : position;
}

int parseNumber(char *text, int position, int size)
{
	int number = 0;
	for (int i = 0; i < size; i++)
	{
		int numeral;
		numeral = text[i + position] - '0';
		number += numeral * (int)pow(10., size - i - 1);
	}
	return number;
}

float ArithmeticalMean(char *fileText)
{
	int len = strlen(fileText);
	int count = 0, sum = 0;
	for (int i = 0; i < len; i++)
	{
		if (fileText[i] <= '9' && fileText[i] >= '0')
		{
			int size = numberSize(fileText, i) - i + 1;
			int number = parseNumber(fileText, i, size);
			if (i == 0 || fileText[i - 1] != '-')
			{
				count++;
				sum += number;
				printf("number - %d\n", number);
			}
			i += size;
		}
	}
	return ((float)sum / count);
}

int main()
{
	FILE *FileWithNumbers;
	FILE **FilePointer = &FileWithNumbers;
	char *fileText;
	int sizeOfFile;
	int decision;

	do
	{
		system("cls");
		fopen_s(FilePointer, "d:\\lab4task2.txt", "r");

		fseek(FileWithNumbers, 0, SEEK_END);
		sizeOfFile = ftell(FileWithNumbers);
		rewind(FileWithNumbers);

		fileText = (char*)calloc(sizeOfFile + 1, sizeof(char));
		fread(fileText, sizeOfFile * sizeof(char), 1, FileWithNumbers);
		fclose(FileWithNumbers);

		printf("Text read from the file:\n");
		puts(fileText);

		printf("Arithmetical mean of positive numerics- %f\n", ArithmeticalMean(fileText));
		free(fileText);
		printf("Do you want to carry on? (1 - yes/2 - no)\n");
		scanf_s("%d", &decision);
	} while (decision == 1);
	
    return 0;
}

