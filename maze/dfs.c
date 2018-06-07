#include "dfs.h"

int weight;
int DFS(Graph * graph, int start) {
	Array * visited = New_Array();
	Array *stack = New_Array();
	DFS_Runner(maze_graph, start, visited, stack);
	Array_View(visited);

	weight += dfs_cost(visited);
	return 1;
}

int DFS_Runner(Graph *graph, int vt_name, Array *visited, Array *stack) {
	Vertex *cur = 0;
	Array_PushBack(visited, Graph_GetVertexByName(maze_graph, vt_name)); //정점을 방문하고.
	DFS_AddNeighbor(maze_graph, vt_name, stack, visited); //인접 정점을 스택에 저장하고.

	while (!Array_IsEmpty(stack)) {
		cur = (Vertex *)(*(Array_End(stack) - 1)); //stack에서 pop()함.
		Array_Erase(stack, (Array_End(stack) - 1)); //stack에서 pop()한 결과 자동으로 안지워지니까 지움.
		Array_PushBack(visited, (Element)cur); //visited에 현재 방문한 정점 저장.

		if (maze[cur->x + cur->y * width].c == "ⓔ") {//도착지를 방문했다면 DFS search를 종료합니다.
			printf("find way!\n");
			Array_PushBack(visited, Graph_GetVertexByName(maze_graph, vt_name));
			//al_cost[1] = weight;
			break;
		}
		DFS_Runner(maze_graph, cur->name, visited, stack);

	}
	//   Array_View(visited);
	return 1;

}


int dfs_cost(Array *visited) {
	Array *route = New_Array();
	Iterator seek = 0;
	Vertex *vt = 0;
	int count = 0;
	int weight = 0;

	vt = (Vertex*)(*(Array_End(visited) - 1));
	while (vt->parent != 0) {
		Array_PushBack(route, (Element)vt);
		vt = vt->parent;
	}
	Array_PushBack(route, (Element)vt);

	//Array_View(route);
	count = route->usage;
	while (count != 1) {
		weight += Graph_GetWeight(maze_graph, Array_GetAt(route, count), Array_GetAt(route, --count));
		printf("(%d -> %d)'s cost: %d\n", count + 1, count, weight);
	}
	al_cost[1] = weight;
	printf("\n비용 : %d\n", weight);
	return weight;
}


void DFS_AddNeighbor(Graph *graph, int vt_name, Array *stack, Array *visited) {
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
			if (!DFS_CheckVisited(stack, opt) && !DFS_CheckVisited(visited, opt)) {
				Array_PushBack(stack, (Element)opt);
			}
		}
	}
}

//가져온 정점의 이름이 방문한 배열에 존재하는 검사
int DFS_CheckVisited(Array *visited, Vertex *target) {
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