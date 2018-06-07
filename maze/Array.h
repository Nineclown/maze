#ifndef __ARRAY_H_
#define __ARRAY_H_

#include "MyFormat.h"
//�迭�� ��Ҹ� ����Ų void�� ������ ����.

//�迭.
typedef struct _array {
	Element *base; //�迭�� �����ּҿ�.
	int capacity; //�迭�� ũ��.
	int usage; //�迭�� ��� ���� ����� index
}Array;

Array *New_Array(); //�迭�� �����մϴ�.
void Delete_Array(Array *arr); //�迭�� �����մϴ�.
void Array_SetSize(Array *arr, int capacity, Element data); //�迭�� ũ�⸦ �����մϴ�.
int Array_PushBack(Array *arr, Element data); //�迭�� �ڿ� ��Ҹ� �߰��մϴ�.
int Array_Insert(Array *arr, Iterator pos, Element data); //�迭�� ��Ҹ� �߰��մϴ�.
void Array_SetAt(Array *arr, int index, Element data);
Element Array_GetAt(Array *arr, int index); //�迭�� ���� �����ɴϴ�.
Iterator Array_Begin(Array *arr); //�迭�� ù��° ��� ���� �����ɴϴ�.
Iterator Array_End(Array *arr); //�迭�� ������ ��� ���� �����ɴϴ�.
void Array_Erase(Array *arr, Iterator pos); //�迭�� Ư�� ��Ҹ� ����
int Array_IsEmpty(Array * arr);

#endif