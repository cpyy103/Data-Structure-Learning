#include<stdio.h>
#include"misc.h"

static int a[20][20] = { 0 };
static int n;
static int count = 0;

static void queen(int i, int j);
static bool check(int i, int j);


void Queen_n(int x)
{
	n = 8;
	queen(0, 0);
	printf("%d Queens %d Solutions\n", n, count);

}

void queen(int i, int j)
{

	if (j == n)		//右侧越界，表示已经放满
		return;
	if (check(i, j))//如果能放
	{
		a[i][j] = 1;
		if (i == n - 1)  //如果已经到了最后一行，表示放满，记录
		{
			count++;
			for (int ii = 0; ii<n; ii++)
			{
				for (int jj = 0; jj<n; jj++)
					printf("%3d", a[ii][jj]);
				printf("\n");
			}
			printf("\n\n");
		}
		else
			queen(i + 1, 0); //从下一行最左边开始放
	}

	a[i][j] = 0;//如果位置不能放，写0置空
				//如果位置能放，此时上面的代码已经执行，已经记录下这一种情况，置空，判断其他位置
	queen(i, j + 1);
}

bool check(int i, int j)
{
	int ii;
	for (ii = 0; ii < n; ii++)
	{
		if (a[i][ii] || a[ii][j])		//横竖线上有皇后
			return 0;
		if ((i - ii >= 0 && j - ii >= 0 && a[i - ii][j - ii]) || (i + ii < n && j + ii < n && a[i + ii][j + ii]))	//左上到右下
			return 0;
		if ((i - ii >= 0 && j + ii < n && a[i - ii][j + ii]) || (i + ii < n && j - ii >= 0 && a[i + ii][j - ii]))	//左下到右上
			return 0;
	}
	return 1;

}
