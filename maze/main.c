#include "util.h"
#include "gen_maze.h"
#include "graph.h"

int main() {
	int i = 0, j = 0;
	Graph *graph = New_Graph();
	Array *neighbor = New_Array();

	//start maze.
	genMaze(1, 1);

	//start game
	//runMiniGame();
	printf("is it? %s", maze[1 + 1 * width].c);

	//�ϴ� ���������� �˻縦 �����Ѵ�.
	//��������? ��� �̷��� ���� 1�� �� ������.
	//�߰��� �б����� �����(���� 1���� �Ǵ� ���� 3�̻�) �� ��ġ�� �����̳� ť�� �����Ѵ�
	//�̷��� dirs ���� �ϴ� �ʱ�ȭ ���Ѻ���

	Node * iter;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			iter = maze + i + j * width;
			if (iter->c != "��")
				iter->dirs = 15;
		}
	}

	//�Է¹��� ���(���� ���n)�� �̿� ��带 �����մϴ�. �̿� ��带 ��ȯ�մϴ�. 

	int x, y; //�̿� ����� ��ǥ ���� ���� �����Դϴ�.
	char dir; //��� n�� �湮�� ������ ���� �����Դϴ�.
	Node *dest; //�̿� ��带 ����ų ������ �����Դϴ�.
	Node *n = NULL;
	//��� n�� �߸��� ���.
	//if (n == NULL) return NULL;

	//��� n�� ���� �湮�� ������ �����ִ� ���, ��� ������ �湮�� ������ �ݺ��մϴ�.
	int count = 0;
	while (n->dirs) {

		dir = 1 << count++;
		if (count > 3)
			DieWithError("��");

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
				y = n->y + 2;
			}
			else continue;
			break;

			//0010�� �Ʒ����Դϴ�.
		case 2:
			if (n->x + 2 < width) {
				x = n->x + 2;
				y = n->y;
			}
			else continue;
			break;

			//0100�� ���Դϴ�.
		case 4:
			if (n->y - 2 >= 0) {
				x = n->x;
				y = n->y - 2;
			}
			else continue;
			break;

			//1000�� �����Դϴ�.
		case 8:
			if (n->x - 2 >= 0) {
				x = n->x - 2;
				y = n->y;
			}
			else continue;
			break;
		}

		//�湮�ؼ� ã�Ƴ� �̿� ��带 dest�� ����ϴ�.
		dest = maze + x + y * width;

		//�̿� ��尡 ������ ������ Ȯ���մϴ�.
		if (dest->c == "��") { //�̿� ��尡 ���� ���.

							  //�̿� ��尡 �̹� �湮��(Ž����) ��쿣 �ٸ� �������� ���� ������ �ϹǷ� �ǵ��� ���ϴ�.
			if (dest->parent != NULL) continue;

			//�� ���� ���, �̿� ���� ��� n�� �����մϴ�.
			dest->parent = n;

			//�� ��带 ���θ��� ���� �����մϴ�.
			maze[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = "  ";
			//draw();

			//�̿� ����� ���� �νʴϴ�.
			maze[x + y * width].c = "  ";
			//draw();

			//�̿� ��带 ��ȯ�մϴ�.
			return dest;
		}
		else if (dest->c == "  ") { //�̿� ��尡 ���� ���.
			int ran = rand() % 10;	//�������� �� �վ�.

			if (!ran)
				maze[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = "  ";
			//draw();
		}
	}

	//��� ������ Ž�������� �̹� �ѹ��� �湮�� ���, �ǵ��� ���ϴ�. 
	//draw();
	return n->parent;


	Graph_AddVertex(graph, "S");
	Graph_AddEdge(graph, "J", "K", 3);

	Graph_FindNeighvor(graph, "A", neighbor);
	Iterator seek = 0, end = 0;
	Vertex pt = 0;
	seek = Array_Begin(neighbor);
	end = Array_End(neighbor);

	for (seek = seek; seek != end; ++seek) {
		pt = (Vertex)(*seek);
		printf("%s\n", pt);
	}


	//Graph_View(graph);

	Delete_Graph(graph);
	return 0;

}

