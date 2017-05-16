// lab6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

struct Tree
{
	Tree *left = NULL;
	Tree *right = NULL;
	int number = 0;
};

int numberSize(char *text, int position);
int parseNumber(char *text, int position, int size);
void saveNumbersToTree(char *fileText, Tree **node);
void addToTree(int info, Tree **node);
void deleteTree(Tree **node);
void showTree(Tree *node);
void levelsCount(Tree *node, int level, int *count);
void assessEachLevel(const int count, Tree *node);
void findLevelCapacity(Tree *node, int aim, int current, int *count);

int main()
{
	FILE *FileWithNumbers;
	char *fileText;
	int sizeOfFile;
	string choice;

	do
	{
		system("cls");
		fopen_s(&FileWithNumbers, "D:\\lab6.txt", "r");

		fseek(FileWithNumbers, 0, SEEK_END);
		sizeOfFile = ftell(FileWithNumbers);
		rewind(FileWithNumbers);

		fileText = (char*)calloc(sizeOfFile + 1, sizeof(char));
		fread(fileText, sizeOfFile * sizeof(char), 1, FileWithNumbers);
		fclose(FileWithNumbers);

		printf("Text read from the file:\n");
		puts(fileText);

		Tree *top = NULL;
		saveNumbersToTree(fileText, &top);
		printf("Here are your numbers in text stored in a binary tree:\n");
		showTree(top);
		cout << endl;

		int level = 0, count = 0;
		levelsCount(top, level, &count);
		cout << "The quantity of levels in your tree:\n" << count;
		cout << endl;
		assessEachLevel(count, top);

		deleteTree(&top);
		free(fileText);
		do
		{
			cout << "Do you want to repeat? (y/n)\n";
			cin >> choice;
		} while (choice != "y" && choice != "n");
	} while (choice == "y");

	return 0;
}

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

void saveNumbersToTree(char *fileText, Tree **top)
{
	int len = strlen(fileText);
	int size, number;
	for (int i = 0; i < len; i++)
	{
		if (fileText[i] <= '9' && fileText[i] >= '0')
		{
			size = numberSize(fileText, i) - i + 1;
			number = parseNumber(fileText, i, size);
			if (i != 0 && fileText[i - 1] == '-')
			{
				number = -number;
			}
			printf("number - %d\n", number);
			addToTree(number, top);
			i += size;
		}
	}
}

void addToTree(int info, Tree **node)
{
	if (*node == NULL)
	{	
		*node = new Tree;
		(*node)->number = info;
		return;
	}
	if (info < (*node)->number)
	{
		addToTree(info, &(*node)->left);
	}
	if (info >= (*node)->number)
	{
		addToTree(info, &(*node)->right);
	}
}

void deleteTree(Tree **node)
{
	if (*node != NULL)
	{
		deleteTree(&(*node)->left);
		deleteTree(&(*node)->right);
		delete *node;
		*node = NULL;
	}
}

void showTree(Tree *node)
{
	if (node != NULL)
	{
		showTree(node->left);
		cout << node->number << " ";
		showTree(node->right);
	}
}

void levelsCount(Tree *node, int level, int *count)
{
	if (node == NULL)
	{
		*count = level > *count ? level : *count;
		return;
	}
	level++;
	levelsCount(node->left, level, count);
	levelsCount(node->right, level, count);
}

void assessEachLevel(int count, Tree *node)
{
	int quantity;
	for (int i = 0; i < count; i++)
	{	
		quantity = 0;
		findLevelCapacity(node, i, 0, &quantity);
		cout << i + 1 << " level has " << quantity << " elements." << endl;
	}
}

void findLevelCapacity(Tree *node, int aim, int current, int *count)
{
	if (node == NULL) return;
	if (aim == current)
	{
		(*count)++;
		return;
	}
	if (current < aim)
	{
		current++;
		findLevelCapacity(node->left, aim, current, count);
		findLevelCapacity(node->right, aim, current, count);
	}
}