#ifndef LIST_H
#define LIST_H
#define MaxSize 50

//顺序表 
typedef struct {
	int data[MaxSize];
	int length;
}SqList;

//单链表 
typedef struct LNode {
	int data;
	struct LNode *next;
}LNode, *LinkList;

//双链表 
typedef struct DNode {
	int data;
	struct DNode *prior, *next;
}DNode, *DLinkList;



void ListTest(void);
void LinkListTest(void);


void printf_list(SqList &L);
bool ListInsert(SqList &L, int i, int e);
int LocateElem(SqList L, int e);
bool ListDelete(SqList &L, int i);
void LinkListInsert(LinkList L, LNode *s, int i);
void LinkListDelete(LinkList L, int i);


void printf_linklist(LinkList L);
LinkList CreateList_Head(LinkList &L);
LinkList CreateList_Tail(LinkList &L);
void LinkListInsert(LinkList L, LNode *s, int i);
void LinkListDelete(LinkList L, int i);
LNode *GetElem_i(LinkList L, int i);
LNode *GetElem_e(LinkList L, int e);
int LinkListLen(LinkList L);



void printf_arr(int A[], int n);
void Reverse(int A[], int from, int to);
void Reverse_1(void);


void FindMajority(void);
int Search(int A[], int n);

LNode *Search_Kth(LinkList L, int k); //寻找第K个结点
LNode *FindCommonAddr(LinkList L1, LinkList L2);  //寻找公共后缀
void R_printf(LinkList L);   //反向输出
LinkList Reverse_2(LinkList &L);  //就地逆置

#endif


