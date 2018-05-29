#include "generating.h"
#include <Windows.h>

int init(int *x, int *y) {
	int i, j;
	Node *iter;

	width = *x;
	height = *y;
	//�̷� ũ�⸸ŭ�� �޸𸮸� �Ҵ�޽��ϴ�.
	maze = calloc(width * height, sizeof(Node));
	if (maze == NULL) return 1;

	//�̷��� �� ������ �ʱ�ȭ�մϴ�.
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {

			iter = maze + i + j * width;
			iter->c = "��";
			if (i * j % 2) { //������ ��带 ���� �ƴϰ� ����ϴ�. �̷��� �����ڸ� �κ��� �ݵ�� ���̵Ǿ�� �մϴ�.
				iter->x = i;
				iter->y = j;
				iter->dirs = 15; //�� ��帶�� �湮�� ������ �ʱ�ȭ �մϴ�. 00001111.
			}
		}
	}

	//draw();
	return 0;
}

Node *link(Node *n) {
	//�Է¹��� ���(���� ���n)�� �̿� ��带 �����մϴ�. �̿� ��带 ��ȯ�մϴ�. 
	
	int x, y; //�̿� ����� ��ǥ ���� ���� �����Դϴ�.
	char dir; //��� n�� �湮�� ������ ���� �����Դϴ�.
	Node *dest; //�̿� ��带 ����ų ������ �����Դϴ�.

	//��� n�� �߸��� ���.
	if (n == NULL) return NULL;

	//��� n�� ���� �湮�� ������ �����ִ� ���, ��� ������ �湮�� ������ �ݺ��մϴ�.
	while (n->dirs) {
		//rand()�� ���� ������ ������ ���մϴ�.
		dir = (1 << (rand() % 4));

		//������ ������ �̹� ��� n�� �湮�� ������ ���,
		if (~n->dirs & dir) continue;

		//��� n�� dir���� �湮 ǥ�ø� ����ϴ�.
		n->dirs &= ~dir;

		//������ ������ �湮�մϴ�.
		switch (dir) {
			//0001�� �������Դϴ�.
		case 1:
			if (n->y + 2 < height) {
				x = n->x;
				y = n->y + 2;
			}
			else continue;
			break;

			//0010�� �Ʒ����Դϴ�.
		case 2:
			if (n->x + 2 < width) {
				x = n->x + 2;
				y = n->y;
			}
			else continue;
			break;

			//0100�� ���Դϴ�.
		case 4:
			if (n->y - 2 >= 0) {
				x = n->x;
				y = n->y - 2;
			}
			else continue;
			break;

			//1000�� �����Դϴ�.
		case 8:
			if (n->x - 2 >= 0) {
				x = n->x - 2;
				y = n->y;
			}
			else continue;
			break;
		}

		//�湮�ؼ� ã�Ƴ� �̿� ��带 dest�� ����ϴ�.
		dest = maze + x + y * width;

		//�̿� ��尡 ������ ������ Ȯ���մϴ�.
		if (dest->c == "��") { //�̿� ��尡 ���� ���.
			
			//�̿� ��尡 �̹� �湮��(Ž����) ��쿣 �ٸ� �������� ���� ������ �ϹǷ� �ǵ��� ���ϴ�.
			if (dest->parent != NULL) continue;

			//�� ���� ���, �̿� ���� ��� n�� �����մϴ�.
			dest->parent = n;

			//�� ��带 ���θ��� ���� �����մϴ�.
			maze[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = "  ";
			//draw();

			//�̿� ����� ���� �νʴϴ�.
			maze[x + y * width].c = "  ";
			//draw();

			//�̿� ��带 ��ȯ�մϴ�.
			return dest;
		}
		else if (dest->c == "  ") { //�̿� ��尡 ���� ���.
			int ran = rand() % 10;
			
			if (!ran)
				maze[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = "  ";
			//draw();
		}
	}

	//��� ������ Ž�������� �̹� �ѹ��� �湮�� ���, �ǵ��� ���ϴ�. 
	n->c = "  ";
	//draw();
	return n->parent;
}

int setEnd() {
	
}

void draw() {
	system("cls");
	int i, j;

	//�̷θ� ����մϴ�.
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++)
			printf("%s", maze[i + j * width].c);
		printf("\n");
	}

	Sleep(100);
}