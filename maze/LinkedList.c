#include "LinkedList.h"
#include <malloc.h>
#include <memory.h>

Link New_Node(Element data) {
	Link link = (Link)malloc(sizeof(Node));
	link->data = data;
	link->next = link->prev = 0;
	return link;
}

void HangNode(Link link, Link pos) {
	link->prev = pos->prev;
	link->next = pos;
	pos->prev->next = link;
	pos->prev = link;
}

void DisconnectNode(Link pos) {
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
}

LinkedList *New_LinkedList() {
	LinkedList *linkedlist = 0;
	linkedlist = (LinkedList *)malloc(sizeof(LinkedList));
	linkedlist->head = New_Node(0);
	linkedlist->tail = New_Node(0);
	linkedlist->head->next = linkedlist->tail;
	linkedlist->tail->prev = linkedlist->head;
	linkedlist->usage = 0;
	return linkedlist;
}

void Delete_LinkedList(LinkedList *linkedlist) {
	Link seek = linkedlist->head;

	while (seek != linkedlist->tail)
	{
		seek = seek->next;
		free(seek->prev);
	}
	free(linkedlist->tail);
	free(linkedlist);
}

void LinkedList_PushBack(LinkedList *linkedlist, Element data) {
	LinkedList_Insert(linkedlist, linkedlist->tail, data);
}

void LinkedList_Insert(LinkedList *linkedlist, Link pos, Element data) {
	Link link = New_Node(data);
	HangNode(link, pos);
	linkedlist->usage++;
}

Link LinkedList_Begin(LinkedList *linkedlist) {
	return linkedlist->head->next;
}

Link LinkedList_End(LinkedList *linkedlist) {
	return linkedlist->tail;
}

void LinkedList_Erase(LinkedList *linkedlist, Link pos) {
	DisconnectNode(pos);
	linkedlist->usage--;
}