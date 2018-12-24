#include <stdio.h>
#include"pointer.h"
void PointTest()
{
	int a[4][3] = {
		1,2,3,
		4,5,6,
		7,8,9,
		10,11,12
	};

	int(*prow)[3];	//指向二维数组，行数不定，3列。如a[4][3]
	int *pcol[3];   //指针数组
	int *p;

	pcol[0] = &a[0][2];
	pcol[1] = &a[1][2];
	pcol[2] = &a[3][1];
	printf("%d %d %d\n", *pcol[0], *pcol[1], *pcol[2]);		// 3 6 11

	prow = a;
	printf("%d %d %d\n", *prow[0], *prow[1], *(prow[3]+1));	// 1 4 11,  第1行第1个数，第2行第1个数，第3行第2个数
															//prow先与[]结合（第i行），再与*结合（*的右结合性）		
	printf("%d %d %d\n", (*prow)[0], (*prow)[1], *(*prow + 1));	//1 2 2, 每列的第一个数，prow先于*结合（第i列）
	printf("%d %d %d\n", *prow + 2, *(*prow + 2), *(*prow + 2) + 2);	//xxxxxx  3 5, 第3列地址 第三列第一个数 第三列第一个数加2
	printf("%d %d %d %d\n", **prow, *(*(prow + 1)), *(*(prow + 1) + 1), *(*(prow + 2) + 3)); //1 5 10, a[0][0] a[1][0] a[1][1] 
																			//a[2][3](由于下标表偏移，每行有3个数，a[2][3]即为a[3][0])

	prow = a + 1;		//prow =& a[1] 
	printf("%d %d %d\n", (*prow)[0], (*prow)[1], (*prow)[2]);	//4 5 6, 第二行每列的第一个数
	printf("%d %d %d\n", *(*prow + 1) + 2, *(*prow + 1), *(*(prow + 1) + 1));  //7 5 8
	printf("%d %d %d \n", *prow[1], *(prow[1] + 1), prow[1][2]); //7 8 9

	printf("%d %d %d\n", a[2][1], *(a[2] + 1), *(*(a + 2) + 1));	//8 8 8, 等价
	printf("%d %d %d %d %d \n", **a, **(a + 1), *(*(a + 1) + 1), *(*a + 1), (*a)[1]); //1 4 5 2 2
	printf("---------------------\n");
	
	int b[10] = { 10,20,30,40,50,60,70,80,90,100 };
	p = b;	
	printf("%d\n", *p);		//10  
	printf("%d ", *p++);	//10  先取值，指针自加1
	printf("%d\n", *p);		//20
	printf("%d ", *++p);	//30  指针自加，取值
	printf("%d\n", *p);		//30
	printf("%d ", ++*p);	//31 指针所指向的值加1，取值
	printf("%d\n", *p);		//31

	for (int i = 0; i < 5; i++)		//10 20 31 40 50
		printf("%d ", b[i]);
	printf("\n\n");

	p = b + 5;
	printf("%d\n", *p);		//60
	printf("%d ", *(p++));	//60 先取值，指针自加1
	printf("%d\n", *p);		//70
	printf("%d ", *(++p));	//80 指针自加，取值
	printf("%d\n", *p);		//80
	printf("%d ", ++(*p));	//81 指针所指向的值加1，取值
	printf("%d\n", *p);		//81
	printf("%d ", (*p)++);	//81  取值，指针所指向的值加1
	printf("%d\n", *p);		//82

	for (int i = 5; i < 10; i++)	//60 70 82 90 100
		printf("%d ", b[i]);
	printf("\n\n");

	struct test {
		int x, y;
	}t[4] = { {10,20}, {30,40}, {50,60}, {70,80} };
	struct test *tt = t;
	printf("%d\n", tt->x);		//10
	printf("%d\n", tt++->x);	//10
	printf("%d\n", tt->x);		//30
	printf("%d\n", ++tt->x);	//31
	printf("%d\n", tt->x);		//31
	printf("%d\n", tt->x++);	//31
	printf("%d\n", tt->x);		//32
	printf("%d\n", (++tt)->x);	//50
	printf("%d\n", tt->x);		//50
	printf("%d\n", (tt++)->x);	//50
	printf("%d\n", tt->x);		//70


}