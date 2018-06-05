#include "util.h"
#include "gen_maze.h"
#include "gen_graph.h"
#include "bfs.h"

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

