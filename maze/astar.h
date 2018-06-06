#ifndef __ASTAR_H_
#define __ASTAR_H_

#include "main.h"
#include "gen_graph.h"

typedef struct _listNode { //리스트에 사용하는 노드 구조체
	Vertex *node;
	Vertex *parent_node;
	struct _listNode *prev;
	struct _listNode *next;
	double g_score;
	double h_score;
	double f_score;
} ListNode;

typedef struct List { //리스트 구조체
	ListNode *head;
	int cnt;
} List;

List *open_list, *closed_list;

ListNode* searchListNode(List *list, Vertex* node);
void deleteListNode(List *list, ListNode *list_node);
void addListNode(List *list, Vertex *node, Vertex *parent_node, double g_score);
void addOpenList(ListNode *list_node);
ListNode* getLastListNode(List *list);
ListNode* getLowFScoreListNode(List *list);
void addClosedList(ListNode *list_node);
void printListNode(List *list);
void astart(Vertex *start, Vertex *end);

#endif