#include "util.h"

//���ϰ� �Է°� ���, �Լ� ������ �˻��ϱ� ���� �Լ���
void DieWithError(char* errorMessage) {
	perror(errorMessage);
	exit(1);
}

//������ ������ ���� �Լ���

int runMiniGame() {
	// game
	system("cls");
	removeCursor();
	setCursor(0,0);
	Maze_Draw_Release();
	//showBoard();
	character_static();
	getchar();

	return 0;
}

void setCursor(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD getCursor(void) {
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO pos;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pos);
	curPoint.X = pos.dwCursorPosition.X;
	curPoint.Y = pos.dwCursorPosition.Y;
	return curPoint;
}

void removeCursor(void) {
	CONSOLE_CURSOR_INFO cur;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
	cur.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

void showBoard(void) {
	int x = 0, y = 0;
	//COORD cur = getCursor();

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			//setCursor(cur.X + (x * 2), cur.Y + y);
			printf("%s", maze[x + y * width].c);
		}
		printf("\n");
	}
	//setCursor(cur.X, cur.Y);
	//checkMouse(&x, &y);
	//maze[x + y * width].c = "��";
	//draw();
}

void character_static(void) {
	int kb;

	GAME = 1;
	setCursor(2, 1);  //�ɸ��� ������ġ
	while (GAME) {
		while (!_kbhit()) {
			showCharacter();
			Sleep(100);
		}
		kb = _getch();
		switch (kb) {
		case UP:
			RemoveCharacter_Set(0, -1);
			break;
		case DOWN:
			RemoveCharacter_Set(0, 1);
			break;
		case RIGHT:
			RemoveCharacter_Set(2, 0);
			break;
		case LEFT:
			RemoveCharacter_Set(-2, 0);
			break;
		}
	}
}

void showCharacter(void) {
	COORD cur = getCursor();

	printf("��");
	setCursor(cur.X, cur.Y);

}

void RemoveCharacter_Set(int x, int y) {
	int value = detect(x, y);

	if (value == 0) {
		COORD cur = getCursor();

		printf("  ");
		setCursor(cur.X + x, cur.Y + y);
	}
	else if (value == 2) {
		setCursor(1, width);
		printf("����!\n");
		GAME = 0;
	}
}

int detect(int x, int y) {
	int x1 = 0;
	int y1 = 0;

	// Ŀ�� ��ġ ��� 
	COORD cur = getCursor();

	// �̷γ������� ��ġ ���.
	y1 = cur.X + x;
	x1 = cur.Y + y;
	x1 = x1;
	y1 = y1 / 2;

	// �̷� �ۿ� �ִ���?
	//printf("%d + %d\n", x1, y1);
	if (!((x1 > 0 && x1 < width - 1) && (y1 > 0 && y1 < height - 1)))
		return 1;

	//�迭�� �Ѿ�� �ʴ�����?
	//printf("maze[%d + %d * width].c\n", x1, y1);
	if ((maze[x1 + y1 * width].c) == "��")
		return 1;

	//�̼Ǽ���
	else if (maze[x1 + y1 * width].c == "��")
		return 2;
	else
		return 0;
}