#include "bfs.h"

int BFS(Graph * graph, int start) {
	Array *visited = New_Array();
	Array *neighbor = New_Array();
	Vertex *currentVertex = 0;

	currentVertex = Graph_GetVertexByName(maze_graph, start);

	//visited
	Array_PushBack(visited, (Element)currentVertex); //현재 정점(실제론 시작 정점)를 방문했다고 visited 배열에 담습니다.
	
	//neighbor
	BFS_AddNeighbor(maze_graph, currentVertex, neighbor, visited); //현재 정점과 인접한 정점들을 neighbor 배열에 담습니다.
	
	while (!Array_IsEmpty(neighbor)) { //neighbor 배열이 빌 때까지 반복합니다. //도착점이 생기면 도착점에 도달할 때까지 탐색을하면 됩니다.
		
		//dequeue
		currentVertex = (Vertex*)(*Array_Begin(neighbor)); //neighbor 배열의 인덱스가 0인(처음) 정점을 가져옵니다. 배열을 큐로 사용합니다.
														   //
		//visited
		Array_PushBack(visited, (Element)currentVertex); //가져온 정점을 방문했다고 visited 배열에 담습니다.

		//도착지를 방문했다면 BFS search를 종료합니다.
		if (maze[currentVertex->x + currentVertex->y * width].c == "ⓔ") {
			//printf("find way!\n");
			Array_Erase(neighbor, (Iterator)Array_Begin(neighbor)); //배열에 값을 제거합니다.
			break;
		}
		Array_Erase(neighbor, (Iterator)Array_Begin(neighbor)); //배열에 값을 제거합니다.
		
		//enqueue
		BFS_AddNeighbor(maze_graph, currentVertex, neighbor, visited);//가져온 정점과 인접한 정점 중 방문하지 않은 정점들을 neighbor에 추가합니다.
	}
	//printf("BFS visited\n");
	//Array_View(visited);
	//printf("BFS routing\n");
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

	//Array_View(route);
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
	//printf("BFS calculating cost\n");
	while (count != 0) {
		vt1 = (Vertex *)(Array_GetAt(route, count));
		vt2 = (Vertex *)(Array_GetAt(route, --count));
		weight = Graph_GetWeight(maze_graph, vt1, vt2);
		total += weight;
		//printf("[%d] -> [%d] cost: %d\n", vt1->name, vt2->name, weight);
	}
	//printf("\n비용 : %d\n", total);
	al_cost[2] = total;
	return 1;
}

void BFS_AddNeighbor(Graph *graph, Vertex *vt, Array *neighbor, Array *visited) {
	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	seek = Array_Begin(graph->edges);
	end = Array_End(graph->edges);

	//그래프의 모든 간선을 다 탐색합니다.
	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);
		if (Edge_Include(edge, vt->name)) { //특정 간선이 타겟 정점을 갖고 있을 때,
			Vertex *opt; //인접한 정점.
			opt = Edge_AnOther(edge, vt->name); //이게 넘겨주는 게 주소이긴한데 복사한 값의 주소지 원래 값의 주소가 아니야.
			if (!BFS_CheckVisited(visited, opt) && !BFS_CheckVisited(neighbor, opt)) { //인접한 정점이 아직, 방문하지 않고 큐에 넣어지지도 않았다면,
				opt->parent = vt; //maze_graph의 정점을 가져다 씀.
				Array_PushBack(neighbor, (Element)opt);
				//printf("중간=neighbor==========\n");
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
			//printf("[%d]는 이미 방문한 or 방문할 예정입니다\n", target->name);
			return 1;
		}
	}
	return 0;
}