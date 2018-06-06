#ifndef __ASTAR_H_
#define __ASTAR_H_

#include "main.h"
#include "gen_graph.h"

typedef struct _listNode { //����Ʈ�� ����ϴ� ��� ����ü
	Vertex *node;
	Vertex *parent_node;
	struct _listNode *prev;
	struct _listNode *next;
	double g_score;
	double h_score;
	double f_score;
} ListNode;

typedef struct List { //����Ʈ ����ü
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