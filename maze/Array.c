#include "Array.h"
#include <malloc.h>
#include <memory.h>

Array *New_Array() {
	Array *arr = 0;
	arr = (Array *)malloc(sizeof(Array));
	arr->base = 0;
	arr->capacity = arr->usage = 0;

	return arr;
}

void Delete_Array(Array *arr) {

	if (arr->base) {
		free(arr->base);
	}
	free(arr);
}

void Array_SetSize(Array *arr, int capacity, Element data) {

	arr->capacity = capacity;
	arr->base = (Element *)realloc(arr->base, sizeof(Element)*arr->capacity);
	for (; arr->usage < arr->capacity; arr->usage++) {
		arr->base[arr->usage] = data;
	}
}

void Array_PushBack(Array *arr, Element data) {
	Iterator at = Array_End(arr);
	Array_Insert(arr, at, data);
}

void Array_Insert(Array *arr, Iterator pos, Element data) {

	int index = pos - arr->base;
	int mcount = arr->usage - index;
	if (arr->capacity == arr->usage) {
		if (arr->capacity) {
			arr->capacity *= 2;
		}
		else {
			arr->capacity = 1;
		}
		arr->base = (Element *)realloc(arr->base, sizeof(Element)*arr->capacity);
	}
	memcpy(arr->base + index + 1, arr->base + index, sizeof(Element)*mcount);
	arr->base[index] = data;
	arr->usage++;
}

void Array_SetAt(Array *arr, int index, Element data) {
	if ((index >= 0) && (index < arr->usage)) {
		arr->base[index] = data;
	}
}

Element Array_GetAt(Array *arr, int index) {
	if ((index >= 0) && (index < arr->usage)) {
		return arr->base[index];
	}
	return 0;
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

