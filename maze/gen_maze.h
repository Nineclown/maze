#ifndef __GEN_MAZE_H_
#define __GEN_MAZE_H_

#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "util.h"

typedef struct _node {
	int x, y; //����� ��ġ�� ��� �����Դϴ�.
	void *parent; //����� ����� ������ �����Դϴ�.
	char *c; //��尡 ������ ������ �����ϴ� �����Դϴ�. '0'�� ��, '1'�� ���Դϴ�.
	char dirs; //��尡 �湮�� ����� ��� �����Դϴ�. 
} Node;

Node *maze; //�̷�. ��� �迭�� ���������Դϴ�.
int width, height;//�̷��� ũ�⸦ ��� ���� �����Դϴ�.

int Maze_CheckInput();
int Maze_Generating(int x, int y);
int Maze_Init(int x, int y); //�̷θ� �ʱ�ȭ�ϰ� ������ �⺻ ���� �ʱ�ȭ�ϴ� �Լ��Դϴ�.
Node *Maze_Link(Node * n); //��� ���� ������ �����ϴ� �Լ��Դϴ�.
void Maze_Draw(); //�̷θ� ����ϴ� �Լ��Դϴ�.

void Maze_Draw_Debug();

void Maze_Draw_Release();

#endif