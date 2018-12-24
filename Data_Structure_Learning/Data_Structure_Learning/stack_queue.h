#ifndef STACKQUEUE_H
#define STACKQUEUE_H
#define MaxSize 50
//栈 
typedef struct {
	int data[MaxSize];
	int top;   //栈顶指针 
}SqStack;
//队列 
typedef struct {
	int data[MaxSize];
	int front, rear;
}SqQueue;



void InitStack(SqStack &S);
bool isStackEmpty(SqStack &S);
bool Push(SqStack &S, int e);
bool Pop(SqStack &S, int &e);
bool GetTop(SqStack &s, int &e);
void StackTest(void);

//循环队列 
void InitQueue(SqQueue &Q);
bool isQueueEmpty(SqQueue Q);
bool EnQueue(SqQueue &Q, int e);
bool DeQueue(SqQueue &Q, int &e);
void QueueTest(void);

void StackQueueTest(void);


void Reverse_StackQueue(void);
void CheckBracket(void);
bool Check(char *s);

#endif
