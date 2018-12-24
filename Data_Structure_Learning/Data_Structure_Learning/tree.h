#ifndef TREE_H
#define TREE_H

#include "stack_queue.h"
#include "list.h"
#define MaxSize 50
//二叉树 
typedef struct BiTNode {
	int data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
//链表
typedef struct Node{
	BiTree p;
	struct Node *next;
}Node, *pNode;
//线索二叉树
typedef struct ThreadNode {
	int data;
	struct ThreadNode *lchild, *rchild;
	int ltag, rtag;						//左右孩子线索标志
}ThreadNode, *ThreadTree;
//双亲表示法
typedef struct {
	int data;
	int parent;
}PTNode;
typedef struct {
	PTNode nodes[50];	//双亲表示
	int n;				//节点数
}PTree;
//孩子兄弟表示法
typedef struct CSNode{
	int data;
	struct CSNode *firstchild, *nextsibling;	//第一个孩子和右兄弟指针
}CSNode, *CSTree;


void BiTreeTest(void);

BiTree LevelCreateBiTree(int A[], int n);		//层序建树
void PreCreateBiTree(BiTree &p);				//先序建树
int FindCommAncestor(SqList T, int i, int j);	//寻找公共祖先
void SearchAncestor(BiTree T, int e);			//寻找祖先结点
int FindCommAnsestor_2(BiTree T, int a, int b);//寻找公共祖先
int BiTreeDepth(BiTree T);					//树深
void BiTreeDepthWidth(BiTree T);					//树深树宽
BiTree PreInCreateBiTree(int A[], int B[], int a1, int a2, int b1, int b2); //已知先序中序建树
void WPL(BiTree T);				//带权路径长度
int wplPreOrder(BiTree T, int depth);
int wplLevelOrder(BiTree T);

void BiTreeInfo(BiTree p);
void PreOrder(BiTree p);
void PreOrder(BiTree p);
void InOrder(BiTree p);
void InOrder_2(BiTree p);
void PostOrder(BiTree p);
void PostOrder_2(BiTree p);
void LevelOrder(BiTree p);
void LevelOrder_2(BiTree p);
void visit(BiTree p);

//孩子兄弟表示，二叉树结构
void TreeTest(void);
int leaves(BiTree T);
int height(BiTree T);

//二叉排序树
void TreeTest_BST(void);
BiTree BST_Create(int A[], int n);
int BST_Insert(BiTree &T, int e);
int BST_Search(BiTree T, int e, BiTree &parent, BiTree &cur);
void BST_Delete(BiTree &T, int e);
int BST_Judge(BiTree T);

void AVL_Judge(BiTree T, int &balance, int &height);//判断是否为平衡二叉树
int AVL_Nodes(int height);

#endif
