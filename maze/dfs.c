#include "dfs.h"

int DFS(Graph * graph, int start) {
	Array * visited = New_Array();
	Array *stack = New_Array();
	DFS_Runner(maze_graph, start, visited, stack);
	//Array_View(visited); #debug
	DFS_Routing(visited);
	return 1;
}

int DFS_Runner(Graph *graph, int vt_name, Array *visited, Array *stack) {
	Vertex *currentVertex = 0;

	currentVertex = Graph_GetVertexByName(maze_graph, vt_name);

	Array_PushBack(visited, (Element)currentVertex); //������ �湮�ϰ� ����.
	DFS_AddNeighbor(maze_graph, currentVertex, stack, visited); //���� ������ ���ÿ� �����ϰ�.
	
	while (!Array_IsEmpty(stack)) {
		currentVertex = (Vertex *)(*(Array_End(stack) - 1)); //stack���� pop()��.
		Array_Erase(stack, (Array_End(stack) - 1)); //stack���� pop()�� ��� �ڵ����� ���������ϱ� ����.
		//Array_PushBack(visited, (Element)cur); //visited�� ���� �湮�� ���� ����.
		if (maze[currentVertex->x + currentVertex->y * width].c == "��") {
			Array_PushBack(visited, (Element)currentVertex);
			break;
		}
		if (DFS_Runner(maze_graph, currentVertex->name, visited, stack))
			return 1;
	}
	return 1;
}

int DFS_Routing(Array *visited) {
	Array *route = New_Array();
	Iterator seek = 0;
	Vertex *vt = 0;

	vt = (Vertex*)(*(Array_End(visited) - 1));
	while (vt->parent != 0) {
		Array_PushBack(route, (Element)vt);
		vt = vt->parent;
	}
	Array_PushBack(route, (Element)vt);

	//Array_View(route);
	DFS_GetCost(route);

	return 1;
}

int DFS_GetCost(Array *route) {
	int count = 0;
	int total = 0;
	int weight = 0;
	Vertex *vt1 = 0;
	Vertex *vt2 = 0;

	count = route->usage - 1;
	//printf("BFS calculating cost\n");
	while (count != 0) {
		vt1 = (Vertex *)(Array_GetAt(route, count));
		vt2 = (Vertex *)(Array_GetAt(route, --count));
		weight = Graph_GetWeight(maze_graph, vt1, vt2);
		total += weight;
		//printf("[%d] -> [%d] cost: %d\n", vt1->name, vt2->name, weight);
	}
	//printf("\n��� : %d\n", total);
	al_cost[1] = total;
	return 1;
}

void DFS_AddNeighbor(Graph *graph, Vertex *vt, Array *stack, Array *visited) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	//�׷����� ��� ������ �� Ž���մϴ�.
	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, vt->name)) { //Ư�� ������ Ÿ�� ������ ���� ���� ��,
			Vertex *opt;
			opt = Edge_AnOther(edge, vt->name); //Ÿ�� ������ ������ ������ �ݴ��� ������ �����ɴϴ�.
			if (!DFS_CheckVisited(stack, opt) && !DFS_CheckVisited(visited, opt)) {
				opt->parent = vt;
				Array_PushBack(stack, (Element)opt);
			}
		}
	}
}

//������ ������ �̸��� �湮�� �迭�� �����ϴ� �˻�
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