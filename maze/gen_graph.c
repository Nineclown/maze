#include "gen_graph.h"


int Maze_ReInit() {
	int i = 0, j = 0;

	//초기화.
	NUM = 10;
	Node * iter;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			iter = maze + i + j * width;
			if (iter->c != "■") {
				Maze_FindDir(iter);
			}
		}
	}
	return 1;
}

int Maze_FindDir(Node *n) {
	char dirs = 0;
	int count = 0;
	//오른쪽 0001
	if (maze[n->x + (n->y - 1) * width].c != "■") {
		dirs += 1;
		count++;
	}
	//위쪽
	if (maze[n->x - 1 + n->y * width].c != "■") {
		dirs += 2;
		count++;
	}
	//왼쪽
	if (maze[n->x + (n->y + 1) * width].c != "■") {
		dirs += 4;
		count++;
	}
	//아래쪽
	if (maze[n->x + 1 + n->y * width].c != "■") {
		dirs += 8;
		count++;
	}
	n->dirs = dirs;

	if (count >= 3 || count <= 1) {
		//이 때는 반드시 vertex가 만들어져야 한다.
		Graph_AddVertex(maze_graph, NUM++, n->x, n->y);
		if (n->c == "ⓢ") {
		}
		else if (count == 1) {
			n->c = "ⓔ";
		}
		else
			n->c = "ⓥ";

	}

	return 1;
}

Graph *New_Graph() {
	Graph *graph = 0; //코딩규칙.
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

	return vertex;
}

Edge *New_Edge(Vertex vt1, Vertex vt2, int weight) {
	Edge *edge = 0;
	edge = (Edge *)malloc(sizeof(Edge));
	edge->vt1 = vt1;
	edge->vt2 = vt2;
	edge->weight = weight;
	return edge;
}

void Delete_Graph(Graph * graph) {
	Iterator seek = 0, end = 0;
	Edge *dege = 0;

	//seek = Array_Begin(graph);
}

int Graph_AddVertex(Graph *graph, int name, int x, int y) {
	if (Graph_ExistVertex(graph, name)) {
		return 0;
	}

	Vertex *vertex = 0;
	vertex = New_Vertex(name, x, y);
	Array_PushBack(graph->vertexs, vertex);

	return 1;
}

int Graph_AddEdge(Graph *graph, Vertex vt1, Vertex vt2, int weight) {
	if (Graph_ExistVertex(graph, vt1.name) && Graph_ExistVertex(graph, vt2.name)) {
		Edge *edge = 0; //간선을 생성하기 위한 코딩규칙.

		if (Graph_ExistEdge(graph, vt1, vt2))
			return 0; //이미 두 vertex 간의 edge가 존재한다면 실패합니다.
		//그 외
		edge = New_Edge(vt1, vt2, weight);
		Array_PushBack(graph->edges, edge);
		
		return 1;
	}
	return 0;
}

int Graph_ExistVertex(Graph *graph, int vt_name) {
	Iterator seek = 0, end = 0;
	Vertex *stored_pt = 0;
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		stored_pt = (Vertex *)(*seek);

		if (stored_pt->name ==  vt_name) {
			return 1; //true를 위해 1을 리턴.
		}
	}
	return 0;
}

void Graph_ViewVerexs(Graph *graph) {

	Iterator seek = 0, end = 0;
	Vertex *vt = 0;
	printf("정점 개수:%d\n", graph->vertexs->usage);
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		vt = (Vertex *)(*seek);
		printf("%d\n", vt->name);
	}
}


int Graph_ExistEdge(Graph *graph, Vertex vt1, Vertex vt2) {
	Iterator seek = 0, end = 0;
	Edge *stored_eg = 0;
	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	for (seek = seek; seek != end; ++seek) {
		stored_eg = (Edge *)(*seek);
		if (Edge_Include(stored_eg, vt1) && Edge_Include(stored_eg, vt2)) {
			return 1; //true를 나타내기 위해 1를 리턴.
		}
	}
	return 0;
}

int Edge_Include(Edge *edge, Vertex vt) {
	return (edge->vt1.name == vt.name) || (edge->vt2.name == vt.name);
}

