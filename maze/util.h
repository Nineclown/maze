#ifndef __UTIL_H_
#define __UTIL_H_

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#include <Windows.h>
#include <conio.h>
#include <time.h>
#include "gen_maze.h"

//���Ǽ��� ���� �Լ�.
void DieWithError(char* errorMessage);

int runMiniGame();

//���ӿ� ���Ǵ� �Լ�.
void setCursor(int x, int y);
COORD getCursor(void);
void removeCursor(void);
void showBoard(void);
void character_static(void);
void showCharacter(void);
void RemoveCharacter_Set(int x, int y);
int detect(int x, int y);

#endif
