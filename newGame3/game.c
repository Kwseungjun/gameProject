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
	//뒷장 페이지 초기화
	scr_clear();
	//테두리 그리기
	border();
	gotoxy(MAPXSTART, 1);
	//플레이어 기준 x값 최소, 최대 | y값 최소 최대 결정
	int hLow, hHigh, wLow, wHigh;

	//위, 아래, 왼쪽, 오른쪽 끝으로 갔을때 작아진 부분만큼 반대쪽 맵 크기 늘리기
	int hUpDif = 0, hDownDif = 0, wLeftDif = 0, wRightDif = 0;
	int i = 1;

	//맵의 최소, 최대값 설정
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

	//맵 그리기
	for (int h = hLow; h < hHigh; h++) {
		for (int w = wLow; w < wHigh; w++) {
			char temp = tempMap[h][w];
			if (temp == '0') {
				printscr("  ");
			}
			else if (temp == '1') {
				printscr("■");
			}
			else if (temp == 'p') {
				*x = w;
				*y = h;
				printscr("☆");
			}
		}
		i++;
		gotoxy(MAPXSTART, i);
	}

	//뒷장, 앞장 전환
	scr_switch();
}

void game() {

	int x;
	int y;
	int changeData = TRUE;

	//게임 시작시 플레이어 위치 가져오기
	userData(&x, &y);

	while (1) {
		//캐릭터 움직임에 변화가 있을시 맵 다시 그리기
		if (changeData == TRUE)
			drawMap(&x, &y);

		switch (keyControl()) {
			//위, 아래, 왼쪽, 오른쪽 이동
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
