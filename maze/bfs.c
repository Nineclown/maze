#include "bfs.h"

int BFS(Graph * graph, int start) {
	Array *visited = New_Array();
	Array *neighbor = New_Array();
	Vertex *currentVertex = 0;

	currentVertex = Graph_GetVertexByName(maze_graph, start);

	//visited
	Array_PushBack(visited, (Element)currentVertex); //���� ����(������ ���� ����)�� �湮�ߴٰ� visited �迭�� ����ϴ�.
	
	//neighbor
	BFS_AddNeighbor(maze_graph, currentVertex, neighbor, visited); //���� ������ ������ �������� neighbor �迭�� ����ϴ�.
	
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
		BFS_AddNeighbor(maze_graph, currentVertex, neighbor, visited);//������ ������ ������ ���� �� �湮���� ���� �������� neighbor�� �߰��մϴ�.
	}
	printf("BFS visited\n");
	Array_View(visited);

	printf("BFS routing\n");
	BFS_Routing(visited);

	return 1;
}

int BFS_Routing(Array *visited) {
	Array *route = New_Array();
	Iterator seek = 0;
	Vertex *vt = 0;

	vt = (Vertex*)(*(Array_End(visited) - 1));
	while (vt->parent != 0) {
		Array_PushBack(route, (Element)vt);
		vt = vt->parent;
	}
	Array_PushBack(route, (Element)vt);

	Array_View(route);
	BFS_GetCost(route);
	
	return 1;
}

int BFS_GetCost(Array *route) {
	int count = 0;
	int total = 0;
	int weight = 0;
	Vertex *vt1 = 0;
	Vertex *vt2 = 0;

	count = route->usage - 1;
	printf("BFS calculating cost\n");
	while (count != 0) {
		vt1 = (Vertex *)(Array_GetAt(route, count));
		vt2 = (Vertex *)(Array_GetAt(route, --count));
		weight = Graph_GetWeight(maze_graph, vt1, vt2);
		total += weight;
		printf("[%d] -> [%d] cost: %d\n", vt1->name, vt2->name, weight);
	}
	printf("\n��� : %d\n", total);
	al_cost[2] = total;
	return 1;
}

void BFS_AddNeighbor(Graph *graph, Vertex *vt, Array *neighbor, Array *visited) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	//�׷����� ��� ������ �� Ž���մϴ�.
	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, vt->name)) { //Ư�� ������ Ÿ�� ������ ���� ���� ��,
			Vertex *opt; //������ ����.
			opt = Edge_AnOther(edge, vt->name); //�̰� �Ѱ��ִ� �� �ּ��̱��ѵ� ������ ���� �ּ��� ���� ���� �ּҰ� �ƴϾ�.
			if (!BFS_CheckVisited(visited, opt) && !BFS_CheckVisited(neighbor, opt)) { //������ ������ ����, �湮���� �ʰ� ť�� �־������� �ʾҴٸ�,
				opt->parent = vt; //maze_graph�� ������ ������ ��.
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