#ifndef __UTIL_H_
#define __UTIL_H_

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#include <Windows.h>
#include <conio.h>
#include <time.h>
#include "generating.h"

//편의성을 위한 함수.
void DieWithError(char* errorMessage);
int chkInvalidInput(int* x, int* y);

//게임에 사용되는 함수.
void setCursor(int x, int y);
COORD getCursor(void);
void removeCursor(void);
void showBoard(void);
void character_static(void);
void showCharacter(void);
void RemoveCharacter_Set(int x, int y);
int detect(int x, int y);

void checkMouse(int *x, int *y);
#endif
