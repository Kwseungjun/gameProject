#include "main.h"
#include "game.h"
#include "displayControl.h"
#include "map.h"
#include "attack.h"
#include "spawnObject.h"

typedef struct {
	int x, y;
	int exist;
} BULLET;

int frameCount = 0;
int delay = 10;
int magazineFrameSync = 500;
int monsterFrameSync = 100;
int healthFrameSync = 1000;
int reloadFrameSync = 100;
int magazineCount = 0;
int monsterCount = 0;
int healthCount = 0;
int startTime;
int maxHP = 5;
int userHP = 5;
int gameLoop = 1;

MONSTER mon[MAXMONSTER];

//게임 내에서 사용할 키 컨트롤
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
		else if (temp == '1') {
			selectWeapon = HG;
		}
		else if (temp == '2') {
			selectWeapon = AR;
		}
		else if (temp == '3') {
			selectWeapon = SG;
		}
		else if (temp == '4') {
			selectWeapon = SR;
		}
		else if (temp == 'e' || temp == 'E') {
			if (selectWeapon == SR) {
				selectWeapon = HG;
			}
			else {
				selectWeapon++;
			}
		}
		else if (temp == ESC)
			exit(1);
		else if (temp == ' ')
			return ATTACK;
	}
}

int move(int* x, int* y, int _x, int _y)
{
	char mapObject = tempMap[*y + _y][*x + _x];
	char mapObject2 = tempMap[*y + _y - 1][*x + _x];

	//이동할 장소에 장애물이 있는지 확인
	if ((mapObject == '0' && mapObject2 == '0') || (mapObject == 'P' && mapObject2 == '0') || (mapObject == '0' && mapObject2 == 'p')) {
		tempMap[*y][*x] = '0';
		tempMap[*y-1][*x] = '0';
		tempMap[*y + _y][*x + _x] = 'p';
		tempMap[*y + _y - 1][*x + _x] = 'P';
		*x += _x;
		*y += _y;
		return TRUE;
	}
	else if (mapObject == 'z' || mapObject == 'x' || mapObject == 'c' || mapObject == 'v' || mapObject == 'n' || mapObject2 == 'z' || mapObject2 == 'x' || mapObject2 == 'c' || mapObject2 == 'v' || mapObject2 == 'n') {
		switch (mapObject) {
		case 'z':
			weapon[HG].resetMagazine++;
			break;
		case 'x':
			weapon[AR].resetMagazine++;
			break;
		case 'c':
			weapon[SG].resetMagazine++;
			break;
		case 'v':
			weapon[SR].resetMagazine++;
			break;
		case 'n':
			userHP++;
			break;
		}
		switch (mapObject2) {
		case 'z':
			weapon[HG].resetMagazine++;
			break;
		case 'x':
			weapon[AR].resetMagazine++;
			break;
		case 'c':
			weapon[SG].resetMagazine++;
			break;
		case 'v':
			weapon[SR].resetMagazine++;
			break;
		case 'n':
			userHP++;
			break;
		}

		tempMap[*y][*x] = '0';
		tempMap[*y-1][*x] = '0';
		tempMap[*y + _y][*x + _x] = 'p';
		tempMap[*y + _y - 1][*x + _x] = 'P';
		*x += _x;
		*y += _y;
		return TRUE;
	}
	//피격시 체력감소
	else if (mapObject == 'q' || mapObject == 'e' || mapObject == 'r' || mapObject == 't') {
		userHP--;
		if (userHP <= 0)
			gameLoop = 0;
		return TRUE;
	}
	else if (mapObject2 == 'q' || mapObject2 == 'e' || mapObject2 == 'r' || mapObject2 == 't') {
		userHP -= 2;
		if (userHP <= 0)
			gameLoop = 0;
		return TRUE;
	}
	return FALSE;
}

//게임 시작시 플레이어 위치 가져오는 함수
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

void gameInit() {

	weapon[HG].bullet = 15;
	weapon[HG].damage = HGDAMAGE;
	weapon[HG].lastShootTime = 0;
	weapon[HG].weaponSetTime = 1;
	weapon[HG].resetMagazine = 1;

	weapon[AR].bullet = 30;
	weapon[AR].damage = ARDAMAGE;
	weapon[AR].lastShootTime = 0;
	weapon[AR].weaponSetTime = 0;
	weapon[AR].resetMagazine = 1;

	weapon[SG].bullet = 7;
	weapon[SG].damage = SGDAMAGE;
	weapon[SG].lastShootTime = 0;
	weapon[SG].weaponSetTime = 1;
	weapon[SG].resetMagazine = 1;

	weapon[SR].bullet = 5;
	weapon[SR].damage = SRDAMAGE;
	weapon[SR].lastShootTime = 0;
	weapon[SR].weaponSetTime = 2;
	weapon[SR].resetMagazine = 1;

	magazine[HG].oneMagazine = 15;
	magazine[AR].oneMagazine = 30;
	magazine[SG].oneMagazine = 7;
	magazine[SR].oneMagazine = 5;
}

void game() {

	int x;
	int y;
	int changeData = TRUE;
	int runTime, startTime;

	startTime = time(NULL);

	//게임 시작시 플레이어 위치 가져오기
	userData(&x, &y);

	gameInit();

	while (gameLoop) {

		runTime = time(NULL) - startTime;


		//캐릭터 움직임에 변화가 있을시 맵 다시 그리기
		if (changeData == TRUE)
			drawMap(&x, &y);

		if (frameCount % monsterFrameSync == 0)
			spawnMonster();
		if (frameCount % magazineFrameSync == 0)
			spawnMagazine();
		if (frameCount % healthFrameSync == 0)
			spawnHealth();
		Sleep(delay);


		frameCount++;

		int keyData = keyControl();

		switch (keyData) {
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
			//방향키로 공격
		case UP:
			if (weapon[selectWeapon].bullet <= 0) {
				if (weapon[selectWeapon].resetMagazine > 0) {
					weapon[selectWeapon].resetMagazine--;
					weapon[selectWeapon].bullet = magazine[selectWeapon].oneMagazine;
				}
				else
					break;
			}
			if (runTime - weapon[selectWeapon].lastShootTime >= weapon[selectWeapon].weaponSetTime) {
				attack(&x, &y, 0, -1, 'h');
				drawMap(&x, &y);
				Sleep(50);
				endAttack(&x, &y, 0, -1, 'h');
				drawMap(&x, &y);
				weapon[selectWeapon].lastShootTime = runTime;
			}
			break;
		case DOWN:
			if (weapon[selectWeapon].bullet <= 0) {
				if (weapon[selectWeapon].resetMagazine > 0) {
					weapon[selectWeapon].resetMagazine--;
					weapon[selectWeapon].bullet = magazine[selectWeapon].oneMagazine;
				}
				else
					break;
			}
			if (runTime - weapon[selectWeapon].lastShootTime >= weapon[selectWeapon].weaponSetTime) {
				attack(&x, &y, 0, 1, 'h');
				drawMap(&x, &y);
				Sleep(50);
				endAttack(&x, &y, 0, 1, 'h');
				drawMap(&x, &y);
				weapon[selectWeapon].lastShootTime = runTime;
			}
			break;
		case LEFT:
			if (weapon[selectWeapon].bullet <= 0) {
				if (weapon[selectWeapon].resetMagazine > 0) {
					weapon[selectWeapon].resetMagazine--;
					weapon[selectWeapon].bullet = magazine[selectWeapon].oneMagazine;
				}
				else
					break;
			}
			if (runTime - weapon[selectWeapon].lastShootTime >= weapon[selectWeapon].weaponSetTime) {
				attack(&x, &y, -1, 0, 'w');
				drawMap(&x, &y);
				Sleep(50);
				endAttack(&x, &y, -1, 0, 'w');
				drawMap(&x, &y);
				weapon[selectWeapon].lastShootTime = runTime;
			}
			break;
		case RIGHT:
			if (weapon[selectWeapon].bullet <= 0) {
				if (weapon[selectWeapon].resetMagazine > 0) {
					weapon[selectWeapon].resetMagazine--;
					weapon[selectWeapon].bullet = magazine[selectWeapon].oneMagazine;
				}
				else
					break;
			}
			if (runTime - weapon[selectWeapon].lastShootTime >= weapon[selectWeapon].weaponSetTime) {
				attack(&x, &y, 1, 0, 'w');
				drawMap(&x, &y);
				Sleep(50);
				endAttack(&x, &y, 1, 0, 'w');
				drawMap(&x, &y);
				weapon[selectWeapon].lastShootTime = runTime;
			}
			break;
		}


	}
}
