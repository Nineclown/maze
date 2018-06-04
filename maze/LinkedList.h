#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_

#include "MyFormat.h"

typedef struct _Node {
	struct _Node *next;
	struct _Node *prev;
	Element data;
}Node;

typedef struct _LinkedList {
	struct _Node *head;
	struct _Node *tail;
	int usage;
}LinkedList;

typedef Node *Link;


LinkedList *New_LinkedList();
void Delete_LinkedList(LinkedList *linkedlist);
void LinkedList_PushBack(LinkedList *linkedlist, Element data);
void LinkedList_Insert(LinkedList *linkedlist, Link pos, Element data);
Link LinkedList_Begin(LinkedList *linkedlist);
Link LinkedList_End(LinkedList *linkedlist);
void LinkedList_Erase(LinkedList *linkedlist, Link pos);

#endif