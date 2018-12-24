#include<stdio.h>
#include<stdlib.h>
#include "list.h"

//顺序表，数组测试 
void ListTest()
{
	printf("ListTest\n");
	SqList L;
	int i;
	L.length = 0;
	for (i = 0; i<9; i++)
	{
		L.data[i] = i + 1;
		L.length++;
	}
	printf_list(L);
	if (ListInsert(L, 5, 9))
		printf_list(L);
	if (ListDelete(L, 5))
		printf_list(L);
	printf("locate 4: %d \n", LocateElem(L, 4));

	printf("------------------\n");
	Reverse_1();
}

//链表测试
void LinkListTest()
{
	printf("LinkListTest\n");
	LinkList L1;
	CreateList_Head(L1);
	printf_linklist(L1);
	printf("GetElem_i_4: %d \n", GetElem_i(L1, 4)->data);
	printf("Reverse printf:\n");
	R_printf(L1->next);
	printf("\n");
	printf("Reverse_2 printf:\n");
	printf_linklist(Reverse_2(L1));
	printf("\n");

	LinkList L2;
	CreateList_Tail(L2);
	printf_linklist(L2);
	printf("GetElem_e_4: %d \n", GetElem_e(L2, 4)->data);

	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->data = 3;
	printf("insert a elem:\n");
	printf_linklist(L1);
	printf("delete a elem:\n");
	LinkListDelete(L1, 3);
	printf_linklist(L1);

	printf("kth_from_end : %d\n", Search_Kth(L1, 3)->data);

	printf("-------------------\n");

	FindMajority();
}

//打印数组 
void printf_arr(int A[], int n)
{
	for (int i = 0; i<n; i++)
		printf("%d ", A[i]);
	printf("\n");
}
//打印顺序表 
void printf_list(SqList &L)
{
	for (int i = 0; i<L.length; i++)
		printf("%d ", L.data[i]);
	printf("\n");
}
//打印链表
void printf_linklist(LinkList L)
{
	printf("printf_linklist:\n");
	L = L->next;
	while (L)
	{
		printf("%d ", L->data);
		L = L->next;
	}
	printf("\n");
}
//在i位置插入元素e 
bool ListInsert(SqList &L, int i, int e)
{
	int j;
	if (i<1 || i>L.length) //i有效范围 
		return false;
	if (L.length >= MaxSize)  //储存空间是否已满 
		return false;
	for (j = L.length; j >= i; j--)
		L.data[j] = L.data[j - 1];
	L.data[j] = e;
	L.length++;
	return true;
}

//删除第i个数 
bool ListDelete(SqList &L, int i)
{
	if (i<1 || i>L.length) //i有效范围 
		return false;

	for (int j = i; j<L.length; j++)
		L.data[j - 1] = L.data[j];
	L.length--;
	return true;
}

//返回e的位置 
int LocateElem(SqList L, int e)
{
	for (int i = 0; i<L.length; i++)
		if (L.data[i] == e)
			return i + 1;
	return 0;
}



//头插建立链表 
LinkList CreateList_Head(LinkList &L)
{
	LNode *s;
	int x = 1;
	L = (LinkList)malloc(sizeof(LNode)); //带头结点的链表 
	L->next = NULL;
	while (x<10)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x++;
		s->next = L->next;
		L->next = s;
	}
	return L;
}

//尾插法建立链表 
LinkList CreateList_Tail(LinkList &L)
{
	L = (LinkList)malloc(sizeof(LNode));
	LNode *s, *r = L; //r为表尾指针 
	int x = 1;
	while (x<10)
	{
		s = (LNode*)malloc(sizeof(LNode));
		s->data = x++;
		r->next = s;
		r = s;
	}
	r->next = NULL;
	return L;
}


//按序号查找 
LNode *GetElem_i(LinkList L, int i)
{
	LNode *p = L;
	if (i == 0)
		return L;  //返回头结点
	if (i<0)
		return NULL; //无效
	while (p&&i--)
	{
		//printf("%d ", p->data); 
		p = p->next;

	}

	return i<0 ? p : NULL;
}
//按元素查找 
LNode *GetElem_e(LinkList L, int e)
{
	LNode *p = L;
	while (p&&p->data != e)
		p = p->next;
	return p;
}
//第i个位置插入结点
void LinkListInsert(LinkList L, LNode *s, int i)
{
	LNode *p = GetElem_i(L, i - 1);
	s->next = p->next;
	p->next = s;
}
//第i个位置删除结点
void LinkListDelete(LinkList L, int i)
{
	LNode *p = GetElem_i(L, i - 1);
	LNode *q;
	q = p->next;
	p->next = q->next;
	free(q);
}



//有一维数组A[n]，将A中数据循环左移p个位置
//由(X0,X1,...,Xn-1)变为Xp,Xp+1,..,Xn-1,X0,X1..Xp-1
//将数组从ab变为ba，先将a逆置，得a逆b，再将b逆置得a逆b逆
//将a逆b逆逆置得ba   
void Reverse(int A[], int from, int to)
{
	int i, temp;
	for (i = 0; i<(to - from + 1) / 2; i++)
	{
		temp = A[from + i];
		A[from + i] = A[to - i];
		A[to - i] = temp;
	}
}
void Reverse_1(void)
{
	int A[] = { 1,2,3,4,5,6,7,8,9 };
	int p = 5, n = sizeof(A) / sizeof(A[0]);

	Reverse(A, 0, p - 1);
	Reverse(A, p, n - 1);
	Reverse(A, 0, n - 1);
	printf_arr(A, n);

	printf("--------------------\n");

}


//已知数组A[n],若存在相同的元素x，其个数为m，且m>n/2，则x为主元素
//如A={0,5,5,3,5,7,5,5}，则5为主元素
//如A={0,5,5,3,5,7,5,0}，则没有主元素
void FindMajority(void)
{
	int A[] = { 1,2,3,5,3,7,3,3,3 };
	printf("majority: %d\n", Search(A, sizeof(A) / sizeof(A[0])));

	printf("--------------------\n");
}

int Search(int A[], int n)
{
	int i, count = 1, temp; //temp用来保存候补主元素
	temp = A[0];
	for (i = 1; i<n; i++)
		if (A[i] == temp)
			count++;
		else
			if (count>0)
				count--;
			else
			{
				temp = A[i];
				count = 1;
			}
	if (count>0)
		for (i = count = 0; i<n; i++)
			if (A[i] == temp)
				count++;
	if (count>n / 2)      //确认主元素 
		return temp;
	else
		return -1;
}

//查找链表中倒数第k位置上的结点
LNode *Search_Kth(LinkList L, int k)
{
	LNode *p = L, *q = L;
	while (k--)
		p = p->next;
	while (p)
	{
		p = p->next;
		q = q->next;
	}
	return q;
}

//查找两链表公共后缀
int LinkListLen(LinkList L)
{
	int len = 0;
	LNode *p = L;
	while (p)
	{
		len++;
		p = p->next;
	}
	return len;
}
LNode *FindCommonAddr(LinkList L1, LinkList L2)
{
	int m = LinkListLen(L1), n = LinkListLen(L2);
	LNode *p, *q;
	for (p = L1; m>n; m--) //若m>n,p指向m-n+1个结点 
		p = p->next;
	for (q = L2; m<n; n--)
		q = q->next;
	while (p->next && q->next!=p->next)
	{
		p = p->next;
		q = q->next;
	}
	return p->next;

}
//反向输出链表
void R_printf(LinkList L)
{
	if (L->next)
		R_printf(L->next);
	printf("%d ", L->data);
}
//将链表就地逆置
LinkList Reverse_2(LinkList &L)
{
	LNode *p, *r;
	p = L->next;
	L->next = NULL;  //将头结点摘下
	while (p)
	{
		r = p->next;     //头插
		p->next = L->next;
		L->next = p;
		p = r;
	}
	return L;
}
