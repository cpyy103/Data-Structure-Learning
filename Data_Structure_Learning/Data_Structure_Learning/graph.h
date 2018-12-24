#ifndef GRAPH_H
#define GRAPH_H
#define MaxSize 50
//邻接矩阵
typedef struct {
	int vertex[MaxSize];		//顶点表（权值）
	int edge[MaxSize][MaxSize];	//边表
	int vertexNum, arcNum;	//顶点数，弧数
}MGraph; 

//邻接表
typedef struct ArcNode {		//边表结点
	int adjvex;					//该弧指向的顶点的位置
	struct ArcNode *next;		//指向下一条弧的指针
	//int info;					//权值
}ArcNode;
typedef struct VNode {			//顶点表结点
	int data;					//顶点数据
	ArcNode *first;				//指向第一条依附于该顶点的弧的指针
}VNode, AdjList[MaxSize];
typedef struct {
	AdjList vertices;			//邻接表
	int vertexNum, arcNum;		//顶点数，弧数
}ALGraph;

//十字链表
typedef struct ArcNode_2 {					//边表
	int tailvex, headvex;					//弧的尾头结点
	struct ArcNode_2 *taillink, *headlink;	//指向弧尾相同，弧头相同的结点
	//int info;									
}ArcNode_2;
typedef struct VNode_2 {				//顶点表
	int data;	
	ArcNode_2 *firstin, *firstout;		//第一条入弧和出弧
}VNode_2;								
typedef struct {
	VNode_2 xlist[MaxSize];				//邻接表
	int vertexNum, arcNum;
}GLGraph;

//邻接多重表
typedef struct ArcNode_3 {				//边表
	bool mark;							//访问标记
	int ivex, jvex;						//该弧的两个结点
	struct ArcNode_3 *ilink, *jlink;	//两个顶点的下一条边
	//int info							
}ArcNode_3;
typedef struct VNode_3 {				//顶点表
	int data;							
	ArcNode_3 *firstedge;				//第一条依附该顶点的边
}VNode_3;
typedef struct {
	VNode_3 adjmulist[MaxSize];
	int vertexNum, arcNum;		
}AMLGraph;

void GraphTest(void);
MGraph *CreateMGraph(void);
MGraph *CreateMGraph_2(int n);
void DisplayMGraph(MGraph *p);
ALGraph *CreateALGraph(void);
ALGraph *CreateALGraph_2(void);		
void DisplayALGraph(ALGraph *p);



int FirstNeighbor(ALGraph *p, int v);
int NextNeighbor(ALGraph *p, int v, int n);
void BFSTraverse(ALGraph *G);
void BFS(ALGraph *G, int v);
void DFSTraverse(ALGraph *G);
void DFS(ALGraph *G, int v);
void visit(ALGraph *G, int v);

void BFSTraverse_2(ALGraph *G, int source);
void DFSTraverse_2(ALGraph *G, int source);
void DFSTraverse2(ALGraph *G, int source);

void BFS_Min_Distance(ALGraph *G, int v);

void Prim(MGraph *G);
void Dijkstra(MGraph *G, int v);
void Floyd(MGraph *G);
#endif // !GRAPH_H

