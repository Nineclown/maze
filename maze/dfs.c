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
	Array_PushBack(visited, Graph_GetVertexByName(maze_graph, vt_name)); //������ �湮�ϰ�.
	DFS_AddNeighbor(maze_graph, vt_name, stack, visited); //���� ������ ���ÿ� �����ϰ�.

	while (!Array_IsEmpty(stack)) {
		cur = (Vertex *)(*(Array_End(stack) - 1)); //stack���� pop()��.
		Array_Erase(stack, (Array_End(stack) - 1)); //stack���� pop()�� ��� �ڵ����� ���������ϱ� ����.
		Array_PushBack(visited, (Element)cur); //visited�� ���� �湮�� ���� ����.

		if (maze[cur->x + cur->y * width].c == "��") {//�������� �湮�ߴٸ� DFS search�� �����մϴ�.
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
	printf("\n��� : %d\n", weight);
	return weight;
}


void DFS_AddNeighbor(Graph *graph, int vt_name, Array *stack, Array *visited) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	//�׷����� ��� ������ �� Ž���մϴ�.
	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, vt_name)) { //Ư�� ������ Ÿ�� ������ ���� ���� ��,
			Vertex *opt;
			opt = Edge_AnOther(edge, vt_name); //Ÿ�� ������ ������ ������ �ݴ��� ������ �����ɴϴ�.
			if (!DFS_CheckVisited(stack, opt) && !DFS_CheckVisited(visited, opt)) {
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