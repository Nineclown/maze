#include "PriQueue.h"
#include <malloc.h>
#include <memory.h>

PriQueue *New_PriorityQueue(Compare compare) {
	PriQueue *pq = (PriQueue *)malloc(sizeof(PriQueue));
	pq->list = New_LinkedList();
	pq->compare = compare;
	return pq;
}

void Delete_PriQueue(PriQueue *pq) {
	Delete_LinkedList(pq->list);
	free(pq);
}

void PriQueue_Put(PriQueue *pq, Element data) {
	Link seek = LinkedList_Begin(pq->list);
	Link end = LinkedList_End(pq->list);
	for (; seek != end; seek = seek->next)
	{
		if (pq->compare(seek->data, data)>0)
		{
			break;
		}
	}
	LinkedList_Insert(pq->list, seek, data);
}

Element PriQueue_Get(PriQueue *pq) {
	Link begin;
	if (PriQueue_IsEmpty(pq))
	{
		return 0;
	}
	begin = LinkedList_Begin(pq->list);
	LinkedList_Erase(pq->list, begin);
	return begin->data;
}

int PriQueue_IsEmpty(PriQueue *pq) {
	return pq->list->usage == 0;
}