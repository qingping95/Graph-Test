#include <iostream>
#include <stdio.h>
#include <cstring>
////test GitHub

#pragma warning(disable:4996)

using namespace std;
#define MAX 11111
struct Edge
{
	int to;
	int next;
	Edge() { to = -1; next = -1; }
};

void displayStar()
{
	printf("***************************************************\n");
}

struct Graph
{
	int vertexNum;
	int edgeGraphIdx;
	int edgeTreeIdx;
	int edgeNum;
	bool *vis;
	Edge *G;
	int *GHead;

	Edge *T;
	int *THead;

	Graph()//构造函数
	{
		vertexNum = -1;
		edgeTreeIdx = 0;
		edgeGraphIdx = 0;
		edgeNum = -1;
		T = NULL;
		G = NULL;
		GHead = NULL;
		THead = NULL;
		vis = NULL;
	}
	~Graph()
	{
		delete vis;
		delete G;
		delete T;
		delete GHead;
		delete THead;
	}

	void GraphInit()
	{
		vertexNum = -1;
		edgeTreeIdx = 0;
		edgeGraphIdx = 0;
		edgeNum = -1;
		T = NULL;
		G = NULL;
		GHead = NULL;
		THead = NULL;
		vis = NULL;
	}
	void setVertexNum(int num)//设置节点数，并且初始化Head数组
	{
		vertexNum = num;
		delete GHead;
		delete THead;
		delete vis;
		GHead = new int[num + 1];
		THead = new int[num + 1];
		vis = new bool[num + 1];
		memset(GHead, -1, (num + 1)*sizeof(int));
	}
	void setEdgeNum(int num)//设置边数，为Edge申请空间
	{
		edgeNum = num;
		delete G;
		G = new Edge[num * 2];
	}
	int getVertexNum()
	{
		return vertexNum;
	}
	int getEdgeNum()
	{
		return edgeNum;
	}


	void initTree()
	{
		edgeTreeIdx = 0;
		delete T;
		memset(THead, -1, (vertexNum + 1)*sizeof(int));
		T = new Edge[vertexNum - 1];
	}
	
	void checkdfs(int s)
	{
		vis[s] = true;
		for (int i = GHead[s]; i != -1; i = G[i].next)
		{
			int v = G[i].to;
			if (vis[v]) continue;
			checkdfs(v);
		}
	}
	bool CheckIsConnect(int s)
	{
		memset(vis, 0, (vertexNum + 1)*sizeof(bool));
		checkdfs(s);
		for (int i = 1; i <= vertexNum; i++)
		{
			if (!vis[i]) return false;
		}
		return true;
	}

	void addGraphEdge(int u, int v)
	{
		G[edgeGraphIdx].to = v;
		G[edgeGraphIdx].next = GHead[u];
		GHead[u] = edgeGraphIdx++;
	}
	void Graphdfs(int s)
	{
		vis[s] = true;
		printf("%d ", s);
		for (int i = GHead[s]; i != -1; i = G[i].next)
		{
			int v = G[i].to;
			if (vis[v]) continue;
			addTreeEdge(s, v);
			Graphdfs(v);
		}
	}
	void GraphDFSAndOutput(int s)
	{
		memset(vis, 0, (vertexNum + 1)*sizeof(bool));
		initTree();
		displayStar();
		printf("深度优先遍历序列为： ");
		Graphdfs(s);
		for (int i = 1; i <= vertexNum;i++)
			if(!vis[i])
				Graphdfs(i);
		printf("\n");
		displayStar();
		printf("\n");
	}
	void GraphDFSNoRecusive(int s)
	{
		displayStar();
		printf("深度优先遍历序列为(非递归)： ");
		int Stk[MAX];
		int tail = 0;
		memset(vis, 0, (vertexNum + 1)*sizeof(bool));
		Stk[tail++] = s;
		printf("%d ", s);
		vis[s] = true;
		while (tail > 0)
		{
			int cur = Stk[tail - 1];
			bool success = false;
			for (int i = GHead[cur]; i != -1; i = G[i].next)
			{
				int v = G[i].to;
				if (vis[v]) continue;
				printf("%d ", v);
				vis[v] = true;
				Stk[tail++] = v;
				success = true;
				break;
			}
			if (!success)
				tail--;
			if (tail == 0)
			{
				for (int i = 1; i <= vertexNum; i++)
				{
					if (vis[i]) continue;
					Stk[tail++] = i;
					printf("%d ", i);
					vis[i] = true;
					break;
				}
			}
		}
		printf("\n");
		displayStar();
		printf("\n");
	}
	void GraphBFSAndOutput(int s)
	{
		int que[MAX];
		int front = 0, tail = 0;
		memset(vis, 0, (vertexNum + 1)*sizeof(bool));
		que[tail++] = s;
		vis[s] = true;

		initTree();
		displayStar();
		printf("宽度优先遍历的序列： ");

		while (front < tail)
		{
			int cur = que[front++];
			printf("%d ", cur);
			for (int i = GHead[cur]; i != -1; i = G[i].next)
			{
				int v = G[i].to;
				if (vis[v]) continue;
				addTreeEdge(cur, v);
				vis[v] = true;
				que[tail++] = v;
			}
			if ( front >= tail )
			{
				for (int i = 1; i <= vertexNum; i++)
				{
					if (vis[i]) continue;
					que[tail++] = i;
					vis[i] = true;
					break;
				}
			}
		}

		printf("\n");
		displayStar();
		printf("\n");

	}

	void inputEdge(int flag)
	{
		for (int i = 1; i <= edgeNum; i++)
		{
			printf("请输入第%d条边（用空格隔开）： ", i);
			int u, v;
			//scanf("%d%d", &u, &v);
			cin >> u >> v;
			this->addGraphEdge(u, v);
			if(flag) this->addGraphEdge(v, u);
		}
	}

	void addTreeEdge(int u, int v)
	{
		T[edgeTreeIdx].to = v;
		T[edgeTreeIdx].next = THead[u];
		THead[u] = edgeTreeIdx++;
	}
	void Treedfs(int s)
	{
		vis[s] = true;
		for (int i = THead[s]; i != -1; i = T[i].next)
		{
			int v = T[i].to;
			if (vis[v]) continue;
			printf("(%d,%d) ", s, v);
			Treedfs(v);
		}
	}
	void TreeDFSAndOutput(int s)
	{
		displayStar();
		printf("此时生成树的边集为： \n");
		memset(vis, 0, (vertexNum + 1)*sizeof(bool));
		Treedfs(s);
		printf("\n");
		displayStar();
		printf("\n");

	}
	void TreeBFSAndOutput(int s)
	{
		int que[MAX];
		int front = 0, tail = 0;
		memset(vis, 0, (vertexNum + 1)*sizeof(bool));
		que[tail++] = s;
		vis[s] = true;
		displayStar();

		printf("此时生成树的边集： \n");

		while (front < tail)
		{
			int cur = que[front++];
			for (int i = THead[cur]; i != -1; i = T[i].next)
			{
				int v = T[i].to;
				if (vis[v]) continue;
				printf("%d->%d\n", cur, v);
				vis[v] = true;
				que[tail++] = v;
			}
		}

		printf("\n");
		displayStar();
		printf("\n");
	}
	void showGraphAdjustList()
	{
		displayStar();
		printf("该图的邻接表如下：\n");
		for (int u = 1; u <= vertexNum; u++)
		{
			for (int i = GHead[u]; i != -1; i = G[i].next)
			{
				int v = G[i].to;
				printf("%d->%d ", u, v);
			}
			printf("\n");
		}
		displayStar();
	}
	void showTreeAdjustList()
	{
		displayStar();
		printf("该树的邻接表如下：\n");
		for (int u = 1; u <= vertexNum; u++)
		{
			for (int i = THead[u]; i != -1; i = T[i].next)
			{
				int v = T[i].to;
				printf("%d->%d ", u, v);
			}
			printf("\n");
		}
		displayStar();
	}
};
int main()
{
	//freopen("D:\in.txt", "r", stdin);
	//freopen("D:/out.txt", "w", stdout);
	int vertexNum, edgeNum;
	Graph graph;
	int cas = 0;
	displayStar();
	cout << "*\t     实验五：图及其应用\t                  *" << endl;
	displayStar();
	printf("* 1.构建一个图。\t\t\t          *\n");
	printf("* 2.查看图的深度优先遍历序列以及深度优先生成树。  *\n");
	printf("* 3.查看图的深度优先遍历序列(选做，非递归)。      *\n");
	printf("* 4.查看图的宽度优先遍历序列以及宽度优先生成树。  *\n");
	printf("* 5.查看图的邻接表。                              *\n");
	printf("* 6.退出。                                        *\n");
	displayStar();
	cin >> cas;
	while (cas != 6) {
		switch (cas)
		{
		case 1:
		{
			graph.GraphInit();
			printf("请输入顶点数和边数：（用空格隔开）\n");
			cin >> vertexNum >> edgeNum;
			graph.setVertexNum(vertexNum);
			graph.setEdgeNum(edgeNum);
			printf("(选做)请选择：\n1.无向图。\n2.有向图。\n");
			int flag = 0;
			scanf("%d", &flag);
			if (flag == 2) flag = 0;
			graph.inputEdge(flag);
			
			printf("建立成功！\n");
			system("pause");
			break;
		}
		case 2:
		{
			printf("请输入源点的节点编号： ");
			int s;
			cin >> s;
			graph.GraphDFSAndOutput(s);
			if (!graph.CheckIsConnect(1))
			{
				printf("您输入的图以该节点为起点的图不联通！无法生成树。\n");
			}
			else
			{
				graph.TreeDFSAndOutput(s);
			}
			system("pause");
			break;
		}
		case 3:
		{
			printf("请输入源点的节点编号： ");
			int s;
			cin >> s;
			graph.GraphDFSNoRecusive(s);
			system("pause");
			break;
		}
		case 4:
		{
			printf("请输入源点的节点编号： ");
			int s;
			cin >> s;
			graph.GraphBFSAndOutput(s);
			if (!graph.CheckIsConnect(1))
			{
				printf("您输入的图以该节点为起点的图不联通！无法生成树。\n");
			}
			else
			{
				graph.TreeDFSAndOutput(s);
			}
			system("pause");
			break;
		}
		case 5:
		{
			graph.showGraphAdjustList();
			system("pause");
			break;
		}
		}


		system("CLS");
		displayStar();
		cout << "*\t     实验五：图及其应用\t                  *" << endl;
		displayStar();
		printf("* 1.构建一个图。\t\t\t          *\n");
		printf("* 2.查看图的深度优先遍历序列以及深度优先生成树。  *\n");
		printf("* 3.查看图的深度优先遍历序列(选做，非递归)。      *\n");
		printf("* 4.查看图的宽度优先遍历序列以及宽度优先生成树。  *\n");
		printf("* 5.查看图的邻接表。                              *\n");
		printf("* 6.退出。                                        *\n");
		displayStar();
		cin >> cas;
	}
	system("CLS");
	displayStar();
	cout << "\n\n\n\n\n\n\n";
	cout << "\t\t感谢您的使用！再见！";
	cout << "\n\n\n\n\n\n\n";
	displayStar();
	system("pause");
	return 0;
}