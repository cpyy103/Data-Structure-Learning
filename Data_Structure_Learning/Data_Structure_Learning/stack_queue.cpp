#include<stdio.h>
#include "stack_queue.h"
#include<stdlib.h>


//检查括号是否配对 
void CheckBracket()
{

	char *s = "({}{[]})";
	puts(s);
	if (Check(s))
		printf("括号配对成功\n");
	else
		printf("括号配对失败\n");

	printf("--------------------\n");
}
bool Check(char *s)
{
	SqStack S;
	InitStack(S);
	int e;      //由于定义的Push,Pop函数中的元素是int，若使用char会报错，相当于内部ASCII转换了 
	for (int i = 0; s[i] != '\0'; i++)
		switch (s[i])
		{
		case '(':
			Push(S, '(');
			break;
		case '{':
			Push(S, '{');
			break;
		case '[':
			Push(S, '[');
			break;
		case ')':
			Pop(S, e);
			if (e != '(')
				return false;
			break;
		case ']':
			Pop(S, e);
			if (e != '[')
				return false;
			break;
		case '}':
			Pop(S, e);
			if (e != '{')
				return false;
			break;
		}
	if (!isStackEmpty(S))
		return false;
	return true;

}

//利用一个队列和一个空栈将元素逆置 
void Reverse_StackQueue()
{
	//条件初始化 
	int e, i;
	SqQueue Q;
	SqStack S;
	InitStack(S);
	InitQueue(Q);
	printf("InitQueue :\n");
	for (i = 1; i<10; i++) {
		EnQueue(Q, i);
		printf("%d ", i);
	}
	printf("\n");

	while (!isQueueEmpty(Q))
	{
		DeQueue(Q, e);
		Push(S, e);
	}
	printf("Reversed Queue:\n");
	while (!isStackEmpty(S))
	{
		Pop(S, e);
		EnQueue(Q, e);
		printf("%d ", e);
	}
	printf("\n");

	printf("--------------------\n");
}

void StackQueueTest()
{
	StackTest();
	QueueTest();
	Reverse_StackQueue();
	CheckBracket();
}
void StackTest()
{
	int i, e;
	SqStack S;
	InitStack(S);
	printf("StackTest\n");
	if (isStackEmpty(S))
		printf("The Stack is Empty !\n");

	printf("InitStack :\n");
	for (i = 1; i<10; i++) {
		Push(S, i);
		printf("%d ", i);
	}
	printf("\n");

	Pop(S, e);
	printf("pop element: %d \n", e);
	GetTop(S, e);
	printf("get top element: %d \n", e);

	printf("--------------------\n");
}

void QueueTest()
{
	SqQueue Q;
	int e, i;
	InitQueue(Q);
	printf("QueueTest\n");
	if (isQueueEmpty(Q))
		printf("The Queue is Empty !\n");
	printf("InitQueue :\n");
	for (i = 1; i<10; i++) {
		EnQueue(Q, i);
		printf("%d ", i);
	}
	printf("\n");

	DeQueue(Q, e);
	printf("DeQueue element: %d \n", e);
	DeQueue(Q, e);
	printf("DeQueue element: %d \n", e);

	printf("--------------------\n");
}



void InitStack(SqStack &S)
{
	S.top = -1;
}

bool isStackEmpty(SqStack &S)
{
	if (S.top == -1)
		return true;
	else
		return false;
}

bool Push(SqStack &S, int e)
{
	if (S.top == MaxSize - 1)  //栈满 
		return false;
	S.data[++S.top] = e;
	return true;
}

bool Pop(SqStack &S, int &e)
{
	if (S.top == -1)   //栈空 
		return false;
	e = S.data[S.top--];
	return true;
}

bool GetTop(SqStack &S, int &e)
{
	if (S.top == -1)   //栈空 
		return false;
	e = S.data[S.top];
	return true;
}


void InitQueue(SqQueue &Q)
{
	Q.front = Q.rear = 0;
}

bool isQueueEmpty(SqQueue Q)
{
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

bool EnQueue(SqQueue &Q, int e)
{
	if ((Q.rear + 1) % MaxSize == Q.front) //队满
		return false;
	Q.data[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MaxSize; //队尾指针加1取模 
	return true;
}

bool DeQueue(SqQueue &Q, int &e)
{
	if (Q.rear == Q.front) //队空 
		return false;
	e = Q.data[Q.front];
	Q.front = (Q.front + 1) % MaxSize;
	return true;
}
