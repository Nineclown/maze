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

int GAME;

//편의성을 위한 함수.
void DieWithError(char* errorMessage);

int runMiniGame();

//게임에 사용되는 함수.
void setCursor(int x, int y);
COORD getCursor(void);
void removeCursor(void);
void showBoard(void);
void character_static(void);
void showCharacter(void);
void RemoveCharacter_Set(int x, int y);
int detect(int x, int y);

#endif
