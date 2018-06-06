#include "dijkstra.h"
#define INF 100

void dijkstra(Graph *graph) {
	int n = graph->vertexs->usage;
	int i, j;
	int min;
	int v;
	int *dist;
	int *visit;
	int start = 0;
	int end = 0;
	int weight = 0;
	
	dist = (int*)calloc(n + 1, sizeof(int));
	visit = (int*)calloc(n + 1, sizeof(int));

	for (i = 1; i <= n; i++)
		dist[i] = INF;


	start = Graph_GetStartV(graph)->name;
	end = Graph_GetEndV(graph)->name;
	dist[start] = 0;        // 시작점의 거리 0
	//printf("start, end: %d, %d\n", start, end);

	for (i = 1; i <= n; i++) {
		min = INF;

		for (j = 1; j <= n; j++) {
			if (visit[j] == 0 && min > dist[j]) {   // 갈수 있는 정점중에 가장 가까운 정점 선택
				min = dist[j];
				v = j;
			}
		}
		visit[v] = 1;   // 가장 가까운 정점으로 방문, i정점에서 가장 가까운 최단경로 v

		for (j = 1; j <= n; j++) {
			weight = Graph_GetWeight(graph, Graph_GetVertexByName(graph, v), Graph_GetVertexByName(graph, j));
			if (-1 == weight) {
				continue;
			}
			if (dist[j] > dist[v] + weight) {      // 방문한 정점을 통해 다른 정점까지의 거리가 짧아지는지 계산하여 누적된값 저장
				dist[j] = dist[v] + weight;
				//printf("dist[%d] = dist[%d] + weight: %d\n",j, v, weight);
			}
		}
	}
	printf("%d\n", dist[end]);
}