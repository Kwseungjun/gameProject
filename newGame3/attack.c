#include "map.h"
#include "game.h"

int weapon = HG;

void attack(int* x, int* y, int _x, int _y, char wh) {

	int xData = *x + _x;
	int yData = *y + _y;
	char mapObject = tempMap[yData][xData];
	//��ֹ��� ���������� �Ѿ��� ���ư�
	if (weapon == HG || weapon == AR) {
		while (TRUE) {
			if (tempMap[yData][xData] != '0')
				break;
			tempMap[yData][xData] = wh;
			yData += _y;
			xData += _x;
			mapObject = tempMap[yData][xData];
		}
	}
	//���� ź���� ����
	else if (weapon == SG) {
		int isEmptyPlace = TRUE;
		for (int i = 0; i < 9; i++) {
			if (isEmptyPlace == FALSE)
				break;
			switch (i) {
			case 0:
				if (tempMap[yData][xData] == '0') {
					tempMap[yData][xData] = 's';
				}
				else
					isEmptyPlace = FALSE;
				if (_x != 0) {
					xData += _x;
					yData--;
				}
				else {
					yData += _y;
					xData--;
				}
				break;
			case 1:
				if (tempMap[yData][xData] == '0')
					tempMap[yData][xData] = 's';
				if (_x != 0)
					yData++;
				else
					xData++;

				break;

			case 2:
				if (tempMap[yData][xData] == '0')
					tempMap[yData][xData] = 's';
				else
					isEmptyPlace = FALSE;
				if (_x != 0)
					yData++;
				else
					xData++;
				break;

			case 3:
				if (tempMap[yData][xData] == '0')
					tempMap[yData][xData] = 's';
				if (_x != 0) {
					yData -= 3;
					xData += _x;
				}
				else {
					xData -= 3;
					yData += _y;
				}
				break;

			case 4: case 5: case 6: case 7: case 8:
				if (tempMap[yData][xData] == '0')
					tempMap[yData][xData] = 's';

				if (_x != 0)
					yData++;
				else
					xData++;
				break;

			}
		}
	}
}

void endAttack(int* x, int* y, int _x, int _y, char wh) {
	int xData = *x + _x;
	int yData = *y + _y;
	char mapObject = tempMap[yData][xData];
	//HG, AR �����
	if (weapon == HG || weapon == AR) {
		while (TRUE) {
			if (tempMap[yData][xData] != wh)
				break;
			tempMap[yData][xData] = '0';
			yData += _y;
			xData += _x;
			mapObject = tempMap[yData][xData];
		}
	}
	//���� �����
	else if (weapon == SG) {
		for (int i = 0; i < 9; i++) {
			switch (i) {
			case 0:
				if (tempMap[yData][xData] == 's') {
					tempMap[yData][xData] = '0';
				}
				if (_x != 0) {
					xData += _x;
					yData--;
				}
				else {
					yData += _y;
					xData--;
				}
				break;
			case 1: case 2:
				if (tempMap[yData][xData] == 's')
					tempMap[yData][xData] = '0';
				if (_x != 0)
					yData++;
				else
					xData++;

				break;

			case 3:
				if (tempMap[yData][xData] == 's')
					tempMap[yData][xData] = '0';

				if (_x != 0) {
					yData -= 3;
					xData += _x;
				}
				else {
					xData -= 3;
					yData += _y;
				}
				break;

			case 4: case 5: case 6: case 7: case 8:
				if (tempMap[yData][xData] == 's')
					tempMap[yData][xData] = '0';

				if (_x != 0)
					yData++;
				else
					xData++;
				break;
			}
		}
	}
}