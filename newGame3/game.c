#include "main.h"
#include "game.h"
#include "displayControl.h"
#include "map.h"

typedef struct {
	int x, y;
	int exist;
} BULLET;

int keyControl()
{
	if (_kbhit() == 1) {
		unsigned char temp = _getch();

		if (temp == SPECIAL1 || temp == SPECIAL2) {
			temp = _getch();
			switch (temp) {
			case UP:
				return UP;
				break;
			case DOWN:
				return DOWN;
				break;
			case LEFT:
				return LEFT;
				break;
			case RIGHT:
				return RIGHT;
				break;
			}
		}
		else if (temp == 'w' || temp == 'W')
			return UP2;
		else if (temp == 's' || temp == 'S')
			return DOWN2;
		else if (temp == 'a' || temp == 'A')
			return LEFT2;
		else if (temp == 'd' || temp == 'D')
			return RIGHT2;
		else if (temp == ESC)
			exit(1);
		else if (temp == ' ')
			return ATTACK;
	}
}

int keyMenuControl()
{	
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
		return UP2;
	else if (temp == 's' || temp == 'S')
		return DOWN2;
	else if (temp == ESC)
		exit(1);
	else if (temp == ' ')
		return SUBMIT;
}

int move(int* x, int* y, int _x, int _y)
{
	char mapObject = tempMap[*y + _y][*x + _x];

	//�̵��� ��ҿ� ��ֹ��� �ִ��� Ȯ��
	if (mapObject == '0') {
		tempMap[*y][*x] = '0';
		tempMap[*y + _y][*x + _x] = 'p';
		*x += _x;
		*y += _y;
		return TRUE;
	}
	return FALSE;
}

void attack(int* x, int* y, int _x, int _y, char wh) {

	int xData = *x + _x;
	int yData = *y + _y;
	char mapObject = tempMap[yData][xData];

	while (TRUE) {
		if (tempMap[yData][xData] != '0')
			break;
		tempMap[yData][xData] = wh;
		yData += _y;
		xData += _x;
		mapObject = tempMap[yData][xData];
	}
}

void endAttack(int* x, int* y, int _x, int _y, char wh) {
	int xData = *x + _x;
	int yData = *y + _y;
	char mapObject = tempMap[yData][xData];

	while (TRUE) {
		if (tempMap[yData][xData] != wh)
			break;
		tempMap[yData][xData] = '0';
		yData += _y;
		xData += _x;
		mapObject = tempMap[yData][xData];
	}
}

void userData(int* x, int* y) {
	for (int h = 0; h < 20; h++) {
		for (int w = 0; w < 99; w++) {
			if (tempMap[h][w] == 'p') {
				*x = w;
				*y = h;
				return;
			}
		}
	}
}

void drawMap(int* x, int* y)
{
	//���� ������ �ʱ�ȭ
	scr_clear();
	//�׵θ� �׸���
	border();
	gotoxy(MAPXSTART, 1);
	//�÷��̾� ���� x�� �ּ�, �ִ� | y�� �ּ� �ִ� ����
	int hLow, hHigh, wLow, wHigh;

	//��, �Ʒ�, ����, ������ ������ ������ �۾��� �κи�ŭ �ݴ��� �� ũ�� �ø���
	int hUpDif = 0, hDownDif = 0, wLeftDif = 0, wRightDif = 0;
	int i = 1;

	//���� �ּ�, �ִ밪 ����
	if (*y - MAPYHALF < 0) {
		hLow = 0;
		hUpDif = 0 - (*y - MAPYHALF);
	}
	else
		hLow = *y - MAPYHALF;

	if (*y + MAPYHALF > MAPYMAX) {
		hHigh = MAPYMAX;
		hDownDif = (*y + MAPYHALF) - MAPYMAX;
		hLow = hLow - hDownDif;
	}
	else
		hHigh = *y + MAPYHALF + hUpDif;

	if (*x - MAPXHALF < 0) {
		wLow = 0;
		wLeftDif = 0 - (*x - MAPXHALF);
	}
	else
		wLow = *x - MAPXHALF;

	if (*x + MAPXHALF > MAPXMAX) {
		wHigh = MAPXMAX;
		wRightDif = (*x + MAPXHALF) - MAPXMAX;
		wLow = wLow - wRightDif;
	}
	else
		wHigh = *x + MAPXHALF + wLeftDif;

	//�� �׸���
	for (int h = hLow; h <= hHigh; h++) {
		for (int w = wLow; w <= wHigh; w++) {
			char temp = tempMap[h][w];
			if (temp == '0') {
				printscr("  ");
			}
			else if (temp == '1') {
				printscr("��");
			}
			else if (temp == 'p') {
				*x = w;
				*y = h;
				printscr("��");
			}
			else if (temp == 'w') {
				printscr("��");
			}
			else if (temp == 'h') {
				printscr("��");
			}
		}
		i++;
		gotoxy(MAPXSTART, i);
	}

	//����, ���� ��ȯ
	scr_switch();
}



void game() {

	int x;
	int y;
	int changeData = TRUE;

	//���� ���۽� �÷��̾� ��ġ ��������
	userData(&x, &y);

	while (1) {
		//ĳ���� �����ӿ� ��ȭ�� ������ �� �ٽ� �׸���
		if (changeData == TRUE)
			drawMap(&x, &y);

		int keyData = keyControl();

		switch (keyData) {
			//��, �Ʒ�, ����, ������ �̵�
		case UP2:
			changeData = move(&x, &y, 0, -1);
			break;
		case DOWN2:
			changeData = move(&x, &y, 0, 1);
			break;
		case LEFT2:
			changeData = move(&x, &y, -1, 0);
			break;
		case RIGHT2:
			changeData = move(&x, &y, 1, 0);
			break;
		case UP:
			attack(&x, &y, 0, -1, 'h');
			drawMap(&x, &y);
			Sleep(50);
			endAttack(&x, &y, 0, -1, 'h');
			drawMap(&x, &y);
			break;
		case DOWN:
			attack(&x, &y, 0, 1, 'h');
			drawMap(&x, &y);
			Sleep(50);
			endAttack(&x, &y, 0, 1, 'h');
			drawMap(&x, &y);
			break;
		case LEFT:
			attack(&x, &y, -1, 0, 'w');
			drawMap(&x, &y);
			Sleep(50);
			endAttack(&x, &y, -1, 0, 'w');
			drawMap(&x, &y);
			break;
		case RIGHT:
			attack(&x, &y, 1, 0, 'w');
			drawMap(&x, &y);
			Sleep(50);
			endAttack(&x, &y, 1, 0, 'w');
			drawMap(&x, &y);
			break;
		}
	}

}
