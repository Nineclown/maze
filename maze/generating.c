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

//이 함수의 동작원리는 일단 입력값으로 노드를 입력받는데, 이 함수가 처음 호출될 때 받는 입력값은 시작 지점의 노드이다.
//노드를 입력받아서 해당 노드로 부터 이동할 수 있는 방향을 찾아내야 한다.
Node *link(Node *n) {
	//Connects node to random neighbor (if possible) and returns
	//address of next node that should be visited
	int x, y;
	char dir;
	Node *dest;

	//Nothing can be done if null pointer is given - return
	if (n == NULL) return NULL;

	//While there are directions still unexplored
	//dirs는 노드 구조체에 들어있는 캐릭터형 1바이트 값인데, 1바이트면 충분히 4방향을 표현할 수 있고, 이를 위한 초기 값을 15로 지정한다.
	//15는 00001111이므로, 각 1이 방향을 나타내고, 방문을 하면 1을 0으로 바꾼다.
	// 결국 00000000이 되면 반복문이 종료되고 결과값을 리턴한다.
	//결과값은 노드이다. 현재 노드의 이전 노드이다.
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
		//포인터 하나로 2차원 배열을 나타낼 수 있다.
		dest = nodes + x + y * width;
		
		//Make sure that destination node is not a wall
		if (dest->c == '0') {
			//If destination is a linked node already - abort
			//현재 가려는 노드가 이미 방문했던 노드인 경우(확인 방법은 방문을 하게 되면 이전의 장소를 기억한다)
			if (dest->parent != NULL) continue;

			//Otherwise, adopt node
			dest->parent = n;

			//Remove wall between nodes
			//이게 이동을 2칸씩 하기 때문에 중간에 벽이 있다고 가정한다. 따라서 이 벽을 제거한다.
			nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = '0';
			draw();
			Sleep(600);
			//Return address of the child node
			//벽도 허물고, dest의 돌아갈 값도 설정한 후 이 노드를 반환한다.
			return dest;
		}
	}

	//If nothing more can be done here - return parent's address
	draw();
	Sleep(600);
	//이건 이제 모든 방향을 다 탐색하고 나서 다시 타고 돌아가서 결국 원지점을 향하는 코드다.
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
				printf("■");
			else
				printf(" %c", nodes[i + j * width].c);
			//else if (nodes[i + j * width].c == 'S')
			//	//	printf("%c", nodes[i + j * width].c);
			//	printf("●");
			//else if (nodes[i + j * width].c == 'E')
			//	printf("◎");
			//else
			//	printf("  ");
			//// newend■

			// original
			//printf("%c", nodes[i + j * width].c);
		}
		printf("\n");
	}
}