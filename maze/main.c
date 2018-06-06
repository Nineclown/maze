#include "main.h"

/*
�̷� ���� �� Ž�� ���α׷��Դϴ�.
�̷δ� Ȧ�� ũ���� �Է¸��� ���� �� �ֽ��ϴ�. ex. (11, 17)

Maze_Generating()�� ���� ���ϴ� ������ ������������ �ϴ� �̷θ� �����մϴ�. ���������� �̷θ� ������ �� �������� �ʽ��ϴ�.

Graph_Generating()�� ���� �̷θ� �׷���ȭ ��Ű�� �� �������� �������� ���������� �����մϴ�. �Ǵ� ����ڰ� ���� ���������� ������ �� �ֽ��ϴ�.

��밡���� Ž�� �˰��� ���

0. �¼���.

1. DFS.

2. BFS.

3. Djikstra Algorithm.

4. A* Algorithm.

�̷� ��������: maze
�̷��� �� ��ҿ� �����ϴ� ���: maze[ x + y * width].c //c�� �ش� �̷ΰ� ������ ������, ��������, ������, ���������� ���� ������ ���� �ֽ��ϴ�.

�׷��� �������� maze_graph:
�׷����� ������ �����ϴ� ���: Graph_GetVertex ���� �Լ���. �Ǵ� (vertex*)maze_graph.base[index]�� ���� ������ �����մϴ�.
�׷����� ������ ������ ������ �����ϴ� ���: Graph_FindNeighbor() �Լ��� ���� ������ �����մϴ�.

*/

void rh_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ �켱�� �˰��� ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	right_hand(maze, 1, 1, 1);
	after = clock();
	t = (double)((after - before));
	printf("�ð� : %.0lfms\n\n", t);
	al_time[0] = t;
}

void dfs_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ DFS �˰��� ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	DFS(maze_graph, 1);
	after = clock();
	t = (double)((after - before));
	printf("�ð� : %.0lfms\n\n", t);
	al_time[1] = t;
}

void bfs_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ BFS �˰��� ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	BFS(maze_graph, 1);
	after = clock();
	t = (double)((after - before));
	printf("�ð� : %.0lfms\n\n", t);
	al_time[2] = t;
}

void dijk_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ Dijkstra �˰��� ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	dijkstra(maze_graph);
	after = clock();
	t = (double)((after - before));
	printf("�ð� : %.0lfms\n\n", t);
	al_time[3] = t;
}

void astar_run() {
	clock_t before;
	clock_t after;
	double t;

	system("cls");
	printf("[ A* �˰��� ]\n\n");
	Maze_Draw_Debug();
	printf("\n");

	before = clock();
	astart(Graph_GetStartV(maze_graph), Graph_GetEndV(maze_graph));
	after = clock();
	t = (double)((after - before));
	printf("�ð� : %.0lfms\n\n", t);
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
		printf("[ �˰��� ���� ]\n\n");
		Maze_Draw_Debug();

		printf("\n");
		printf("(1) �¼��� �˰���\n");
		printf("(2) DFS �˰���\n");
		printf("(3) BFS �˰���\n");
		printf("(4) Dijkstra �˰���\n");
		printf("(5) A* �˰���\n");
		printf("(6) ��� �˰��� ��\n");
		printf("(0) ���α׷� ����\n");
		printf("\n��ȣ�� �Է��ϼ��� : ");
		scanf_s("%d", &menu);

		switch (menu) {
		case 1: //�¼��� �˰���.
			rh_run();

			printf("�ƹ� Ű�� ������ �˰��� ���� ȭ������ ���ư��ϴ�.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 2: //DFS �˰���.
			dfs_run();

			printf("�ƹ� Ű�� ������ �˰��� ���� ȭ������ ���ư��ϴ�.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 3: //BFS �˰���.
			bfs_run();

			printf("�ƹ� Ű�� ������ �˰��� ���� ȭ������ ���ư��ϴ�.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 4: //Dijkstra �˰���.
			dijk_run();

			printf("�ƹ� Ű�� ������ �˰��� ���� ȭ������ ���ư��ϴ�.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 5: //A* �˰���.
			astar_run();

			printf("�ƹ� Ű�� ������ �˰��� ���� ȭ������ ���ư��ϴ�.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 6: //��� ��.
			bfs_run();
			astar_run();

			system("cls");
			printf("[ ��� �˰��� �� ]\n\n");
			Maze_Draw_Debug();
			printf("\n");

			printf("\t ��� \t �ð�\n");
			printf("------------------------\n");
			printf("BFS \t %d \t %.0lfms\n", al_cost[1], al_time[1]);
			printf("A* \t %d \t %.0lfms\n", al_cost[2], al_time[2]);
			printf("\n");

			printf("�ƹ� Ű�� ������ �˰��� ���� ȭ������ ���ư��ϴ�.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			system("pause > nul");
			break;
		case 0:
			printf("\n���α׷��� �����մϴ�.\n\n");
			return 0;
		}

	} while (menu != 0);

	//Delete_Maze(maze);
	//Delete_Graph(maze_graph);
	return 0;

}

