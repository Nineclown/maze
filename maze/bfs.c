#include "bfs.h"

int BFS(Graph * graph, int start) {
	Array *visited = New_Array();
	Array *neighbor = New_Array();
	Vertex *currentVertex = 0;

	//visited
	Array_PushBack(visited, Graph_GetVertexByName(maze_graph, start)); //현재 정점(실제론 시작 정점)를 방문했다고 visited 배열에 담습니다.
	
	//neighbor
	Graph_FindNeighbor(maze_graph, start, neighbor); //현재 정점과 인접한 정점들을 neighbor 배열에 담습니다.
	//Array_View(neighbor);

	while (!Array_IsEmpty(neighbor)) { //neighbor 배열이 빌 때까지 반복합니다. //도착점이 생기면 도착점에 도달할 때까지 탐색을하면 됩니다.
		//Array_View(visited);
		
		//dequeue
		currentVertex = (Vertex*)(*Array_Begin(neighbor)); //neighbor 배열의 인덱스가 0인(처음) 정점을 가져옵니다. 배열을 큐로 사용합니다.
		
		//visited
		Array_PushBack(visited, (Element)currentVertex); //가져온 정점을 방문했다고 visited 배열에 담습니다.

		if (maze[currentVertex->x + currentVertex->y * width].c == "ⓔ") {
			printf("find way!\n");
			Array_Erase(neighbor, (Iterator)Array_Begin(neighbor)); //배열에 값을 제거합니다. 수정 필요.
			break;
		}
		Array_Erase(neighbor, (Iterator)Array_Begin(neighbor)); //배열에 값을 제거합니다. 수정 필요.
		
		//enqueue
		BFS_AddNeighbor(maze_graph, currentVertex->name, neighbor, visited);//가져온 정점과 인접한 정점 중 방문하지 않은 정점들을 neighbor에 추가합니다.
	}

	Array_View(visited);
	return 1;
}

void BFS_AddNeighbor(Graph *graph, int vt_name, Array *neighbor, Array *visited) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	//그래프의 모든 간선을 다 탐색합니다.
	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, vt_name)) { //특정 간선이 타겟 정점을 갖고 있을 때,
			Vertex *opt;
			opt = Edge_AnOther(edge, vt_name); //타겟 정점과 공유한 간선의 반대편 정점을 가져옵니다.
			if (!BFS_CheckVisited(visited, opt)) {
				Array_PushBack(neighbor, opt);
			}
			else {
				//
			}
		}
	}
	//Array_View(neighbor);
}

//가져온 정점의 이름이 방문한 배열에 존재하는 검사
int BFS_CheckVisited(Array *visited, Vertex *target) {
	Iterator seek = 0, end = 0;
	Vertex *vt = 0;
	seek = Array_Begin(visited);
	end = Array_End(visited);

	for (seek = seek; seek != end; ++seek) {
		vt = (Vertex*)(*seek);
		if (target->name == vt->name)
			return 1;
	}
	return 0;
}