#ifndef __ARRAY_H_
#define __ARRAY_H_

//�迭�� ��Ҹ� ����Ų void�� ������ ����.
typedef void *Element;

//�迭.
typedef struct array {
	Element *base; //�迭�� �����ּҿ�.
	int capacity; //�迭�� ũ��.
	int usage; //�迭�� ��� ���� ����� index
}Array;

typedef Element *Iterator; //Element�� ����Ű�� ������. iter or temp�� ���.

Array *New_Array(); //�迭�� �����մϴ�.
void Delete_Array(Array *arr); //�迭�� �����մϴ�.
void Array_SetSize(Array *arr, int capacity, Element data); //�迭�� ũ�⸦ �����մϴ�.
void Array_PushBack(Array *arr, Element data); //�迭�� �ڿ� ��Ҹ� �߰��մϴ�.
void Array_Insert(Array *arr, Iterator pos, Element data); //�迭�� ��Ҹ� �߰��մϴ�.
void Array_SetAt(Array *arr, int index, Element data); //�𸣰ڽ��ϴ�.
Element Array_GetAt(Array *arr, int index); //�迭�� ���� �����ɴϴ�.
Iterator Array_Begin(Array *arr); //�迭�� ù��° ��� ���� �����ɴϴ�.
Iterator Array_End(Array *arr); //�迭�� ������ ��� ���� �����ɴϴ�.
void Array_Erase(Array *arr, Iterator pos); //�迭�� Ư�� ��Ҹ� �����ϴ� �� ��������.

#endif