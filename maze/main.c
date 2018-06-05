#include "util.h"
#include "gen_maze.h"
#include "gen_graph.h"
#include "bfs.h"

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
int main() {
	//start maze.
	Maze_Generating(1, 1);

	Graph_Generating();

	//start game
	//runMiniGame();
	
	BFS(maze_graph, 1);
	//Delete_Maze(maze);
	//Delete_Graph(maze_graph);
	return 0;

}

