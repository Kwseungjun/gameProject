﻿#define _CRT_SECURE_NO_WARNINGS

#include "displayControl.h"
#include "main.h"

#define TRUE 1
#define FALSE 0
#define SUBMIT 4

#define MAPXMAX 100
#define MAPYMAX 30
#define MAPXHALF 20
#define MAPYHALF 10
//┌─┐│└┘
void border() {
	gotoxy(8, 0); printscr("┌────────────────────────────────────────┐");
	for (int h = 1; h < MAPYMAX/2+6; h++)
		gotoxy(8, h); printscr("│                                                                                │\n");
	printscr("        └────────────────────────────────────────┘");
}
char map1[MAPYMAX][MAPXMAX] = {
		{"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"10000000000000000000000000000000000000000000000000p0000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1001100000000000000000000011000000000000000000000011000000000000000000000110000000000000001100000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"},
		{"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"}
};

void init()
{
	//창 사이즈 조절
	system("mode con cols=100 lines=30 | title Game Title");
	scr_init();
}
/*
void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
*/
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
	char mapObject = map1[*y + _y][*x + _x];

	if (mapObject == '0') {
		map1[*y][*x] = '0';
		map1[*y + _y][*x + _x] = 'p';
		return TRUE;
	}
	return FALSE;
}

void title() {
	gotoxy(0,5);
	printscr("                      #########     #########      #######   \n");
	printscr("                      ##     ##     ##     ##     ##         \n");
	printscr("                      ##     ##     ##     ##    ##          \n");
	printscr("                      #########     #########    ##          \n");
	printscr("                      ## ###        ##           ##   ###### \n");
	printscr("                      ##   ###      ##           ##     ##   \n");
	printscr("                      ##     ##     ##            ##    ##   \n");
	printscr("                      ##     ##     ##             #######   \n");
}

int menuChoice() {

	int x = 36;
	int y = 14;

	scr_clear();
	title();

	gotoxy(x-2, y);
	printscr("> Start");
	gotoxy(x, y+2);
	printscr("Option");
	gotoxy(x, y+4);
	printscr("Exit");

	scr_switch();

	while (TRUE) {
		int keyData = keyControl();

		switch (keyData) {
		case UP2:
			if (y > 14) {
				gotoxy(x - 2, y);
				printscr(" ");
				y -= 2;
				gotoxy(x - 2, y);
				printscr(">");
			}
			break;

		case DOWN2:
			if (y < 18) {
				gotoxy(x - 2, y);
				printscr(" ");
				y += 2;
				gotoxy(x - 2, y);
				printscr(">");
			}
			break;

		case SUBMIT:
			return y - 14;
		}
	}
}

void userData(int *x, int *y) {
	for (int h = 0; h < 20; h++) {
		for (int w = 0; w < 99; w++) {
			if (map1[h][w] == 'p') {
				*x = w;
				*y = h;
				return;
			}
		}
	}
}

void drawMap(int* x, int* y)
{
	scr_clear();
	border();
	gotoxy(10, 1);
	int hLow, hHigh, wLow, wHigh;
	int hUpDif = 0, hDownDif = 0, wLeftDif = 0, wRightDif = 0;
	int i = 1;

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

	for (int h = hLow; h < hHigh; h++) {
		for (int w = wLow; w < wHigh; w++) {
			char temp = map1[h][w];
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
		gotoxy(10, i);
	}

	scr_switch();
}

void game() {

	int x;
	int y;
	int changeData = TRUE;

	userData(&x, &y);

	while (1) {
		if (changeData == TRUE)
			drawMap(&x, &y);

		switch (keyControl()) {
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

int main(void) {
	init();

	while (TRUE) {
		scr_clear();
		title();
		scr_switch();
		int userChoice = menuChoice();

		switch (userChoice) {
		case 0:
			//게임시작
			game();
			break;

		case 1:
			//옵션

			break;

		case 2:
			exit(1);
			break;
		}
	}
}