#include "util.h"

//���ϰ� �Է°� ���, �Լ� ������ �˻��ϱ� ���� �Լ���
void DieWithError(char* errorMessage) {
	perror(errorMessage);
	exit(1);
}

int chkInvalidInput(int *x, int *y) {
	if ((scanf_s("%d", x) + scanf_s("%d", y)) < 2) {
		perror("invalid maze type!\n");
		exit(1);
	}
	if (init(x, y)) {
		perror("calloc failed. parameter ");
		exit(1);
	}

	if (!(width % 2) || !(height % 2)) {
		perror("faild");
		exit(1);
	}
	if (width <= 0 || height <= 0) {
		perror("faild");
		exit(1);
	}
	return 0;
}


//������ ������ ���� �Լ���
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

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			//setCursor(cur.X + (x * 2), cur.Y + y);
			printf("%s", maze[x + y * width].c);
		}
		printf("\n");
	}
	
	//checkMouse(&x, &y);
	//maze[x + y * width].c = "��";
	//draw();
}

void character_static(void) {
	int kb;
	setCursor(2, 1);  //�ɸ��� ������ġ
	while (1) {
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
		setCursor(24, 24);
		printf("����!");
		system("pause");
		exit(1);
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


void checkMouse(int *x, int *y) {

	INPUT_RECORD rec;
	DWORD        dwNOER;

	while (1)
	{
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // �ܼ�â �Է��� �޾Ƶ���.
		if (rec.EventType == MOUSE_EVENT) // ���콺 �̺�Ʈ�� ���
		{
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) // ���� ��ư�� Ŭ���Ǿ��� ���
			{
				*x = rec.Event.MouseEvent.dwMousePosition.X; // X�� �޾ƿ�
				*y = rec.Event.MouseEvent.dwMousePosition.Y; // Y�� �޾ƿ�
				COORD Coor = { 0, 0 };
				DWORD dw;
				FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 80 * 25, Coor, &dw); // �ܼ�â ȭ���� �����.
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coor); // Ŀ���� 0, 0���� �̵���Ų��.
				printf("%d, %d", *x, *y); // ��ǥ�� ����Ѵ�.
				return;
			}
		}
	}
}