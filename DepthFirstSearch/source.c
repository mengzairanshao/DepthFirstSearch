// /*
// * @Author: han
// * @Date:   2017-05-06 10:22
// * @Last Modified by:   han
// * @Last Modified time: 2017-05-08 10:51:29
// */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 8

/***********************************************************/
/*
*	function:构建邻接表,测试深度优先搜索
*/
/**********************************************************/

/*表节点*/
typedef struct LinkNode
{
	int index; /*顶点*/
	int data; /*权值*/
	struct LinkNode* next;/*下一个表节点*/
} LinkNode, *LinkPtr;

/*顶点*/
typedef struct VexNode
{
	int m; /*顶点个数*/
	LinkPtr* first; /*表头结点数组*/
} VexNode;

/**
 * [depthFirstSearch 深度优先搜索]
 * @param  Vex    [邻接表]
 * @param  mState [访问状态表,记录节点是否被访问]
 * @param  start  [开始节点,从哪个节点开始访问]
 * @param  end    [结束节点]
 * @return        [是否存在通路]
 */
bool depthFirstSearch(VexNode* Vex, int *mState, int start, int end)
{
	int n = 0;	/*记录该访问单链表中的哪一个(访问状态表中为零的节点)*/
	LinkPtr temp = NULL;	/*临时节点*/
	/*找到单链表对应的状态表为零的节点*/
	for (temp = Vex->first[start] , n = 0; temp; temp = temp->next , n++)
	{
		if (*(mState + Vex->m*start + n) == 0)
		{
//			printf("%d->", start);
			*(mState + Vex->m*start + n) = 1;/*标记该节点已访问过*/
			/*判断是否是寻找的节点*/
			if (temp->index == end)
			{
				printf("\n%d<-", temp->index);
				return true;
			}
			/*已访问过的节点不在访问*/
			if (*(mState + Vex->m*(temp->index) + 0)==0 && depthFirstSearch(Vex, mState, temp->index, end))
			{
				printf("%d<-", temp->index);
				return true;
			}
		}
	}
	return false;
}

/**
* [adjList 邻接表构建]
* @param Vex    [存储顶点信息的数组(即邻接表)]
* @param m      [存储顶点和边集信息的矩阵]
*/
void adjList(VexNode* Vex, int* m)
{
	int length = Vex->m;
	LinkNode* link_node = NULL; /*表节点*/
	LinkNode* first_node = NULL;/*头结点*/
	/*循环行*/
	for (int i = 0; i < length; i++)
	{
		link_node = malloc(sizeof(LinkNode));
		link_node->index = i;
		link_node->data = -1;
		link_node->next = NULL;
		/*循环列*/
		for (int j = 0; j < length; j++)
		{
			/*保存头结点*/
			if (j == 0)
				first_node = link_node;
			/*遇到非零的元素,将表节点保存到头结点后的最后一个位置*/
			if ((*(m + length * i + j)) != 0)
			{
				LinkNode* newNode = NULL;
				newNode = malloc(sizeof(LinkNode));
				newNode->index = j;
				newNode->data = *(m + length * i + j);
				newNode->next = NULL;
				link_node->next = newNode;
				link_node = newNode;
			}
		}
		/*头结点赋值保存到数组中*/
		Vex->first[i] = first_node->next;
		first_node = NULL;
	}
}

/**
* [printAdjList 打印邻接表]
* @param Vex    [邻接表]
*/
void printAdjList(VexNode* Vex)
{
	LinkNode* temp = NULL;
	/*循环遍历数组中的所有头结点*/
	for (int i = 0; i < Vex->m; i++)
	{
		temp = Vex->first[i];
		/*遍历单链表*/
		for (; temp != NULL;)
		{
			if (temp->index != -1)
			{
				printf("%d->", temp->index);
			}
			temp = temp->next;
		}
		printf("NULL\n");
	}
}

int main()
{
	char Vex[N] = {'A','B','C','D','E','F','G','H'};
	int m[N][N] = {
		{0,1,0,1,1,0,0,0},
		{1,0,1,0,1,0,0,0},
		{0,1,0,0,0,1,0,0},
		{1,0,0,0,0,0,1,0},
		{1,1,0,0,0,0,1,0},
		{0,0,1,0,0,0,0,0},
		{0,0,0,1,1,0,0,1},
		{0,0,0,0,0,0,1,0}
	};
	int mState[N][N] = {0};
	VexNode* mVex = NULL;
	mVex = malloc(sizeof(VexNode));
	mVex->m = N;
	mVex->first = malloc(N * sizeof(LinkPtr));
	for (int i = 0; i < N; i++)
		*(mVex->first + i) = NULL;
	adjList(mVex, m);
	printAdjList(mVex);
	depthFirstSearch(mVex, mState, 0, 5);
	printf("%d", 0);
	return 0;
}
