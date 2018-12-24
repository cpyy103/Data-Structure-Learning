#include<stdio.h>
#include "misc.h"
static int count = 0;
static void hannuo(int n, char a, char b, char c);
void Hannuo(int n)
{
	count = 0;
	printf("The number of disk : %d \n", n);
	printf("The steps are:\n");
	hannuo(n, 'A', 'B', 'C');
	printf("%d steps in total\n", count);
}
//通过c从a搬到b
void hannuo(int n, char a, char b, char c)
{
	if (n == 1)
	{
		printf("%c --> %c\n", a, b);
		count++;
	}
	else
	{
		hannuo(n - 1, a, c, b);
		printf("%c --> %c\n", a, b);
		count++;
		hannuo(n - 1, c, b, a);
	}
}