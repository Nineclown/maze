#include "rhand.h"

int right_count = 0;
void right(int *dir)
{
	*dir <<= 1;
	*dir = (*dir > LEFT) ? UP : *dir;
}
void left(int *dir)
{
	*dir >>= 1;
	*dir = (*dir == 0) ? LEFT : *dir;
}

void forward(int *x, int *y, int dir)
{

	*x = (dir == LEFT) ? --(*x) :
		(dir == RIGHT) ? ++(*x) : *x;
	*y = (dir == UP) ? --(*y) :
		(dir == DOWN) ? ++(*y) : *y;

}
Node* Wall_ahead(Node *maze, int x, int y, int dir)
{
	Node *target = 0;
	target = maze;
	x = (dir == LEFT) ? --x :
		(dir == RIGHT) ? ++x : x;
	y = (dir == UP) ? --y :
		(dir == DOWN) ? ++y : y;
	target->x = x;
	target->y = y;
	right_count++;
	return target;
}
int still_in_maze(int x, int y)
{
	if (x>0 && x<width - 1 && y>0 && y< height - 1)
		return 1;
	else
		return 0;
}

void right_hand(Node *maze, int x, int y, int dir)
{
	forward(&x, &y, dir);
	while (still_in_maze(x, y))
	{
		if (right_count == 100)
		{
			printf("No way..\n ");
			exit(1);
		}
		right(&dir);
		while (Wall_ahead(maze, x, y, dir))
			left(&dir);
		forward(&x, &y, dir);
	}

}
