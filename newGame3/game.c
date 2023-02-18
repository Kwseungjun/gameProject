#include "main.h"
#include "game.h"
#include "displayControl.h"
#include "map.h"

int keyControl()
{
	char temp = _getch();
	if (temp == 'w' || temp == 'W')
		return UP2;
	else if (temp == 's' || temp == 'S')
		return DOWN2;
	else if (temp == 'a' || temp == 'A')
		return LEFT2;
	else if (temp == 'd' || temp == 'D')
		return RIGHT2;
	else if (temp == ' ')
		return SUBMIT;
}

int move(int* x, int* y, int _x, int _y)
{
	char mapObject = tempMap[*y + _y][*x + _x];

	if (mapObject == '0') {
		tempMap[*y][*x] = '0';
		tempMap[*y + _y][*x + _x] = 'p';
		return TRUE;
	}
	return FALSE;
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
	for (int h = hLow; h < hHigh; h++) {
		for (int w = wLow; w < wHigh; w++) {
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

		switch (keyControl()) {
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
		}
	}

}
