#ifndef __PRIQUEUE_H_
#define __PRIQUEUE_H_

#include "LinkedList.h"

typedef struct _PriorityQueue PriQueue;
typedef int(*Compare)(Element el1, Element el2);
struct _PriorityQueue
{
	LinkedList *list;
	Compare compare;
};
PriQueue *New_PriorityQueue(Compare compare);
void Delete_PriQueue(PriQueue *pq);
void PriQueue_Put(PriQueue *pq, Element data);
Element PriQueue_Get(PriQueue *pq);
int PriQueue_IsEmpty(PriQueue *pq);

#endif