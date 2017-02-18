// lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

int ToBinary(unsigned int num, int* arr, const int k) //transmission of m into binary system
{
	int i;
	for (i = 0; num != 0; i++)
	{
		arr[k - i - 1] = num % 2;
		num /= 2;
	}
	return i;
}

int main()
{
	unsigned long m;
	const int size = 32;
	int nums;
	printf("Please, enter m.\n");
	scanf_s("%u", &m);

	int* arr;
	arr = (int*)calloc(size, sizeof(int)); //array for memorizing bits

	nums = ToBinary(m, arr, size); //the number of bits in binary enterpretation of m

	printf("m in decimal - %u, m in binary - ", m); //the output of m in both systems
	for (int i = size - nums; i < size; i++)
	{
		printf("%d", arr[i]);
	}
	printf("\n");

	int tripl = nums / 3; //the number of triplets of 0 and 1
	printf("The number of bits is %d,  thus the number of triplets is %d\n", nums, tripl);

	printf("Wanted numbers:\n");
	for (int i = 1; i <= tripl; i++)
	{
		printf("The %d number in the binary system - ", i);
		for (int j = 0; j < i; j++)
		{
			if (j % 2 == 0) printf("111");
			else printf("000");
		}
		printf(", in the decimal - ");
		int dec = 0;
		for (int j = 0; j < i * 3; j++)
		{
			if (i % 2 == 0 && (j / 3) % 2 == 1)
			{
				dec += pow(2., j);
			}
			if (i % 2 == 1 && (j / 3) % 2 == 0)
			{
				dec += pow(2., j);
			}
		}
		printf("%u", dec);
		printf("\n");
	}

	free(arr);
	
	_getch();
    return 0;
}

