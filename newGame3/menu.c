#include "main.h"
#include "displayControl.h"

//처음 시작 메뉴
void mainMenu(int x, int y) {
	gotoxy(x, y);
	printscr("Start");
	gotoxy(x, y + 2);
	printscr("Option");
	gotoxy(x, y + 4);
	printscr("Exit");
}

//맵 선택 메뉴
void mapMenu(int x, int y) {
	gotoxy(x, y);
	printscr("Map1");
	gotoxy(x, y + 2);
	printscr("Map2");
	gotoxy(x, y + 4);
	printscr("Map3");
}

//타이틀
void title(int x, int y, int choice) {
	gotoxy(0, 5);
	printscr("                      ########      ########       #######   \n");
	printscr("                      ##     ##     ##     ##     ##         \n");
	printscr("                      ##     ##     ##     ##    ##          \n");
	printscr("                      ########      ########     ##          \n");
	printscr("                      ## ###        ##           ##   ###### \n");
	printscr("                      ##   ###      ##           ##     ##   \n");
	printscr("                      ##     ##     ##            ##    ##   \n");
	printscr("                      ##     ##     ##             #######   \n");

	if (choice == 0)
		mainMenu(x, y);
	else if (choice == 1)
		mapMenu(x, y);
}
//메뉴 키 컨트롤(khbit 없음)
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

//w,s로 위, 아래 조종후 스페이스바로 선택
int menuControl(int keyData, int* x, int* y) {
	switch (keyData) {
	case UP2:
		if (*y > 14) {
			gotoxy(*x - 2, *y);
			printscr(" ");
			*y -= 2;
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		else if (*y == 14) {
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		break;

	case DOWN2:
		if (*y < 18) {
			gotoxy(*x - 2, *y);
			printscr(" ");
			*y += 2;
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		else if (*y == 18) {
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		break;

	case ESC:
		exit(1);

	case SUBMIT:
		return *y - 14;
	}
}
//메뉴선택 함수
int menuChoice() {

	int x = 36;
	int y = 14;
	int select;

	scr_clear();
	title(x, y, 0);
	gotoxy(34, 14);
	printscr(">");
	scr_switch();

	while (TRUE) {
		int keyData = keyMenuControl();

		scr_clear();
		title(36, 14, 0);

		select = menuControl(keyData, &x, &y);
		if (select == 0 || select == 2 || select == 4)
			return select;
		scr_switch();
	}
}

//맵 선택 함수
int mapChoice() {
	int x = 36;
	int y = 14;
	int select;

	scr_clear();
	title(x, y, 1);
	gotoxy(34, 14);
	printscr(">");
	scr_switch();

	while (TRUE) {
		int keyData = keyMenuControl();

		scr_clear();
		title(36, 14, 1);

		select = menuControl(keyData, &x, &y);
		if (select == 0 || select == 2 || select == 4)
			return select;
		scr_switch();
	}
}