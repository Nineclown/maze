#ifndef __ARRAY_H_
#define __ARRAY_H_

//배열의 요소를 가리킨 void형 포인터 변수.
typedef void *Element;

//배열.
typedef struct array {
	Element *base; //배열은 시작주소와.
	int capacity; //배열의 크기.
	int usage; //배열의 사용 중인 요소의 index
}Array;

typedef Element *Iterator; //Element를 가리키는 포인터. iter or temp로 사용.

Array *New_Array(); //배열을 생성합니다.
void Delete_Array(Array *arr); //배열을 제거합니다.
void Array_SetSize(Array *arr, int capacity, Element data); //배열의 크기를 설정합니다.
void Array_PushBack(Array *arr, Element data); //배열의 뒤에 요소를 추가합니다.
void Array_Insert(Array *arr, Iterator pos, Element data); //배열에 요소를 추가합니다.
void Array_SetAt(Array *arr, int index, Element data); //모르겠습니다.
Element Array_GetAt(Array *arr, int index); //배열의 값을 가져옵니다.
Iterator Array_Begin(Array *arr); //배열의 첫번째 요소 값을 가져옵니다.
Iterator Array_End(Array *arr); //배열의 마지막 요소 값을 가져옵니다.
void Array_Erase(Array *arr, Iterator pos); //배열의 특정 요소를 제거하는 것 같은데요.

#endif