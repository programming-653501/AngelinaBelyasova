// lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

int ToBinary(int num, int* arr, const int k) //transmission of m into binary system
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
	bool prog = true;
	while (prog)
	{
		int m;
		const int size = 32;
		int nums;
		bool cond = true;
		while (cond)
		{
			printf("Please, enter positive m as you'll get a wrong result otherwise.\n");
			scanf_s("%d", &m);
			if (m >= 0) cond = false;
		}

		int* arr;
		arr = (int*)calloc(size, sizeof(int)); //array for memorizing bits

		nums = ToBinary(m, arr, size); //the number of bits in binary enterpretation of m

		printf("m in decimal - %d, m in binary - ", m); //the output of m in both systems
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
					dec += (int)pow(2., j);
				}
				if (i % 2 == 1 && (j / 3) % 2 == 0)
				{
					dec += (int)pow(2., j);
				}
			}
			printf("%d", dec);
			printf("\n");
		}
		free(arr);
		printf("Do you want to run it once more? 1.Yes 2.No\n");
		int decision;
		scanf_s("%d", &decision);
		prog = false;
		if (decision == 1) prog = true;
	}
	
	_getch();
    return 0;
}

