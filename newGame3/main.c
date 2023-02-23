#define _CRT_SECURE_NO_WARNINGS

#include "displayControl.h"
#include "main.h"
#include "map.h"
#include "menu.h"
#include "game.h"

int userStage = 1;

void init()
{
	//창 사이즈 조절
	system("mode con cols=125 lines=37 | title Game Title");
	scr_init();
}



int main(void) {
	init();

	while (TRUE) {
 		int userChoice = menuChoice();
		gameLoop = TRUE;
		userHP = maxHP;
		switch (userChoice) {
		case 0:
			//게임시작
			while (userStage < 4) {
				gameLoop = TRUE;
				game();
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