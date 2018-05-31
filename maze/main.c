#include "util.h"
#include "gen_maze.h"
#include "graph.h"

int main() {
	int i = 0, j = 0;
	Graph *graph = New_Graph();
	Array *neighbor = New_Array();

	//start maze.
	genMaze(1, 1);

	//start game
	//runMiniGame();
	printf("is it? %s", maze[1 + 1 * width].c);

	//일단 시작점부터 검사를 시작한다.
	//언제까지? 모든 미로의 길이 1이 될 때까지.
	//중간에 분기점이 생기면(벽이 1이하 또는 길이 3이상) 이 위치를 스택이나 큐에 저장한다
	//미로의 dirs 값을 일단 초기화 시켜보자

	Node * iter;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			iter = maze + i + j * width;
			if (iter->c != "■")
				iter->dirs = 15;
		}
	}

	//입력받은 노드(이하 노드n)와 이웃 노드를 연결합니다. 이웃 노드를 반환합니다. 

	int x, y; //이웃 노드의 좌표 값을 담을 변수입니다.
	char dir; //노드 n이 방문할 방향을 담을 변수입니다.
	Node *dest; //이웃 노드를 가리킬 포인터 변수입니다.
	Node *n = NULL;
	//노드 n이 잘못된 경우.
	//if (n == NULL) return NULL;

	//노드 n이 아직 방문할 방향이 남아있는 경우, 모든 방향을 방문할 때까지 반복합니다.
	int count = 0;
	while (n->dirs) {

		dir = 1 << count++;
		if (count > 3)
			DieWithError("ㅋ");

		//이미 노드 n이 방문한 방향인 경우,
		if (~n->dirs & dir) continue;

		//노드 n의 dir값에 방문 표시를 남깁니다.
		n->dirs &= ~dir;

		//방문합니다.
		switch (dir) {
			//0001은 오른쪽입니다.
		case 1:
			if (n->y + 1 < height - 1) {
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

		//방문해서 찾아낸 이웃 노드를 dest에 담습니다.
		dest = maze + x + y * width;

		//이웃 노드가 길인지 벽인지 확인합니다.
		if (dest->c == "■") { //이웃 노드가 벽인 경우.

							  //이웃 노드가 이미 방문된(탐색된) 경우엔 다른 방향으로 길을 만들어야 하므로 되돌아 갑니다.
			if (dest->parent != NULL) continue;

			//그 외의 경우, 이웃 노드와 노드 n을 연결합니다.
			dest->parent = n;

			//두 노드를 가로막는 벽을 제거합니다.
			maze[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = "  ";
			//draw();

			//이웃 노드의 벽을 부십니다.
			maze[x + y * width].c = "  ";
			//draw();

			//이웃 노드를 반환합니다.
			return dest;
		}
		else if (dest->c == "  ") { //이웃 노드가 길인 경우.
			int ran = rand() % 10;	//랜덤으로 길 뚫어.

			if (!ran)
				maze[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = "  ";
			//draw();
		}
	}

	//모든 방향을 탐색했지만 이미 한번씩 방문한 경우, 되돌아 갑니다. 
	//draw();
	return n->parent;


	Graph_AddVertex(graph, "S");
	Graph_AddEdge(graph, "J", "K", 3);

	Graph_FindNeighvor(graph, "A", neighbor);
	Iterator seek = 0, end = 0;
	Vertex pt = 0;
	seek = Array_Begin(neighbor);
	end = Array_End(neighbor);

	for (seek = seek; seek != end; ++seek) {
		pt = (Vertex)(*seek);
		printf("%s\n", pt);
	}


	//Graph_View(graph);

	Delete_Graph(graph);
	return 0;

}

