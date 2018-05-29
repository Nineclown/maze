#include "generating.h"
#include <Windows.h>
int init(int *x, int *y) {
	int i, j;
	Node *iter;

	width = *x;
	height = *y;
	//미로 크기만큼의 메모리를 할당받습니다.
	maze = calloc(width * height, sizeof(Node));
	if (maze == NULL) return 1;

	//미로의 각 노드들을 초기화합니다.
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {

			iter = maze + i + j * width;

			if (i * j % 2) { //임의의 노드를 벽이 아니게 만듭니다. 미로의 가장자리 부분은 반드시 벽이되어야 합니다.
				iter->x = i;
				iter->y = j;
				iter->dirs = 15; //각 노드마다 방문할 지도를 초기화 합니다. 00001111.
				iter->c = "  ";
			}
			else iter->c = "■"; //나머지 노드들은 벽으로 초기화 합니다. 벽은 방향이나 좌표를 갖지 않습니다.(0으로 초기화 됩니다.)
		}
	}

	draw();
	return 0;
}


Node *link(Node *n) {
	//입력받은 노드(이하 노드n)와 이웃 노드를 연결합니다. 그리고 연결된 노드를 반환합니다. 
	
	int x, y; //이웃 노드의 좌표 값을 담을 변수입니다.
	char dir; //노드 n이 방문할 방향을 담을 변수입니다.
	Node *dest; //이웃 노드를 가리킬 포인터 변수입니다.

	//노드 n이 잘못된 경우.
	if (n == NULL) return NULL;

	//노드 n이 아직 방문할 방향이 남아있는 경우, 모든 방향을 방문할 때까지 반복합니다.
	while (n->dirs) {
		//rand()를 통해 임의의 방향을 정합니다.
		dir = (1 << (rand() % 4));

		//임의의 방향이 이미 노드 n이 방문한 방향인 경우,
		if (~n->dirs & dir) continue;

		//노드 n의 dir값에 방문 표시를 남깁니다.
		n->dirs &= ~dir;

		//임의의 방향을 방문합니다.
		switch (dir) {
			//0001은 오른쪽입니다.
		case 1:
			if (n->y + 2 < height) {
				x = n->x;
				y = n->y + 2;
			}
			else continue;
			break;

			//0010은 아래쪽입니다.
		case 2:
			if (n->x + 2 < width) {
				x = n->x + 2;
				y = n->y;
			}
			else continue;
			break;

			//0100은 왼입니다.
		case 4:
			if (n->y - 2 >= 0) {
				x = n->x;
				y = n->y - 2;
			}
			else continue;
			break;

			//1000은 위쪽입니다.
		case 8:
			if (n->x - 2 >= 0) {
				x = n->x - 2;
				y = n->y;
			}
			else continue;
			break;
		}

		//임의의 방향으로 방문해서 찾아낸 이웃 노드를 dest에 담습니다.
		dest = maze + x + y * width;

		//이웃 노드가 길인지 벽인지 확인합니다.
		if (dest->c == "  ") {
			
			//이웃 노드가 이미 방문된(탐색된) 경우엔 다른 방향으로 길을 만들어야 하므로 되돌아 갑니다.
			if (dest->parent != NULL) continue;

			//그 외의 경우, 이웃 노드와 노드 n을 연결합니다.
			dest->parent = n;

			//두 노드를 가로막는 벽을 제거합니다.
			maze[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = "  ";
			draw();
			Sleep(600);
			//이웃 노드를 반환합니다.
			return dest;
		}
	}

	//모든 방향을 탐색했지만 이미 한번씩 방문한 경우, 되돌아 갑니다. 
	draw();
	Sleep(600);
	return n->parent;
}

void draw() {
	system("cls");
	int i, j;

	//미로를 출력합니다.
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++)
			printf("%s", maze[i + j * width].c);
		printf("\n");
	}
}