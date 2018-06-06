#include "gen_graph.h"

int Maze_ReInit() {
	int i = 0, j = 0;

	Node *iter;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			iter = maze + i + j * width;
			if (iter->c != "■") {
				iter->x = i;
				iter->y = j;
				if (iter->c == "ⓢ")
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
	//오른쪽 0001
	if (maze[n->x + (n->y + 1) * width].c != "■") {
		dirs += 1;
		count++;
	}
	//아래쪽
	if (maze[n->x + 1 + n->y * width].c != "■") {
		dirs += 2;
		count++;
	}
	//왼쪽
	if (maze[n->x + (n->y - 1) * width].c != "■") {
		dirs += 4;
		count++;
	}
	//위쪽
	if (maze[n->x - 1 + n->y * width].c != "■") {
		dirs += 8;
		count++;
	}
	n->dirs = dirs;

	//버택스 마크만 한다.
	if (count >= 3 || count <= 1) {
		if (n->c == "ⓢ") {
			//nothing
		}
		else
			n->c = "ⓥ";
	}

	return 1;
}

int Graph_SetVnE(Node *n) {
	int name = 0;

	name = maze_graph->vertexs->usage + 1; //vertex의 이름은 1부터 시작.

	if (n->c == "ⓥ" || n->c == "ⓢ") {
		//현재 vertex의 수는?
		//vertex의 수가 0일 경우<= 처음으로 찾음
		if (vertexs->usage == 0) {
			Graph_AddVertex(maze_graph, name, n->x, n->y);
			Array_PushBack(vertexs, (Element)Graph_GetVertexByName(maze_graph, name));
			COUNT = 0;//초기화.
		}

		//vertex의 수가 1일 경우 <= 이미 하나가 있을 때 다른 하나를 찾음
		//edge를 만든다.
		//처음 vertex는 지운다.
		//count를 0으로 초기화한다.
		else if (vertexs->usage == 1) {
			//vertex가 존재하지 않든 존재하든 일단 생성을 시도합니다.
			Graph_AddVertex(maze_graph, name, n->x, n->y);
	
			//그리고 현재 위치에 vertex가 생성되었거나 원래 있었거나 상관없이 Array에 담습니다.
			Array_PushBack(vertexs, (Element)Graph_GetVertex(maze_graph, n->x, n->y));
			//printf("배열 정보: [0]: %d, [1]: %d\n", ((Vertex *)Array_GetAt(vertexs, 0))->name, ((Vertex *)Array_GetAt(vertexs, 1))->name);
			
			//배열의 정보를 바탕으로 edge를 생성하는데, 이미 생성된 edge는 0이고 성공은 1이다.
			if (COUNT % 2)
				COUNT++;
			if (COUNT == 0)
				COUNT = 2;
			Graph_AddEdge(maze_graph, (Vertex*)(*Array_Begin(vertexs)), (Vertex*)(*(Array_End(vertexs) - 1)), COUNT);
			
			//그리고 나서 Array에 처음 들어온 놈은 지운다.
			Array_Erase(vertexs, (Iterator)Array_Begin(vertexs));
			COUNT = 0;
		}
	}

	return 1;
}

Node *Graph_Link(Node *n) {

	Graph_SetVnE(n);
	//이제는 길을 연결하는 작업.
	int x = 0, y = 0; //이웃 노드의 좌표 값을 담을 변수입니다.
	char dir = 0; //노드 n이 방문할 방향을 담을 변수입니다.
	Node *dest = 0; //이웃 노드를 가리킬 포인터 변수입니다.
	int count = 0;
	//노드 n이 잘못된 경우.
	if (n == NULL) return NULL;

	//노드 n이 아직 방문할 방향이 남아있는 경우, 모든 방향을 방문할 때까지 반복합니다.
	while (n->dirs) {
		if (count >= 4)
			DieWithError("rr");
		dir = (1 << count++);

		//이미 노드 n이 방문한 방향인 경우,
		if (~n->dirs & dir) continue;

		//노드 n의 dir값에 방문 표시를 남깁니다.
		n->dirs &= ~dir;

		//방문합니다.
		switch (dir) {
			//0001은 오른쪽입니다.
		case 1:
			if (n->y + 1 < height - 1) {
				x = n->x;
				y = n->y + 1;
			}
			else continue;
			break;

			//0010은 아래쪽입니다.
		case 2:
			if (n->x + 1 < width - 1) {
				x = n->x + 1;
				y = n->y;
			}
			else continue;
			break;

			//0100은 왼입니다.
		case 4:
			if (n->y - 1 > 0) {
				x = n->x;
				y = n->y - 1;
			}
			else continue;
			break;

			//1000은 위쪽입니다.
		case 8:
			if (n->x - 1 > 0) {
				x = n->x - 1;
				y = n->y;
			}
			else continue;
			break;
		}

		//방문해서 찾아낸 이웃 노드를 dest에 담습니다.
		dest = maze + x + y * width;

		//이웃 노드가 이미 방문된(탐색된) 경우엔 다른 방향으로 길을 만들어야 하므로 되돌아 갑니다.
		if (dest->parent != NULL) {
			if (dest->c == "ⓥ") {
				Array_PushBack(vertexs, (Element)Graph_GetVertex(maze_graph, dest->x, dest->y));
				if (COUNT % 2)
					COUNT++;
				if (COUNT == 0)
					COUNT = 2;
				if (Graph_AddEdge(maze_graph, (Vertex*)(*Array_Begin(vertexs)), (Vertex *)(*(Array_End(vertexs) - 1)), COUNT)) {
					//printf("edge추가(%d - %d)\n", ((Vertex*)*Array_Begin(vertexs))->name, ((Vertex*)*(Array_End(vertexs) - 1))->name);
				}
				Array_Erase(vertexs, Array_Begin(vertexs));
				COUNT = 0;
			}
			continue;
			
		}
		//그 외의 경우, 이웃 노드와 노드 n을 연결합니다.
		dest->parent = n;
		COUNT++;
		//draw();
		//이웃 노드를 반환합니다.
		return dest;
	}

	//모든 방향을 탐색했지만 이미 한번씩 방문한 경우, 되돌아 갑니다. 
	//draw();
	return n->parent;
}

int Graph_Generating() {
	Node *start = 0;
	Node *last = 0;
	Node *iter = 0;
	Array *neibor = New_Array();
	//그래프 요소들 초기화.
	maze_graph = New_Graph();
	vertexs = New_Array();
	Array_SetSize(vertexs, 0, 0);

	//미로 --> 그래프 변환
	Maze_ReInit();
	//Maze_Draw();
	Maze_Draw();

	//미로에서 시작점을 찾습니다.
	iter = maze;
	while (iter->c != "ⓢ")
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

int Graph_ExistVertex(Graph *graph, int x, int y) {
	Iterator seek = 0, end = 0;
	Vertex *stored_pt = 0;
	seek = Array_Begin(graph->vertexs);
	end = Array_End(graph->vertexs);

	for (seek = seek; seek != end; ++seek) {
		stored_pt = (Vertex *)(*seek);

		if (stored_pt->x == x && stored_pt->y == y) {
			return 1; //true를 위해 1을 리턴.
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
			return stored_pt; //true를 위해 1을 리턴.
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
	printf("정점 개수:%d\n", graph->vertexs->usage);
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

	printf("간선 개수:%d\n", graph->edges->usage);
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
			return 1; //true를 나타내기 위해 1를 리턴.
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
	//printf("정점 개수:%d\n", graph->vertexs->usage);
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

	printf("ⓔ를 설정하세요: \n");
	Graph_ViewVertexs(maze_graph);
	scanf_s("%d", &input);
	if (input == 1) {
		printf("시작점입니다.\n");
		exit(-1);
	}
	else {
		vt = Graph_GetVertexByName(maze_graph, input);
		maze[vt->x + vt->y * width].c = "ⓔ";
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
	while (iter->c != "ⓢ")
		iter++;
	return Graph_GetVertexByXY(maze_graph, iter->x, iter->y);
}

Vertex *Graph_GetEndV(Graph *graph) {
	Node *iter = 0;
	iter = maze;
	while (iter->c != "ⓔ")
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

