#define _CRT_SECURE_NO_WARNINGS

#include "displayControl.h"
#include "main.h"
#include "map.h"


//┌─┐│└┘

void init()
{
	//창 사이즈 조절
	system("mode con cols=100 lines=30 | title Game Title");
	scr_init();
}

void mainMenu(int x, int y) {
	gotoxy(x, y);
	printscr("Start");
	gotoxy(x, y + 2);
	printscr("Option");
	gotoxy(x, y + 4);
	printscr("Exit");
}

void mapMenu(int x, int y) {
	gotoxy(x, y);
	printscr("Map1");
	gotoxy(x, y + 2);
	printscr("Map2");
	gotoxy(x, y + 4);
	printscr("Map3");
}

void title(int x, int y, int choice) {
	gotoxy(0,5);
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
	title(x,y,0);
	gotoxy(34, 14);
	printscr(">");
	scr_switch();

	while (TRUE) {
		int keyData = keyControl();

		scr_clear();
		title(36,14,0);

		select = menuControl(keyData, &x, &y);
		if (select == 0 || select == 2 || select == 4)
			return select;
		scr_switch();
	}
}

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
		int keyData = keyControl();

		scr_clear();
		title(36, 14, 1);

		select = menuControl(keyData, &x, &y);
		if (select == 0 || select == 2 || select == 4)
			return select;
		scr_switch();
	}
}

int main(void) {
	init();

	while (TRUE) {
		int userChoice = menuChoice();

		switch (userChoice) {
		case 0:
			//게임시작
			switch (mapChoice()) {
			case 0:
				//MAP1
				memcpy(tempMap, map1, sizeof(tempMap));
				game();
				break;

			case 2:
				//MAP2
				memcpy(tempMap, map2, sizeof(tempMap));
				game();
				break;

			case 4:
				//MAP3
				memcpy(tempMap, map3, sizeof(tempMap));
				game();
				break;

			default:
				break;
			}
			break;

		case 2:
			//옵션

			break;

		case 4:
			exit(1);
			break;
		}
	}
}