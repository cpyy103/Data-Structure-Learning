#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"misc.h"


void MiscTest()
{
	int a = 2, b = 5, c = 8;
	a ^= b ^= a ^= b;		//两数交换
	printf("a=%d b=%d\n", a, b);

	Array_1(10);

	printf("%d %d\n", Cal(34), Cal(0xEF));
	printf("%d\n", Transfer("fa"));

	//Queen_n(8);
	//Hannuo(3);

	PrintGodBless();

}
void Array_1(int n)
{
	int i, j, a[20][20];
	int left = 0, right = n - 1, up = 0, down = n - 1;
	int x = 1, row = right, col = down, d = 1;
	printf("n=%d\n", n);
	while (x <= n*n)
	{
		a[row][col] = x++;
		switch (d)
		{
		case 1:
			col--;
			if (col == left)
				d = 2;
			break;
		case 2:
			row--;
			if (row == up)
				d = 3;
			break;
		case 3:
			col++;
			if (col == right)
				d = 4;
			break;
		case  4:
			row++;
			if (row == down)
			{
				down--;
				left++;
				up++;
				right--;
				row--;
				col--;
				d = 1;
			}
			break;
		}

	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}
}

//计算二进制数中有几个1
int Cal(int n)
{
	int count = 0;
	while (n)
	{
		count++;
		n = n&(n - 1);
	}
	return count;
}
//字符串16数转换为10进制输出
int Transfer(char *s)
{
	int n = 0, i = 0, temp;
	while (s[i] != '\0')
	{
		if (s[i] >= '0'&&s[i] <= '9')
			temp = s[i] - '0';
		else
			temp = s[i] - 'a' + 10;
		n = n * 16 + temp;
		i++;
	}
	return n;
}
