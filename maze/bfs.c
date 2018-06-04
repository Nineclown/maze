#include "bfs.h"

int BFS(Graph * graph, int start) {
	Array *visited = New_Array();
	Array *neighbor = New_Array();
	Vertex *currentVertex = 0;

	//visited
	Array_PushBack(visited, Graph_GetVertexByName(maze_graph, start)); //���� ����(������ ���� ����)�� �湮�ߴٰ� visited �迭�� ����ϴ�.
	
	//neighbor
	Graph_FindNeighbor(maze_graph, start, neighbor); //���� ������ ������ �������� neighbor �迭�� ����ϴ�.
	//Array_View(neighbor);

	while (!Array_IsEmpty(neighbor)) { //neighbor �迭�� �� ������ �ݺ��մϴ�. //�������� ����� �������� ������ ������ Ž�����ϸ� �˴ϴ�.
		//Array_View(visited);
		
		//dequeue
		currentVertex = (Vertex*)(*Array_Begin(neighbor)); //neighbor �迭�� �ε����� 0��(ó��) ������ �����ɴϴ�. �迭�� ť�� ����մϴ�.
		
		//visited
		Array_PushBack(visited, (Element)currentVertex); //������ ������ �湮�ߴٰ� visited �迭�� ����ϴ�.

		if (maze[currentVertex->x + currentVertex->y * width].c == "��") {
			printf("find way!\n");
			Array_Erase(neighbor, (Iterator)Array_Begin(neighbor)); //�迭�� ���� �����մϴ�. ���� �ʿ�.
			break;
		}
		Array_Erase(neighbor, (Iterator)Array_Begin(neighbor)); //�迭�� ���� �����մϴ�. ���� �ʿ�.
		
		//enqueue
		BFS_AddNeighbor(maze_graph, currentVertex->name, neighbor, visited);//������ ������ ������ ���� �� �湮���� ���� �������� neighbor�� �߰��մϴ�.
	}

	Array_View(visited);
	return 1;
}

void BFS_AddNeighbor(Graph *graph, int vt_name, Array *neighbor, Array *visited) {
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

//������ ������ �̸��� �湮�� �迭�� �����ϴ� �˻�
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