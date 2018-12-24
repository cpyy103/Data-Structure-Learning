#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
bool Visited[MaxSize];		//用于遍历访问标记数组
int Queue[MaxSize], Front, Rear; //用于遍历作队列

void GraphTest()
{
	//MGraph *G1 = CreateMGraph();
	//DisplayMGraph(G1);
	ALGraph *G2 = CreateALGraph_2();
	DisplayALGraph(G2);
	BFSTraverse(G2);
	DFSTraverse(G2);
	BFSTraverse_2(G2, 0);
	DFSTraverse_2(G2, 0);

	BFS_Min_Distance(G2, 0);

	MGraph *G3 = CreateMGraph_2(1);
	DisplayMGraph(G3);
	Prim(G3);
	Dijkstra(G3, 4);
	Floyd(G3);

}

MGraph *CreateMGraph()
{
	int i, j;
	MGraph *p = (MGraph*)malloc(sizeof(MGraph));
	printf("Input vertexNum\n");
	scanf("%d", &p->vertexNum);
	for (i = 0; i < p->vertexNum; i++)	//矩阵初始化
		for (j = 0; j < p->vertexNum; j++)
			p->edge[i][j] = 0;
	printf("Input vertex:\n");
	for (i = 0; i < p->vertexNum; i++)
		scanf("%d", &p->vertex[i]);
	printf("Input edge:\n");
	for (i = 0; i < p->vertexNum; i++)
		for (j = 0; j < p->vertexNum; j++)
		{
			printf("%d - %d:\n", i, j);
			scanf("%d", &p->edge[i][j]);     //有向图无向图，权值
		}
	return p;
}
//测试用，省得每次手动输入
MGraph *CreateMGraph_2(int n)
{
	int A[6][6] = {    //65535表示无穷大，无向图
		{ 0,2,1,65535,65535,4 },
		{ 2,0,5,3,65535,65535 },
		{ 1,5,0,4,2,6 },
		{ 65535,3,4,0,7,65535 },
		{ 65535,65535,2,7,0,5 },
		{ 4,65535,6,65535,5,0 } };
	int B[6][6] = {   //有向图
		{ 0,1,65535,65535,65535,3 },
		{ 65535,0,2,65535,65535,5 },
		{ 65535,65535,0,2,65535,1 },
		{ 65535,65535,1,0,4,65535 },
		{ 2,65535,65535,1,0,65535 },
		{ 65535,2,4,5,3,0 }
	};
	int (*q)[6];
	if (n == 0) //65535表示无穷大，无向图
		q = &A[0];
	else		//有向图
		q = &B[0];
	int i, j;
	MGraph *p = (MGraph*)malloc(sizeof(MGraph));
	p->vertexNum = sizeof(A)/sizeof(A[0]);
	for (i = 0; i < p->vertexNum; i++)
		p->vertex[i] = i;
	for (i = 0; i < p->vertexNum; i++)
		for (j = 0; j < p->vertexNum; j++)
			p->edge[i][j] = q[i][j];
	return p;
}
void DisplayMGraph(MGraph *p)
{
	int i, j;
	printf("Vertex Info:\n");
	for (i = 0; i < p->vertexNum; i++)
		printf("\t%d ", p->vertex[i]);
	printf("\nEdge Info:\n");
	for (i = 0; i < p->vertexNum; i++)
	{
		for (j = 0; j < p->vertexNum; j++)
			printf("\t%d ", p->edge[i][j]);
		printf("\n");
	}
}
ALGraph *CreateALGraph()
{
	ALGraph *p;
	ArcNode *s;
	p = (ALGraph *)malloc(sizeof(ALGraph));
	int i, a, b;
	printf("Input VertexNum ArcNum\n");
	scanf("%d%d", &p->vertexNum, &p->arcNum);
	for (i = 0; i < p->vertexNum; i++)
	{	
		printf("Input vertex[%d]: ", i);
		scanf("%d", &p->vertices[i].data);
		p->vertices[i].first = NULL;
	}
	for (i = 0; i < p->arcNum; i++)
	{
		printf("Input No.%d Edge(Vi-Vj): ",i);
		scanf("%d%d", &a, &b);
		s = (ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex = b;
		s->next = p->vertices[a].first;  //头插
		p->vertices[a].first = s;

		s = (ArcNode*)malloc(sizeof(ArcNode)); //无向图
		s->adjvex = a;
		s->next = p->vertices[b].first;  
		p->vertices[b].first = s;
	}
	return p;
}
ALGraph *CreateALGraph_2()
{
	ALGraph *p;
	ArcNode *s;
	int A[] = { 1,1,1,2,6,6,7,3,3,8,4,4,4,5,9,0}; //A[i] --> B[i] 有向图
	int B[] = { 2,4,5,6,3,7,3,1,8,4,2,9,7,0,8,4};
	p = (ALGraph *)malloc(sizeof(ALGraph));
	int i;
	p->vertexNum = 10;
	p->arcNum = sizeof(A)/sizeof(A[0]);
	for (i = 0; i < p->vertexNum; i++)
	{
		p->vertices[i].data = i;
		p->vertices[i].first = NULL;
	}
	
	for (i = 0; i < p->arcNum; i++)
	{
		s = (ArcNode*)malloc(sizeof(ArcNode));
		s->adjvex = B[i];
		s->next = p->vertices[A[i]].first;  
		p->vertices[A[i]].first = s;

	}
	return p;
}
void DisplayALGraph(ALGraph *p)
{
	ArcNode *s;
	for (int i = 0; i < p->vertexNum; i++)
	{
		printf("No.%d : %d ", i, p->vertices[i].data);
		s = p->vertices[i].first;
		while (s)
		{
			printf("-> %d ", s->adjvex);
			s = s->next;
		}
		printf("\n");
		
	}
}
int FirstNeighbor(ALGraph *p, int v)
{
	ArcNode *s = p->vertices[v].first;
	if (s)
		return s->adjvex;
	else
		return -1;
}
int NextNeighbor(ALGraph *p, int v, int n)
{
	ArcNode *s = p->vertices[v].first;
	while (s->adjvex != n)
		s = s->next;
	s = s->next;
	if (s)
		return s->adjvex;
	else
		return -1;
}
void BFSTraverse(ALGraph *G)
{
	int i;
	for (i = 0; i < G->vertexNum; i++)
		Visited[i] = false;
	Front = -1;  //定义的队列全局变量
	Rear = -1;
	printf("BFS: \n");
	for (i = 0; i < G->vertexNum; i++) //从第0开始遍历,以防图为非连通图
		if (!Visited[i])
			BFS(G, i);
	printf("\n");
}
void BFS(ALGraph *G, int v)
{
	int i, j;
	visit(G, v);
	Visited[v] = 1;
	Queue[++Rear] = v;	//入队
	while (Front < Rear)
	{
		i = Queue[++Front];
		for (j = FirstNeighbor(G, i); j >= 0; j = NextNeighbor(G, i, j))
			if (!Visited[j])
			{
				visit(G, j);
				Visited[j] = 1;
				Queue[++Rear] = j;
			}
	}
}
void DFSTraverse(ALGraph *G)
{
	int i;
	printf("DFS:\n");
	for (i = 0; i < G->vertexNum; i++)
		Visited[i] = false;
	for (i = 0; i < G->vertexNum; i++)
		if (!Visited[i])
			DFS(G, i);
	printf("\n");
}
void DFS(ALGraph *G, int v)
{
	int i;
	visit(G, v);
	Visited[v] = 1;
	for (i = FirstNeighbor(G, v); i >= 0; i = NextNeighbor(G, v, i))
		if (!Visited[i])
			DFS(G, i);
}
void visit(ALGraph *G, int v)
{
	printf("%d ", G->vertices[v].data);
}
void BFS_Min_Distance(ALGraph *G, int v)
{
	int d[MaxSize], i, j;
	for (i = 0; i < G->vertexNum; i++)
	{
		d[i] = 65535;
		Visited[i] = 0;
	}
	Visited[v] = 1;
	d[v] = 0;
	Front = -1;
	Rear = -1;
	Queue[++Rear] = v;
	while (Front < Rear)
	{
		i = Queue[++Front];
		for (j = FirstNeighbor(G, i); j >= 0; j = NextNeighbor(G, i, j))
			if (!Visited[j])
			{
				Visited[j] = 1;
				d[j] = d[i] + 1;
				Queue[++Rear] = j;
			}
	}
	printf("BFS Min Distance:\nvertex:");
	for (i = 0; i < G->vertexNum; i++)
		printf("\t%d", i);
	printf("\ndict:");
	for (i = 0; i < G->vertexNum; i++)
		printf("\t%d", d[i]);
	printf("\n--------------------\n");
}
void BFSTraverse_2(ALGraph *G, int source)
{
	bool visitedd[MaxSize];
	int i, front = -1, rear = -1, Q[MaxSize];
	ArcNode *cur;
	for (i = 0; i < G->vertexNum; i++)
		visitedd[i] = false;
	printf("BFS_2:\n");
	printf("%d ", G->vertices[source].data);
	visitedd[source] = 1;
	Q[++rear] = source;
	while (front < rear)
	{
		i = Q[++front];
		cur = G->vertices[i].first;
		while (cur)
		{
			if (!visitedd[cur->adjvex])
			{
				printf("%d ", G->vertices[cur->adjvex].data);
				visitedd[cur->adjvex] = 1;
				Q[++rear] = cur->adjvex;
				cur = cur->next;
			}
			else
				cur = cur->next;
		}
	}
	printf("\n");
}
void DFSTraverse_2(ALGraph *G, int source)
{
	printf("DFS_2:\n");
	DFSTraverse2(G, source);
	printf("\n");
}
void DFSTraverse2(ALGraph *G, int source)
{
	static bool visitedd[MaxSize] = { 0 };
	ArcNode *cur;
	printf("%d ", G->vertices[source].data);
	visitedd[source] = 1;
	cur = G->vertices[source].first;
	while (cur)
	{
		if (!visitedd[cur->adjvex])
			DFSTraverse2(G, cur->adjvex);
		cur = cur->next;
	}
}
//最小生成树
void Prim(MGraph *G)
{
	printf("Prim:\n");
	int min, i, j, k;
	int path[MaxSize];   //表示从哪个结点过来
	int dict[MaxSize];  //值为0时，表示已加到生成树中，65535为不连通，其余为权值
	path[0] = 0;
	dict[0] = 0;
	for (i = 1; i < G->vertexNum; i++)  //初始化，从0号开始
	{
		dict[i] = G->edge[0][i];   
		path[i] = 0;
	}
	for (i = 1; i < G->vertexNum; i++)
	{
		min = 65535;
		j = 0;
		k = 0;	
		while (j < G->vertexNum)		//找顶点
		{
			if (dict[j] != 0 && dict[j] < min) //找到不在生成树中且权值最小的
			{
				min = dict[j];
				k = j;
			} 
			j++;
		}
		printf("\t%d - %d\n", path[k], k);
		dict[k] = 0;//加入生成树	
		for (j = 0; j < G->vertexNum; j++)		//更新数组
		{
			if (dict[j] != 0 && G->edge[k][j] < dict[j]) //如果加入该顶点使权值变小
			{
				dict[j] = G->edge[k][j];
				path[j] = k;
			}
		}
	}
}
//最短路径
void Dijkstra(MGraph *G, int v)
{
	int dist[MaxSize] = { 0 };	//源点到其他顶点的最短路径长度
	int path[MaxSize] = { 0 };	//源点到i之间的最短路径的i的前驱结点
	int s[MaxSize] = { 0 };		//表示是否加入到路径中
	int i, j, min, u;
	
	for (i = 0; i < G->vertexNum; i++)	//初始化
	{
		dist[i] = G->edge[v][i];
		s[i] = 0;
		if (G->edge[v][i] < 65535)  //两结点连通
			path[i] = v;
		else
			path[i] = -1;
	}
	s[v] = 1;		//源点加入
	path[v] = -1;
	for (i = 0; i < G->vertexNum; i++)
	{
		min = 65535;
		for (j = 0; j < G->vertexNum; j++)  //找到剩余结点中距离最小的结点
		{
			if (s[j] == 0 && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		}
		s[u] = 1;	//加入路径
		for (j = 0; j < G->vertexNum; j++)
		{
			if (s[j] == 0 && dist[u] + G->edge[u][j] < dist[j]) //更新数组，如果新加入的结点到其他结点的路径变短了
			{
				dist[j] = dist[u] + G->edge[u][i];
				path[j] = u;   //较短的路径，从u过来
			}
		}
	}
	printf("\nDijkstra:\nvertex:");
	for (i = 0; i < G->vertexNum; i++)
		printf("\t%d", i);
	printf("\ndict:");
	for (i = 0; i < G->vertexNum; i++)
		printf("\t%d", dist[i]);
	printf("\npath:");
	for (i = 0; i < G->vertexNum; i++)
		printf("\t%d", path[i]);
	printf("\n");

}
void Floyd(MGraph *G)
{
	int A[MaxSize][MaxSize];
	int path[MaxSize][MaxSize];		//用于保存路径
	int i, j, k;
	for (i = 0; i < G->vertexNum; i++)	//初始化
		for (j = 0; j < G->vertexNum; j++)
		{
			A[i][j] = G->edge[i][j];
			path[i][j] = -1;
		}

	for(k=0;k<G->vertexNum;k++)			//k可以从1开始
		for(i=0;i<G->vertexNum;i++)
			for(j=0;j<G->vertexNum;j++)
				if (A[i][j] > A[i][k] + A[k][j]) //如果i到j的距离比i经过k到j的距离小，更新距离数据，并存储路径
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = k;
				}


	printf("\nFloyd:\nA:\n");
	for (i = 0; i < G->vertexNum; i++)
		printf("\t%d", i);
	printf("\n   ________________________________________________\n");
	for (i = 0; i < G->vertexNum; i++)
	{
		printf("%d |", i);
		for (j = 0; j < G->vertexNum; j++)
			printf("\t%d", A[i][j]);
		printf("\n");
	}
	printf("path:\n");
	for (i = 0; i < G->vertexNum; i++)
		printf("\t%d", i);
	printf("\n   ________________________________________________\n");
	for (i = 0; i < G->vertexNum; i++)
	{
		printf("%d |", i);
		for (j = 0; j < G->vertexNum; j++)
			printf("\t%d", path[i][j]);
		printf("\n");
	}
}