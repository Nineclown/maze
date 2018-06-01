#include "Array.h"
#include <malloc.h>
#include <memory.h>

Array *New_Array() {
	Array *arr = 0; //코딩규칙.
	arr = (Array *)malloc(sizeof(Array));
	arr->base = 0;
	arr->capacity = arr->usage = 0;

	return arr;
}

void Delete_Array(Array *arr) {
	if (arr->base) { //배열의 요소들을 모두 free 시킨 후 배열을 free해야 합니다. 근데 얜 시작만 free한거 같네요?
		free(arr->base);
	}
	free(arr);
}

void Array_SetSize(Array *arr, int capacity, Element data) {
	arr->capacity = capacity; //배열의 크기를 설정합니다.
	arr->base = (Element *)realloc(arr->base, sizeof(Element)*arr->capacity); //크기만큼을 할당받고 그 시작주소를 base가 가리키게 합니다.
	
	//모든 배열의 요소 값을 data로 초기화 시킵니다.
	for (; arr->usage < arr->capacity; arr->usage++) { 
		arr->base[arr->usage] = data;
	}
}

void Array_PushBack(Array *arr, Element data) {
	Iterator at = Array_End(arr); //현재 배열의 마지막 요소. 
	Array_Insert(arr, at, data);
}

void Array_Insert(Array *arr, Iterator pos, Element data) {
	int index = pos - arr->base; //포인터 연산으로도 정수 값이 나오네요?
	int mcount = arr->usage - index; //
	if (arr->capacity == arr->usage) { //배열이 가득찬 상태인 경우,
		if (arr->capacity) { //배열에 이미 값이 있을 경우,
			arr->capacity *= 2; //용량 2배로1
		}
		else { //배열을 생성만 하고 set을 안했을 경우엔 0으로 초기화되어 있습니다.
			arr->capacity = 1;
		}
		// 기존의 공간보다 큰 공간을 할당해야 하므로 realloc.
		arr->base = (Element *)realloc(arr->base, sizeof(Element)*arr->capacity);
	}
	// 배열에 요소를 추가합니다.
	memcpy(arr->base + index + 1, arr->base + index, sizeof(Element)*mcount);
	arr->base[index] = data;
	arr->usage++;
}

void Array_SetAt(Array *arr, int index, Element data) {
	if ((index >= 0) && (index < arr->usage)) { //인덱스 검사.
		arr->base[index] = data; //해당 위치의 요소의 값을 변경합니다.
	}
}

Element Array_GetAt(Array *arr, int index) {
	if ((index >= 0) && (index < arr->usage)) {
		return arr->base[index];
	}
	return 0; //means NULL
}

Iterator Array_Begin(Array *arr) {
	return arr->base;
}

Iterator Array_End(Array *arr) {
	return arr->base + arr->usage;
}

void Array_Erase(Array *arr, Iterator pos) {
	int index = pos - arr->base;
	int mcount = arr->usage - index - 1;
	memcpy(pos, pos + 1, sizeof(Element)*mcount);
	arr->usage--;
}

