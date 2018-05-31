#include "gen_graph.h"


int initMaze() {
	int i = 0, j = 0;
	NUM = 1;
	//�ʱ�ȭ.
	Node * iter;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			iter = maze + i + j * width;
			if (iter->c != "��") {
				findDirection(iter);
			}
		}
	}

	return 0;
}

int findDirection(Node *n) {
	char dirs = 0;
	int count = 0;
	//������ 0001
	if (maze[n->x + (n->y - 1) * width].c != "��") {
		dirs += 1;
		count++;
	}
	//�Ʒ���
	if (maze[n->x - 1 + n->y * width].c != "��") {
		dirs += 2;
		count++;
	}
	//����
	if (maze[n->x + (n->y + 1) * width].c != "��") {
		dirs += 4;
		count++;
	}
	//����
	if (maze[n->x + 1 + n->y * width].c != "��") {
		dirs += 8;
		count++;
	}
	n->dirs = dirs;

	if (count >= 3 || count <= 1) {
		//�� ���� �ݵ�� vertex�� ��������� �Ѵ�.
		n->c = "��";

		//Graph_AddVertex(graph, (char*)NUM++);
	}

	return 0;
}