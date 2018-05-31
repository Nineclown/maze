#include "gen_maze.h"

int init(int x, int y) {
	int i, j;
	Node *iter;

	width = x;
	height = y;
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
			int ran = rand() % 10;	//�������� ���� �վ ��θ� ������ ����ϴ�.			
			if (!ran)
				maze[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = "  ";
			//draw();
		}
	}

	//��� ������ Ž�������� �̹� �ѹ��� �湮�� ���, �ǵ��� ���ϴ�. 
	//draw();
	return n->parent;
}

int genMaze(int x, int y) {
	Node *start, *last, *end;

	//ȣ���� �Լ����� ���ư��� ���̳����� �̷ΰ� �����˴ϴ�.
	srand(time(NULL));

	//1. �̷θ� ������ �� �ִ��� �˻��ϰ� �ʱ�ȭ �մϴ�.
	if (chkInvalidInput() != 0)
		DieWithError("error");

	//2. ���� ��带 �����մϴ�.
	start = maze + x +  y * width;
	start->parent = start;
	start->c = "��";
	last = start;
	//draw();

	//3. ���� �ս��ϴ�. ������ ���� ������ ������.
	while ((last = link(last)) != start);
	
	//4. ���.
	draw();

	return 0;
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

int chkInvalidInput() {
	int x = 0, y = 0;
	printf("input X: Y: ");
	
	//�̷��� ���� ������ 1���� Ŀ���մϴ�.
	if ((scanf_s("%d", &x) + scanf_s("%d", &y)) < 2) {
		perror("invalid maze type!\n");
		exit(1);
	}

	//�Է¹��� ũ�⸦ �������� �̷θ� �ʱ�ȭ �մϴ�.
	if (init(x, y)) {
		perror("calloc failed. parameter ");
		exit(1);
	}

	//�̷��� ����, ���� �� �ϳ��� Ȧ���� �Ǿ�� �մϴ�. ���� ǥ���ϱ� ���ؼ�.��
	if (!(width % 2) || !(height % 2)) {
		perror("faild");
		exit(1);
	}

	//�̷��� ���� ���δ� ������ �Ǿ �ȵ˴ϴ�.
	if (width <= 0 || height <= 0) {
		perror("faild");
		exit(1);
	}
	return 0;
}
