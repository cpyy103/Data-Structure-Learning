#include<stdio.h>
#include<stdlib.h>
#include "tree.h"

void BiTreeTest(void)
{
	int A[] = { 0,1,2,3,4,5,6,7,8,9 };  //第0个数据不参与树的生成
	int B[] = { 0,4,3,5,2,6,1,8,9,7 };
	BiTree T = LevelCreateBiTree(A+1, sizeof(A) / sizeof(A[0])-1); //第0个数据不参与树的生成
	BiTreeInfo(T);
	//BiTree T1 = PreInCreateBiTree(A, B, 1, 9, 1, 9);
	//BiTreeInfo(T1);
	//SearchAncestor(T1, 9);
	//printf("%d %d 's CommAncestor: %d\n", 4, 6, FindCommAnsestor_2(T1, 4, 6));

	/*BiTree T3;
	PreCreateBiTree(T3);
	PreOrder(T3);*/

	//TreeTest();
	//TreeTest_BST();
}
//层序建立二叉树，完全二叉树
BiTree LevelCreateBiTree(int A[], int n)
{
	if (n == 0)
		return NULL;

	BiTree tree = NULL, pnew;
	pNode phead = NULL, ptail = NULL, listpnew = NULL, pcur = NULL;

	for (int i = 0; i < n; i++)
	{
		pnew = (BiTree)calloc(1, sizeof(BiTNode));
		pnew->data = A[i];
		listpnew = (pNode)calloc(1, sizeof(Node));
		listpnew->p = pnew;
		if (i == 0) //初始化
		{
			tree = pnew;//树根
			phead = listpnew;
			ptail = listpnew;
			pcur = listpnew;
			continue;
		}
		else
		{
			ptail->next = listpnew;  //将新结点放入链表
			ptail = listpnew;
		}
		//将结点插入二叉树
		if (pcur->p->lchild == NULL)
		{
			pcur->p->lchild = pnew;
		}
		else if (pcur->p->rchild == NULL)
		{
			pcur->p->rchild = pnew;
			pcur = pcur->next;
		}
	}

	return tree;
}
//先序建立二叉树
void PreCreateBiTree(BiTree &p)
{
	int elem;
	scanf("%d", &elem);
	if (elem == 0)  //若为0，表示无对应子树
		p = NULL;
	else
	{
		p = (BiTree)malloc(sizeof(BiTNode));
		p->data = elem;
		printf("Input %d -> lchild:\n", elem);
		PreCreateBiTree(p->lchild);
		printf("Input %d -> rchild:\n", elem);
		PreCreateBiTree(p->rchild);
	}
	
}
//二叉树按顺序表存储时寻找i,j公共祖先
int FindCommAncestor(SqList T, int i, int j)
{
	if(T.data[i]&&T.data[j])
		while (i != j)
		{
			if (i > j)
				i /= 2;
			else
				j /= 2;
		}
	return T.data[i];
}
//先序
void PreOrder(BiTree p)
{
	if (p)
	{
		visit(p);
		PreOrder(p->lchild);
		PreOrder(p->rchild);
	}
}
//先序非递归
void PreOrder_2(BiTree T)
{
	BiTree S[MaxSize], p = T;
	int top = -1;
	while (p || top != -1)
	{
		if (p)
		{
			visit(p);
			S[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = S[top--];
			p = p->rchild;
		}
	}
}
//中序
void InOrder(BiTree p)
{
	if (p)
	{		
		InOrder(p->lchild);
		visit(p);
		InOrder(p->rchild);
	}
}
//中序非递归
void InOrder_2(BiTree T)
{
	BiTree S[MaxSize], p = T; //借助栈
	int top = -1;
	while (p || top != -1)
	{
		if (p)     //遍历左子树，非空则进栈
		{
			S[++top] = p;		
			p = p->lchild;
		}
		else     //若左子树为空，退栈，访问，再遍历右子树
		{
			p = S[top--];	
			visit(p);
			p = p->rchild;
		}
	}
}
//后序
void PostOrder(BiTree p)
{
	if (p)
	{
		PostOrder(p->lchild);
		PostOrder(p->rchild);
		visit(p);
	}
}
//后序非递归
void PostOrder_2(BiTree T)
{
	BiTree S[MaxSize], p = T, r = NULL;  //r用来记录
	int top = -1;
	while (p || top != -1)
	{
		if (p)             //最左边
		{
			S[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = S[top];				//取栈顶
			if (p->rchild&&p->rchild != r)//如果右子树存在且未被访问过
			{
				p = p->rchild;
				S[++top] = p;			
				p = p->lchild;
			}
			else
			{
				p = S[top--];         
				visit(p);
				r = p;				//记录最近访问的结点
				p = NULL;           //重置p
			}
		}
	}

}
//层序
void LevelOrder(BiTree p)
{
	BiTree Q[MaxSize], temp;
	int front = -1, rear = -1;
	Q[++rear] = p;
	while (front < rear)
	{
		temp = Q[++front];
		visit(temp);
		if (temp->lchild)
			Q[++rear] = temp->lchild;
		if (temp->rchild)
			Q[++rear] = temp->rchild;
	}
}
//层序，从下至上，从右至左
void LevelOrder_2(BiTree p)
{
	BiTree Q[MaxSize], S[MaxSize], temp;
	int front = -1, rear = -1, top = -1;
	Q[++rear] = p;
	while (front < rear)
	{
		temp = Q[++front];
		S[++top] = temp;
		if (temp->lchild)
			Q[++rear] = temp->lchild;
		if (temp->rchild)
			Q[++rear] = temp->rchild;
	}
	for (; top >= 0; top--)
		visit(S[top]);
}
//访问结点
void visit(BiTree p)
{
	printf("%d ", p->data);
}
//相关信息
void BiTreeInfo(BiTree p)
{
	printf("PreOrder:\n");
	PreOrder(p);
	printf("\nInOrder:\n");
	InOrder(p);
	printf("\nPostOrder:\n");
	PostOrder(p);
	printf("\nLevelOrder:\n");
	LevelOrder(p);
	printf("\n");
	BiTreeDepthWidth(p);
	WPL(p);
	printf("-------------------\n");
}
//求树的深度（高度），递归
int BiTreeDepth(BiTree T)
{
	if (!T)
		return 0;
	int ldeep = BiTreeDepth(T->lchild);
	int rdeep = BiTreeDepth(T->rchild);

	return ldeep > rdeep ? ldeep + 1 : rdeep + 1;
}
//求树的深度（高度）,最大宽度，非递归，层序
void BiTreeDepthWidth(BiTree T)
{
	if (!T)
		return ;
	BiTree Q[MaxSize], p;
	int front = -1, rear = -1;
	int last = 0, level = 0, width = 0;	//last指向下一层第一个结点位置
	Q[++rear] = T;				//根结点入队
	while (front < rear)
	{
		p = Q[++front];			//出队
		if (p->lchild)
			Q[++rear] = p->lchild;
		if (p->rchild)
			Q[++rear] = p->rchild;
		if (front == last)		//已经到该层最右结点
		{
			level++;			//层数加1
			last = rear;		//last指向下层
			if (width < last - front)
				width = last - front;
		}
	}
	printf("Depth: %d\nWidth: %d\n", level, width);
}
//已知先序中序建树
//A先序，a1为第一个下标，从1开始，a2为最后一个结点下标
//B中序，b1为第一个下标，从1开始，b2为最后一个结点下标
BiTree PreInCreateBiTree(int A[], int B[], int a1, int a2, int b1, int b2)
{
	int i, llen, rlen;
	BiTree root = (BiTree)malloc(sizeof(BiTNode));
	root->data = A[a1];            //根结点
	for (i = b1; B[i] != root->data; i++); //在中序中寻找根结点下标
	llen = i - b1;		//左子树长度
	rlen = b2 - i;		//右子树长度

	if (llen)			//递归建立左子树
		root->lchild = PreInCreateBiTree(A, B, a1 + 1, a1 + llen, b1, b1 + llen - 1);
	else
		root->lchild = NULL;	//左子树为空

	if (rlen)
		root->rchild = PreInCreateBiTree(A, B, a2 - rlen + 1, a2, b2 - rlen + 1, b2);
	else
		root->rchild = NULL;

	return root;

}
//寻找祖先结点，后序遍历
void SearchAncestor(BiTree T, int e)
{
	BiTree S[MaxSize], p = T, r = NULL;  //r用来记录
	int top = -1;
	while (p || top != -1)
	{
		if (p)             //最左边
		{
			S[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = S[top];						//取栈顶
			if (p->rchild&&p->rchild != r)	//如果右子树存在且未被访问过
			{
				p = p->rchild;
				S[++top] = p;			
				p = p->lchild;
			}
			else
			{
				p = S[top--];					
				
				if (p->data == e)		//栈内数据全为祖先结点
				{
					printf("%d 's Ancestor: ", e);
					for (int j = 0; j <= top; j++)
					{
						printf("%d ", S[j]->data);
					}
					printf("\n");
					return;
				}

				r = p;				//记录最近访问的结点
				p = NULL;           //重置p
			}
		}
	}
}
//寻找公共祖先，设a在b左边
int FindCommAnsestor_2(BiTree T, int a, int b)
{
	BiTree S[MaxSize], p = T, r = NULL; 
	int top = -1, j = 0;
	int A[20], B[20];
	while (p || top != -1)
	{
		if (p)        
		{
			S[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = S[top];
			if (p->rchild&&p->rchild != r)	
			{
				p = p->rchild;
				S[++top] = p;
				p = p->lchild;
			}
			else
			{
				p = S[top--];

				if (p->data == a)
					for (j = 0; j <= top; j++)
						A[j] = S[j]->data;      //将栈中数据保存到数组
				if (p->data == b)
				{
					for (j = 0; j <= top; j++)
						B[j] = S[j]->data;
					for (j = 0; j <= top; j++)
					{
						if (A[j] != B[j])		//数据进行比较，当前数据不一样时，上一个数据即为最近公共祖先
							return A[j - 1];
					}
					return A[j - 1];			//一个结点的祖先与另一个结点的祖先相同（或部分相同）
				}
					
				r = p;			
				p = NULL;       
			}
		}
	}
}
//WPL带权路径长度，所有叶结点带权路径长度之和
void WPL(BiTree T)
{
	printf("WPL: %d\n", wplPreOrder(T, 1));
	printf("WPL: %d\n", wplLevelOrder(T));
}
int wplPreOrder(BiTree T, int depth)
{
	static int wpl = 0;                //wpl静态，在测试程序中，第二颗树的树计算的得出WPL值该树实际的WPL值加上第一颗树的WPL值
	if (T->lchild == NULL&&T->rchild == NULL)
		wpl += depth*T->data;

	if (T->lchild != NULL)
		wplPreOrder(T->lchild, depth + 1);
	if (T->rchild != NULL)
		wplPreOrder(T->rchild, depth + 1);

	return wpl;
}
int wplLevelOrder(BiTree T)
{
	if (!T)
		return 0;
	BiTree Q[MaxSize], p;
	int front = -1, rear = -1;
	int last = 0, level = 1, wpl = 0;	// 层数从1开始，程序运行完后实际层数为level的值减1
	Q[++rear] = T;				
	while (front < rear)
	{
		p = Q[++front];			
		if (p->lchild == NULL&&p->rchild == NULL)
			wpl += level*p->data;
		if (p->lchild)
			Q[++rear] = p->lchild;
		if (p->rchild)
			Q[++rear] = p->rchild;
		if (front == last)		//已经到该层最右结点
		{
			level++;			//层数加1
			last = rear;		//last指向下层
		}
	}
	return wpl;
}
//孩子兄弟表示法
//数据结构为二叉树，lchild为第一个孩子，rchild为兄弟结点
void TreeTest()
{
	BiTree T;
	printf("Input:\n");
	PreCreateBiTree(T);   //1 2 4 0 0 5 0 0 3 6 0 0 7 0 0
	printf("PreOrder:\n");
	PreOrder(T);
	printf("\nleaves: %d\n", leaves(T));
	printf("height: %d\n", height(T));
}
//由二叉树返回树的叶子数
int leaves(BiTree T)
{
	if (T == NULL)
		return 0;
	if (T->lchild == NULL)	//无左子树，即无孩子，为叶结点
		return leaves(T->rchild) + 1;
	else					//返回孩子子树叶子数和兄弟子树叶子数之和
		return leaves(T->lchild) + leaves(T->rchild);
}
//由二叉树返回树的树高
int height(BiTree T)
{
	int h1, h2; 
	if (T == NULL)
		return 0;
	else	 //取子女高度+1和兄弟高度中的大者
	{
		h1 = height(T->lchild);
		h2 = height(T->rchild);
		return h1 + 1 > h2 ? h1 + 1 : h2;
	}
}
//二叉排序树
int BST_Insert(BiTree &T, int e)
{
	if (T == NULL)
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = e;
		T->lchild = NULL;
		T->rchild = NULL;
		return 1;
	}
	else if (T->data == e)		//树中已有相同元素，插入失败
		return 0;
	else if (T->data > e) 
		return BST_Insert(T->lchild, e);
	else
		return BST_Insert(T->rchild, e);
}
BiTree BST_Create(int A[], int n)
{
	BiTree T = NULL;
	for (int i = 0; i < n; i++)
		BST_Insert(T, A[i]);
		
	return T;
}
int BST_Search(BiTree T, int e, BiTree &parent, BiTree &cur)
{
	int flag = -1;  //若flag=1,则为其双亲的右孩子   flag=0，左孩子   flag=-1,没找到   flag=2,为根结点
	cur = T;
	if (cur->data == e)
		flag = 2;
	else
		while (cur&&cur->data != e)
		{
			parent = cur;
			if (cur->data > e)
			{
				cur = cur->lchild;
				flag = 0;
			}
			else
			{
				cur = cur->rchild;
				flag = 1;
			}
		}
	
	if (!cur)
		flag = -1;
	return flag;
}
void BST_Delete(BiTree &T, int e) //不能删除根节点时
{
	BiTree parent = NULL, cur = NULL;
	int flag = BST_Search(T, e, parent, cur);
	if (flag != -1)//存在该结点
	{
		printf("Search: %d, Parent: %d, flag: %d\n", cur->data, parent->data, flag);
		if (!cur->lchild && !cur->rchild) //为叶结点
		{
			if (flag)		//为右孩
				parent->rchild = NULL;
			else
				parent->lchild = NULL;

		}
		else if (cur->lchild && !cur->rchild) //右子树空，左子女填补
		{
			if (flag)
				parent->rchild = cur->lchild;
			else
				parent->lchild = cur->lchild;
		}
		else if (cur->rchild && !cur->lchild)	//左子树空，右子树填补
		{
			if (flag)
				parent->rchild = cur->rchild;
			else
				parent->lchild = cur->rchild;
		}
		else //左右子树均不空，在右子树上找中序第一个子女填补
		{
			BiTree p = cur->rchild, q = cur;
			while (p->lchild)
			{
				q = p;
				p = p->lchild;
			}
			cur->data = p->data;
			if (p->rchild)
				q->lchild = p->rchild;
			else
				q->rchild = NULL;
				
		}

	}

}
//利用中序遍历有序判断是否为二叉排序树
int BST_Judge(BiTree T)
{
	if (!T)
		return 1;
	static int pre_data = -32767;
	int left, right;	

	left = BST_Judge(T->lchild);    //判断左子树
	if (left == 0 || pre_data > T->data)
		return 0;
	pre_data = T->data;
	right = BST_Judge(T->rchild);
	return right;
}
//判断是否为平衡二叉树
//设置平衡标记balance,若为平衡二叉树，返回1，否则返回0
//height为二叉树高度，树的高度为最高子树的高度+1
//后序
void AVL_Judge(BiTree T, int &balance, int &height)
{
	int balanceLeft = 0, balanceRight = 0, heighLeft = 0, heighRight = 0;
	if (!T)
	{
		height = 0;
		balance = 1;
	}
	else if (!T->lchild && !T->rchild)//仅有根节点
	{
		height = 1;
		balance = 1;
	}
	else
	{
		AVL_Judge(T->lchild, balanceLeft, heighLeft);
		AVL_Judge(T->rchild, balanceRight, heighRight);
		height = heighLeft > heighRight ? heighLeft : heighRight + 1;
		if (abs(heighLeft - heighRight) < 2)
			balance = balanceLeft && balanceRight;
		else
			balance = 0;
	}
}
void TreeTest_BST(void)
{
	int A[] = { 4,7,5,8,6,2,3,1,9 };

	BiTree T = BST_Create(A, sizeof(A) / sizeof(A[0]));
	printf("InOrder:\n");
	InOrder(T);
	printf("\n");
	if (BST_Judge(T))
		printf("BST Judge Success\n");
	else
		printf("BST Judge Fail\n");

	int balance = 0, height=0;
	AVL_Judge(T, balance, height);
	if (balance)
		printf("AVL Judge Success\n");
	else
		printf("AVL Judge Fail\n");
	
	BiTree parent = NULL, cur = NULL;
	int flag = BST_Search(T, 5, parent, cur);
	if (flag != -1)
		printf("Search: %d, Parent: %d, flag: %d\n", cur->data, parent->data, flag);
	else
		printf("Not Found \n");

	BST_Delete(T, 7);
	printf("InOrder:\n");
	InOrder(T);
	printf("\n");
}
//层数为height的AVL树的最少结点数
int AVL_Nodes(int height)
{
	if (height == 0)
		return 0;
	else if (height == 1)
		return 1;
	else if (height == 2)
		return 2;

	return AVL_Nodes(height - 1) + AVL_Nodes(height - 2) + 1;
}