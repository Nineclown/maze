#include "rhs.h"

#define R 1
#define D 2
#define L 4
#define U 8

void RHS_Right(char *dir) {
	*dir <<= 1;
	*dir = (*dir == 16) ? R : *dir;
}

void RHS_Left(char *dir) {
	*dir >>= 1;
	*dir = (*dir == 0) ? U : *dir;
}

void RHS_Forward(int *x, int *y, char dir) {
	*x = (dir == U) ? --(*x) : (dir == D) ? ++(*x) : *x;
	*y = (dir == L) ? --(*y) : (dir == R) ? ++(*y) : *y;
	//printf("(%d, %d)로 이동. 방향: %d\n", *x, *y, dir);
}

int RHS_Wall_Ahead(Node *maze, int x, int y, char dir) {
	x = (dir == U) ? --x : (dir == D) ? ++x : x;
	y = (dir == L) ? --y : (dir == R) ? ++y : y;

	return (maze[x + y * width].c == "■");
}

int RHS_FindEnd(int x, int y) {
	if (maze[x + y * width].c == "ⓔ")
		return 1;
	else
		return 0;
}

void RHS(int x, int y, char dir) {
	int count = 0;

	Node *start = 0;
	start = (Node*)malloc(sizeof(Node));
	start->parent = 0;
	start->x = x;
	start->y = y;
	start->dirs = dir;

	while (!RHS_FindEnd(x, y)) {
		RHS_Right(&dir);
		while (RHS_Wall_Ahead(maze, x, y, dir)) {
			RHS_Left(&dir);
		}
		RHS_Forward(&x, &y, dir);
		count++;

		if (count > 150) {
			//printf("cycle!\n");
			count = 9999;
			break;
		}
	}
	free(start);

	al_cost[0] = count;
	//printf("비용: %d\n", al_cost[0]);
}
