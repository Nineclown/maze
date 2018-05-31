#ifndef __GEN_MAZE_H_
#define __GEN_MAZE_H_

//#include "Turboc.h"
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "util.h"

typedef struct node {
	int x, y; //����� ��ġ�� ��� �����Դϴ�.
	void *parent; //����� ����� ������ �����Դϴ�.
	char *c; //��尡 ������ ������ �����ϴ� �����Դϴ�. '0'�� ��, '1'�� ���Դϴ�.
	char dirs; //��尡 �湮�� ����� ��� �����Դϴ�. 
} Node;

Node *maze; //�̷�. ��� �迭�� ���������Դϴ�.
int width, height;//�̷��� ũ�⸦ ��� ���� �����Դϴ�.

int chkInvalidInput();
int genMaze(int x, int y);
int init(int x, int y); //�̷θ� �ʱ�ȭ�ϰ� ������ �⺻ ���� �ʱ�ȭ�ϴ� �Լ��Դϴ�.
Node * link(Node * n); //��� ���� ������ �����ϴ� �Լ��Դϴ�.
void draw(); //�̷θ� ����ϴ� �Լ��Դϴ�.

#endif