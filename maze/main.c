#include"util.h"
#include "graph.h"

int main() {
	Node *start, *last;
	int x, y;

	//Seed random generator
	srand(time(NULL));

	//Initialize maze	
	if (chkInvalidInput(&x, &y) != 0)
		DieWithError("error");

	//Setup start node
	start = nodes + 1 + width;
	start->parent = start;
	start->c = 'S';
	last = start;

	char a = 64;
	//Connect nodes until start node is reached and can't be left
	//시작점에서 출발해서 모든 0을 다 탐색하고 다시 start로 돌아온다.
	while ((last = link(last)) != start) {
		last->c = ++a;
	}
	
	printf("setup end\n");
	//결과.
	draw();
	
	return 0;
}

int main2()

{

	Graph *graph = New_Graph();
	Array *neighbor = New_Array();

	Graph_AddVertex(graph, "S");
	Graph_AddVertex(graph, "A");
	Graph_AddVertex(graph, "B");
	Graph_AddVertex(graph, "C");
	Graph_AddVertex(graph, "D");
	Graph_AddVertex(graph, "E");
	Graph_AddVertex(graph, "F");
	Graph_AddVertex(graph, "G");
	Graph_AddVertex(graph, "H");
	Graph_AddVertex(graph, "I");
	Graph_AddVertex(graph, "J");
	Graph_AddVertex(graph, "K");

	Graph_AddEdge(graph, "S", "A", 7);
	Graph_AddEdge(graph, "A", "B", 3);
	Graph_AddEdge(graph, "B", "C", 5);
	Graph_AddEdge(graph, "C", "D", 3);
	Graph_AddEdge(graph, "D", "E", 3);
	Graph_AddEdge(graph, "E", "F", 3);
	Graph_AddEdge(graph, "E", "G", 3);
	Graph_AddEdge(graph, "G", "H", 5);
	Graph_AddEdge(graph, "H", "I", 3);
	Graph_AddEdge(graph, "I", "J", 3);
	Graph_AddEdge(graph, "J", "K", 3);

	//Graph_FindNeighvor(graph, "A", neighbor);
	//printf("%s", );


	Graph_View(graph);

	Delete_Graph(graph);

	

	return 0;

}
