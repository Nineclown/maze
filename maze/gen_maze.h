#ifndef __GEN_MAZE_H_
#define __GEN_MAZE_H_

#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "util.h"

typedef struct _node {
	int x, y; //노드의 위치를 담는 변수입니다.
	void *parent; //연결된 노드의 포인터 변수입니다.
	char *c; //노드가 벽인지 길인지 구분하는 변수입니다. '0'은 길, '1'은 벽입니다.
	char dirs; //노드가 방문한 기록을 담는 변수입니다. 
} Node;

Node *maze; //미로. 노드 배열인 전역변수입니다.
int width, height;//미로의 크기를 담는 전역 변수입니다.

int Maze_CheckInput();
int Maze_Generating(int x, int y);
int Maze_Init(int x, int y); //미로를 초기화하고 노드들의 기본 값을 초기화하는 함수입니다.
Node *Maze_Link(Node * n); //노드 간의 연결을 설정하는 함수입니다.
void Maze_Draw(); //미로를 출력하는 함수입니다.

void Maze_Draw_Debug();

void Maze_Draw_Release();

#endif