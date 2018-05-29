#include "generating.h"
#include <Windows.h>
int init(int *x, int *y) {
	int i, j;
	Node *n;

	width = *x;
	height = *y;
	//Allocate memory for maze
	nodes = calloc(width * height, sizeof(Node));
	if (nodes == NULL) return 1;

	//Setup crucial nodes
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			n = nodes + i + j * width;
			if (i * j % 2) {
				n->x = i;
				n->y = j;
				n->dirs = 15; //Assume that all directions can be explored (4 youngest bits set)
				n->c = '0';
			}
			else n->c = '1'; //Add walls between nodes
		}
	}

	return 0;
}

//�� �Լ��� ���ۿ����� �ϴ� �Է°����� ��带 �Է¹޴µ�, �� �Լ��� ó�� ȣ��� �� �޴� �Է°��� ���� ������ ����̴�.
//��带 �Է¹޾Ƽ� �ش� ���� ���� �̵��� �� �ִ� ������ ã�Ƴ��� �Ѵ�.
Node *link(Node *n) {
	//Connects node to random neighbor (if possible) and returns
	//address of next node that should be visited
	int x, y;
	char dir;
	Node *dest;

	//Nothing can be done if null pointer is given - return
	if (n == NULL) return NULL;

	//While there are directions still unexplored
	//dirs�� ��� ����ü�� ����ִ� ĳ������ 1����Ʈ ���ε�, 1����Ʈ�� ����� 4������ ǥ���� �� �ְ�, �̸� ���� �ʱ� ���� 15�� �����Ѵ�.
	//15�� 00001111�̹Ƿ�, �� 1�� ������ ��Ÿ����, �湮�� �ϸ� 1�� 0���� �ٲ۴�.
	// �ᱹ 00000000�� �Ǹ� �ݺ����� ����ǰ� ������� �����Ѵ�.
	//������� ����̴�. ���� ����� ���� ����̴�.
	while (n->dirs) {
		//Randomly pick one direction
		dir = (1 << (rand() % 4));

		//If it has already been explored - try again
		if (~n->dirs & dir) continue;

		//Mark direction as explored
		n->dirs &= ~dir;

		//Depending on chosen direction
		switch (dir) {
			//Check if it's possible to go right
		case 1:
			if (n->x + 2 < width) {
				x = n->x + 2;
				y = n->y;
			}
			else continue;
			break;

			//Check if it's possible to go down
		case 2:
			if (n->y + 2 < height) {
				x = n->x;
				y = n->y + 2;
			}
			else continue;
			break;

			//Check if it's possible to go left	
		case 4:
			if (n->x - 2 >= 0) {
				x = n->x - 2;
				y = n->y;
			}
			else continue;
			break;

			//Check if it's possible to go up
		case 8:
			if (n->y - 2 >= 0) {
				x = n->x;
				y = n->y - 2;
			}
			else continue;
			break;
		}

		//Get destination node into pointer (makes things a tiny bit faster)
		//������ �ϳ��� 2���� �迭�� ��Ÿ�� �� �ִ�.
		dest = nodes + x + y * width;
		
		//Make sure that destination node is not a wall
		if (dest->c == '0') {
			//If destination is a linked node already - abort
			//���� ������ ��尡 �̹� �湮�ߴ� ����� ���(Ȯ�� ����� �湮�� �ϰ� �Ǹ� ������ ��Ҹ� ����Ѵ�)
			if (dest->parent != NULL) continue;

			//Otherwise, adopt node
			dest->parent = n;

			//Remove wall between nodes
			//�̰� �̵��� 2ĭ�� �ϱ� ������ �߰��� ���� �ִٰ� �����Ѵ�. ���� �� ���� �����Ѵ�.
			nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = '0';
			draw();
			Sleep(600);
			//Return address of the child node
			//���� �㹰��, dest�� ���ư� ���� ������ �� �� ��带 ��ȯ�Ѵ�.
			return dest;
		}
	}

	//If nothing more can be done here - return parent's address
	draw();
	Sleep(600);
	//�̰� ���� ��� ������ �� Ž���ϰ� ���� �ٽ� Ÿ�� ���ư��� �ᱹ �������� ���ϴ� �ڵ��.
	return n->parent;
}

void draw() {
	system("cls");
	int i, j;

	//Outputs maze to terminal - nothing special
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			// new
			if (nodes[i + j * width].c == '1')
				printf("��");
			else
				printf(" %c", nodes[i + j * width].c);
			//else if (nodes[i + j * width].c == 'S')
			//	//	printf("%c", nodes[i + j * width].c);
			//	printf("��");
			//else if (nodes[i + j * width].c == 'E')
			//	printf("��");
			//else
			//	printf("  ");
			//// newend��

			// original
			//printf("%c", nodes[i + j * width].c);
		}
		printf("\n");
	}
}