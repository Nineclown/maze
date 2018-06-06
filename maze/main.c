#include "main.h"

/*
미로 생성 및 탐색 프로그램입니다.
미로는 홀수 크기의 입력만을 받을 수 있습니다. ex. (11, 17)

Maze_Generating()을 통해 원하는 지점을 시작지점으로 하는 미로를 생성합니다. 도착지점은 미로를 생성할 때 생성되지 않습니다.

Graph_Generating()을 통해 미로를 그래프화 시키며 이 과정에서 랜덤으로 도착지점을 생성합니다. 또는 사용자가 직접 도착지점을 설정할 수 있습니다.

사용가능한 탐색 알고리즘 목록

0. 좌선법.

1. DFS.

2. BFS.

3. Djikstra Algorithm.

4. A* Algorithm.

미로 전역변수: maze
미로의 각 요소에 접근하는 방법: maze[ x + y * width].c //c가 해당 미로가 길인지 벽인지, 시작인지, 끝인지, 정점인지에 대한 정보를 갖고 있습니다.

그래프 전역변수 maze_graph:
그래프의 정점에 접근하는 방법: Graph_GetVertex 관련 함수들. 또는 (vertex*)maze_graph.base[index]를 통해 접근이 가능합니다.
그래프의 정점과 인접한 정점에 접근하는 방법: Graph_FindNeighbor() 함수를 통해 접근이 가능합니다.

*/

void rh_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ 우선법 알고리즘 ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	right_hand(maze, 1, 1, 1);
	after = clock();
	t = (double)((after - before));
	printf("시간 : %.0lfms\n\n", t);
	al_time[0] = t;
}

void dfs_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ DFS 알고리즘 ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	DFS(maze_graph, 1);
	after = clock();
	t = (double)((after - before));
	printf("시간 : %.0lfms\n\n", t);
	al_time[1] = t;
}

void bfs_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ BFS 알고리즘 ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	BFS(maze_graph, 1);
	after = clock();
	t = (double)((after - before));
	printf("시간 : %.0lfms\n\n", t);
	al_time[2] = t;
}

void dijk_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ Dijkstra 알고리즘 ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	dijkstra(maze_graph);
	after = clock();
	t = (double)((after - before));
	printf("시간 : %.0lfms\n\n", t);
	al_time[3] = t;
}

void astar_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ A* 알고리즘 ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	astart(Graph_GetStartV(maze_graph), Graph_GetEndV(maze_graph));
	after = clock();
	t = (double)((after - before));
	printf("시간 : %.0lfms\n\n", t);
	al_time[4] = t;
}

int main() {
	int menu;
	COORD pos = { 0, 0 };

	//start maze
	Maze_Generating(1, 1);
	Graph_Generating();

	dijkstra(maze_graph);
	//start game
	//runMiniGame();

	do {
		system("cls");
		printf("[ 알고리즘 선택 ]\n\n");
		Maze_Draw_Debug();

		printf("\n");
		printf("(1) 좌선법 알고리즘\n");
		printf("(2) DFS 알고리즘\n");
		printf("(3) BFS 알고리즘\n");
		printf("(4) Dijkstra 알고리즘\n");
		printf("(5) A* 알고리즘\n");
		printf("(6) 모든 알고리즘 비교\n");
		printf("(0) 프로그램 종료\n");
		printf("\n번호를 입력하세요 : ");
		scanf_s("%d", &menu);

		switch (menu) {
		case 1: //좌선법 알고리즘.
			rh_run();

			printf("아무 키나 누르면 알고리즘 선택 화면으로 돌아갑니다.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 2: //DFS 알고리즘.
			dfs_run();

			printf("아무 키나 누르면 알고리즘 선택 화면으로 돌아갑니다.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 3: //BFS 알고리즘.
			bfs_run();

			printf("아무 키나 누르면 알고리즘 선택 화면으로 돌아갑니다.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 4: //Dijkstra 알고리즘.
			dijk_run();

			printf("아무 키나 누르면 알고리즘 선택 화면으로 돌아갑니다.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 5: //A* 알고리즘.
			astar_run();

			printf("아무 키나 누르면 알고리즘 선택 화면으로 돌아갑니다.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 6: //모두 비교.
			bfs_run();
			astar_run();

			system("cls");
			printf("[ 모든 알고리즘 비교 ]\n\n");
			Maze_Draw_Debug();
			printf("\n");

			printf("\t 비용 \t 시간\n");
			printf("------------------------\n");
			printf("BFS \t %d \t %.0lfms\n", al_cost[1], al_time[1]);
			printf("A* \t %d \t %.0lfms\n", al_cost[2], al_time[2]);
			printf("\n");

			printf("아무 키나 누르면 알고리즘 선택 화면으로 돌아갑니다.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 0:
			printf("\n프로그램을 종료합니다.\n\n");
			return 0;
		}

	} while (menu != 0);

	//Delete_Maze(maze);
	//Delete_Graph(maze_graph);
	return 0;

}

