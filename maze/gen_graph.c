#include "gen_graph.h"

int Maze_ReInit() {
	int i = 0, j = 0;

	Node *iter;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			iter = maze + i + j * width;
			if (iter->c != "��") {
				iter->x = i;
				iter->y = j;
				if (iter->c == "��")
					iter->parent = iter;
				else
					iter->parent = 0;
				if (!Maze_FindDir(iter))
					DieWithError("Maze_ReInit()");
			}
		}
	}
	Maze_Draw();
	return 1;
}

int Maze_FindDir(Node *n) {
	char dirs = 0;
	int count = 0;
	//������ 0001
	if (maze[n->x + (n->y + 1) * width].c != "��") {
		dirs += 1;
		count++;
	}
	//�Ʒ���
	if (maze[n->x + 1 + n->y * width].c != "��") {
		dirs += 2;
		count++;
	}
	//����
	if (maze[n->x + (n->y - 1) * width].c != "��") {
		dirs += 4;
		count++;
	}
	//����
	if (maze[n->x - 1 + n->y * width].c != "��") {
		dirs += 8;
		count++;
	}
	n->dirs = dirs;

	//���ý� ��ũ�� �Ѵ�.
	if (count >= 3 || count <= 1) {
		if (n->c == "��") {
			//nothing
		}
		else
			n->c = "��";
	}

	return 1;
}

int Graph_SetVnE(Node *n) {
	int name = 0;

	name = maze_graph->vertexs->usage + 1; //vertex�� �̸��� 1���� ����.

	if (n->c == "��" || n->c == "��") {
		//���� vertex�� ����?
		//vertex�� ���� 0�� ���<= ó������ ã��
		if (vertexs->usage == 0) {
			Graph_AddVertex(maze_graph, name, n->x, n->y);
			Array_PushBack(vertexs, (Element)Graph_GetVertexByName(maze_graph, name));
			COUNT = 0;//�ʱ�ȭ.
		}

		//vertex�� ���� 1�� ��� <= �̹� �ϳ��� ���� �� �ٸ� �ϳ��� ã��
		//edge�� �����.
		//ó�� vertex�� �����.
		//count�� 0���� �ʱ�ȭ�Ѵ�.
		else if (vertexs->usage == 1) {
			//vertex�� �������� �ʵ� �����ϵ� �ϴ� ������ �õ��մϴ�.
			Graph_AddVertex(maze_graph, name, n->x, n->y);
	
			//�׸��� ���� ��ġ�� vertex�� �����Ǿ��ų� ���� �־��ų� ������� Array�� ����ϴ�.
			Array_PushBack(vertexs, (Element)Graph_GetVertex(maze_graph, n->x, n->y));
			//printf("�迭 ����: [0]: %d, [1]: %d\n", ((Vertex *)Array_GetAt(vertexs, 0))->name, ((Vertex *)Array_GetAt(vertexs, 1))->name);
			
			//�迭�� ������ �������� edge�� �����ϴµ�, �̹� ������ edge�� 0�̰� ������ 1�̴�.
			if (COUNT % 2)
				COUNT++;
			if (COUNT == 0)
				COUNT = 2;
			Graph_AddEdge(maze_graph, (Vertex*)(*Array_Begin(vertexs)), (Vertex*)(*(Array_End(vertexs) - 1)), COUNT);
			
			//�׸��� ���� Array�� ó�� ���� ���� �����.
			Array_Erase(vertexs, (Iterator)Array_Begin(vertexs));
			COUNT = 0;
		}
	}

	return 1;
}

Node *Graph_Link(Node *n) {

	Graph_SetVnE(n);
	//������ ���� �����ϴ� �۾�.
	int x = 0, y = 0; //�̿� ����� ��ǥ ���� ���� �����Դϴ�.
	char dir = 0; //��� n�� �湮�� ������ ���� �����Դϴ�.
	Node *dest = 0; //�̿� ��带 ����ų ������ �����Դϴ�.
	int count = 0;
	//��� n�� �߸��� ���.
	if (n == NULL) return NULL;

	//��� n�� ���� �湮�� ������ �����ִ� ���, ��� ������ �湮�� ������ �ݺ��մϴ�.
	while (n->dirs) {
		if (count >= 4)
			DieWithError("rr");
		dir = (1 << count++);

		//�̹� ��� n�� �湮�� ������ ���,
		if (~n->dirs & dir) continue;

		//��� n�� dir���� �湮 ǥ�ø� ����ϴ�.
		n->dirs &= ~dir;

		//�湮�մϴ�.
		switch (dir) {
			//0001�� �������Դϴ�.
		case 1:
			if (n->y + 1 < height - 1) {
				x = n->x;
				y = n->y + 1;
			}
			else continue;
			break;

			//0010�� �Ʒ����Դϴ�.
		case 2:
			if (n->x + 1 < width - 1) {
				x = n->x + 1;
				y = n->y;
			}
			else continue;
			break;

			//0100�� ���Դϴ�.
		case 4:
			if (n->y - 1 > 0) {
				x = n->x;
				y = n->y - 1;
			}
			else continue;
			break;

			//1000�� �����Դϴ�.
		case 8:
			if (n->x - 1 > 0) {
				x = n->x - 1;
				y = n->y;
			}
			else continue;
			break;
		}

		//�湮�ؼ� ã�Ƴ� �̿� ��带 dest�� ����ϴ�.
		dest = maze + x + y * width;

		//�̿� ��尡 �̹� �湮��(Ž����) ��쿣 �ٸ� �������� ���� ������ �ϹǷ� �ǵ��� ���ϴ�.
		if (dest->parent != NULL) {
			if (dest->c == "��") {
				Array_PushBack(vertexs, (Element)Graph_GetVertex(maze_graph, dest->x, dest->y));
				if (COUNT % 2)
					COUNT++;
				if (COUNT == 0)
					COUNT = 2;
				if (Graph_AddEdge(maze_graph, (Vertex*)(*Array_Begin(vertexs)), (Vertex *)(*(Array_End(vertexs) - 1)), COUNT)) {
					//printf("edge�߰�(%d - %d)\n", ((Vertex*)*Array_Begin(vertexs))->name, ((Vertex*)*(Array_End(vertexs) - 1))->name);
				}
				Array_Erase(vertexs, Array_Begin(vertexs));
				COUNT = 0;
			}
			continue;
			
		}
		//�� ���� ���, �̿� ���� ��� n�� �����մϴ�.
		dest->parent = n;
		COUNT++;
		//draw();
		//�̿� ��带 ��ȯ�մϴ�.
		return dest;
	}

	//��� ������ Ž�������� �̹� �ѹ��� �湮�� ���, �ǵ��� ���ϴ�. 
	//draw();
	return n->parent;
}

int Graph_Generating() {
	Node *start = 0;
	Node *last = 0;
	Node *iter = 0;
	Array *neibor = New_Array();
	//�׷��� ��ҵ� �ʱ�ȭ.
	maze_graph = New_Graph();
	vertexs = New_Array();
	Array_SetSize(vertexs, 0, 0);

	//�̷� --> �׷��� ��ȯ
	Maze_ReInit();
	//Maze_Draw();
	Maze_Draw();

	//�̷ο��� �������� ã���ϴ�.
	iter = maze;
	while (iter->c != "��")
		iter++;
	start = iter;
	last = start;

	while ((last = Graph_Link(last)) != start);
	Graph_SetEnd(maze_graph);

	Maze_Draw_Debug();
	//Graph_ViewEdges(maze_graph);
	return 1;
}

Graph *New_Graph() {
	Graph *graph = 0; //�ڵ���Ģ.
	graph = (Graph *)malloc(sizeof(Graph));
	graph->vertexs = New_Array();
	graph->edges = New_Array();
	return graph;
}

Vertex *New_Vertex(int name, int x, int y) {
	Vertex *vertex = 0;
	vertex = (Vertex *)malloc(sizeof(Vertex));
	vertex->name = name;
	vertex->x = x;
	vertex->y = y;
	vertex->parent = 0;

	return vertex;
}

Edge *New_Edge(Vertex *vt1, Vertex *vt2, int weight) {
	Edge *edge = 0;
	edge = (Edge *)malloc(sizeof(Edge));
	edge->vt1 = vt1;
	edge->vt2 = vt2;
	edge->weight = weight;
	return edge;
}

void Delete_Graph(Graph *graph) {
	Iterator seek = 0, end = 0;
	Edge *dege = 0;

	//seek = Array_Begin(graph);
}

int Graph_AddVertex(Graph *graph, int name, int x, int y) {
	if (Graph_ExistVertex(graph, x, y)) {
		return 0;
	}

	Vertex *vertex = 0;
	vertex = New_Vertex(name, x, y);
	Array_PushBack(graph->vertexs, vertex);

	return 1;
}

Vertex *Graph_GetVertex(Graph *graph, int x, int y) {
	Iterator seek = 0, end = 0;
	Vertex *stored_pt = 0;
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		stored_pt = (Vertex *)(*seek);

		if (stored_pt->x == x && stored_pt->y == y) {
			return stored_pt;
		}
	}

	return 0;
}

int Graph_AddEdge(Graph *graph, Vertex *vt1, Vertex *vt2, int weight) {
	if (Graph_ExistVertex(graph, vt1->x, vt1->y) && Graph_ExistVertex(graph, vt2->x, vt2->y)) {
		Edge *edge = 0; //������ �����ϱ� ���� �ڵ���Ģ.

		if (Graph_ExistEdge(graph, vt1, vt2))
			return 0; //�̹� �� vertex ���� edge�� �����Ѵٸ� �����մϴ�.
		//�� ��
		edge = New_Edge(vt1, vt2, weight);
		Array_PushBack(graph->edges, edge);

		return 1;
	}
	return 0;
}

int Graph_ExistVertex(Graph *graph, int x, int y) {
	Iterator seek = 0, end = 0;
	Vertex *stored_pt = 0;
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		stored_pt = (Vertex *)(*seek);

		if (stored_pt->x == x && stored_pt->y == y) {
			return 1; //true�� ���� 1�� ����.
		}
	}
	return 0;
}

Vertex *Graph_GetVertexByName(Graph *graph, int vt_name) {
	Iterator seek = 0, end = 0;
	Vertex *stored_pt = 0;
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		stored_pt = (Vertex *)(*seek);

		if (stored_pt->name == vt_name) {
			return stored_pt; //true�� ���� 1�� ����.
		}
	}
	return 0; //means NULL
}

Vertex *Graph_GetVertexByXY(Graph *graph, int x, int y) {
	Iterator seek = 0, end = 0;
	Vertex *stored_pt = 0;
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		stored_pt = (Vertex *)(*seek);

		if (stored_pt->x == x && stored_pt->y == y) {
			return stored_pt;
		}
	}

	return 0;
}

void Graph_ViewVerexs(Graph *graph) {

	Iterator seek = 0, end = 0;
	Vertex *vt = 0;
	printf("���� ����:%d\n", graph->vertexs->usage);
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		vt = (Vertex *)(*seek);
		printf("%d: x: %d y: %d\n", vt->name, vt->x, vt->y);
	}
}

void Array_View(Array *array) {
	Iterator seek = 0, end = 0;
	Vertex *vt = 0;
	seek = Array_Begin(array);
	end = Array_End(array);

	for (seek = seek; seek != end; ++seek) {
		vt = (Vertex *)(*seek);
		printf("[%d] x: %d y: %d\n", vt->name, vt->x, vt->y);
	}
}

void Graph_ViewEdges(Graph *graph) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	printf("���� ����:%d\n", graph->edges->usage);
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		printf("(%d, %d): %d\n", edge->vt1->name, edge->vt2->name, edge->weight);
	}
}

int Graph_ExistEdge(Graph *graph, Vertex *vt1, Vertex *vt2) {
	Iterator seek = 0, end = 0;
	Edge *stored_eg = 0;
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	for (seek = seek; seek != end; ++seek) {
		stored_eg = (Edge *)(*seek);
		if (Edge_Include(stored_eg, vt1->name) && Edge_Include(stored_eg, vt2->name)) {
			return 1; //true�� ��Ÿ���� ���� 1�� ����.
		}
	}
	return 0;
}

int Edge_Include(Edge *edge, int vt_name) {
	return (edge->vt1->name == vt_name) || (edge->vt2->name == vt_name);
}

Vertex *Edge_AnOther(Edge *edge, int vt_name) {
	if (edge->vt1->name == vt_name) {
		return edge->vt2;
	}

	if (edge->vt2->name == vt_name) {
		return edge->vt1;
	}
	return NULL;
}

void Graph_FindNeighbor(Graph *graph, int vt_name, Array *neighbor) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, vt_name)) {
			Vertex *opt;
			opt = Edge_AnOther(edge, vt_name);
			Array_PushBack(neighbor, opt);
		}
	}
}

void Graph_ViewVertexs(Graph *graph) {
	Iterator seek = 0, end = 0;
	Vertex *vt = 0;
	//printf("���� ����:%d\n", graph->vertexs->usage);
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		vt = (Vertex*)(*seek);
		printf("[%d] (%d, %d)\n", vt->name, vt->x, vt->y);
	}
}

int Graph_SetEnd(Graph *graph) {
	int input = 0;
	Vertex *vt = 0;

	Maze_Draw_Debug();

	printf("�Ѹ� �����ϼ���: \n");
	Graph_ViewVertexs(maze_graph);
	scanf_s("%d", &input);
	if (input == 1) {
		printf("�������Դϴ�.\n");
		exit(-1);
	}
	else {
		vt = Graph_GetVertexByName(maze_graph, input);
		maze[vt->x + vt->y * width].c = "��";
	}

	Maze_Draw_Debug();

	return 1;
}

int Graph_GetWeight(Graph *graph, Vertex *vt1, Vertex *vt2) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, vt1->name) && Edge_Include(edge, vt2->name)) {
			return edge->weight;
		}
	}

	return -1;
}

Vertex *Graph_GetStartV(Graph *graph) {
	Node *iter = 0;
	iter = maze;
	while (iter->c != "��")
		iter++;
	return Graph_GetVertexByXY(maze_graph, iter->x, iter->y);
}

Vertex *Graph_GetEndV(Graph *graph) {
	Node *iter = 0;
	iter = maze;
	while (iter->c != "��")
		iter++;
	return Graph_GetVertexByXY(maze_graph, iter->x, iter->y);
}

int Graph_GetCost(Array *route) {
	int count = 0;
	int weight = 0;

	Array_View(route);
	count = route->usage;
	while (count != 1) {
		weight += Graph_GetWeight(maze_graph, Array_GetAt(route, count), Array_GetAt(route, --count));
		printf("(%d -> %d)'s cost: %d\n", count + 1, count, weight);
	}
	printf("cost: %d\n", weight);
	return 1;
}

