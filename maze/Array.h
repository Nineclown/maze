#ifndef __ARRAY_H_
#define __ARRAY_H_

typedef void *Element;

typedef struct array {
	Element *base;
	int capacity;
	int usage;
}Array;

typedef Element *Iterator;

Array *New_Array();
void Delete_Array(Array *arr);
void Array_SetSize(Array *arr, int capacity, Element data);
void Array_PushBack(Array *arr, Element data);
void Array_Insert(Array *arr, Iterator pos, Element data);
void Array_SetAt(Array *arr, int index, Element data);
Element Array_GetAt(Array *arr, int index);
Iterator Array_Begin(Array *arr);
Iterator Array_End(Array *arr);
void Array_Erase(Array *arr, Iterator pos);

#endif