#include "bfs.h"

int BFS(Graph * graph, int start) {
	Array *visited = New_Array();
	Array *neighbor = New_Array();
	Vertex *currentVertex = 0;

	//visited
	Array_PushBack(visited, (Element)Graph_GetVertexByName(maze_graph, start)); //���� ����(������ ���� ����)�� �湮�ߴٰ� visited �迭�� ����ϴ�.
	
	//neighbor
	BFS_AddNeighbor(maze_graph, start, neighbor, visited); //���� ������ ������ �������� neighbor �迭�� ����ϴ�.
	
	//printf("�߰�=neighbor==========\n");
	//Array_View(neighbor);

	while (!Array_IsEmpty(neighbor)) { //neighbor �迭�� �� ������ �ݺ��մϴ�. //�������� ����� �������� ������ ������ Ž�����ϸ� �˴ϴ�.
		
		//dequeue
		currentVertex = (Vertex*)(*Array_Begin(neighbor)); //neighbor �迭�� �ε����� 0��(ó��) ������ �����ɴϴ�. �迭�� ť�� ����մϴ�.
														   //
		//visited
		Array_PushBack(visited, (Element)currentVertex); //������ ������ �湮�ߴٰ� visited �迭�� ����ϴ�.

		//�������� �湮�ߴٸ� BFS search�� �����մϴ�.
		if (maze[currentVertex->x + currentVertex->y * width].c == "��") {
			printf("find way!\n");
			Array_Erase(neighbor, (Iterator)Array_Begin(neighbor)); //�迭�� ���� �����մϴ�.
			break;
		}
		Array_Erase(neighbor, (Iterator)Array_Begin(neighbor)); //�迭�� ���� �����մϴ�.
		
		//enqueue
		BFS_AddNeighbor(maze_graph, currentVertex->name, neighbor, visited);//������ ������ ������ ���� �� �湮���� ���� �������� neighbor�� �߰��մϴ�.
	}
	printf("DFS_visited\n");
	Array_View(visited);

	printf("routing\n");
	BFS_Routing(visited);

	return 1;
}

int BFS_Routing(Array *visited) {
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

	Array_View(route);
	count = route->usage;
	while (count != 1) {
		weight += Graph_GetWeight(maze_graph, Array_GetAt(route, count), Array_GetAt(route, --count));
		printf("(%d -> %d)'s cost: %d\n", count + 1, count, weight);
	}
	printf("\n��� : %d\n", weight);
	al_cost[2] = weight;
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
			Vertex *opt; //������ ����.
			opt = Edge_AnOther(edge, vt_name); //�̰� �Ѱ��ִ� �� �ּ��̱��ѵ� ������ ���� �ּ��� ���� ���� �ּҰ� �ƴϾ�.
			if (!BFS_CheckVisited(visited, opt) && !BFS_CheckVisited(neighbor, opt)) { //������ ������ ����, �湮���� �ʰ� ť�� �־������� �ʾҴٸ�,
				opt->parent = Graph_GetVertexByName(maze_graph, vt_name); //maze_graph�� ������ ������ ��.
				Array_PushBack(neighbor, (Element)opt);
				//printf("�߰�=neighbor==========\n");
				//Array_View(neighbor);
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

	for (seek = seek; seek != end; seek++) {
		vt = (Vertex*)(*seek);
		if (target->name == vt->name) {
			//printf("++++++++++++++\n");
			//printf("[%d]�� �̹� �湮�� or �湮�� �����Դϴ�\n", target->name);
			return 1;
		}
	}
	return 0;
}