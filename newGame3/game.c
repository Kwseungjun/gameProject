#include "main.h"
#include "game.h"
#include "displayControl.h"
#include "map.h"
#include "attack.h"
#include "spawnObject.h"
#include "asciiArt.h"
#include "monster.h"

//게임시작
int gameLoop = 1;
//속도 관련 변수
int frameCount = 0;
int delay = 10;
int startTime;
int runTime, startTime;
//플레이어 체력 변수
int maxHP = 5;
int userHP = 5;
//피격시 무적시간 변수
int isBarrier = FALSE;
int barrierStartTime = 0;

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
		else if (temp == '5') {
			selectWeapon = BR;
		}
		else if (temp == 'e' || temp == 'E') {
			if (selectWeapon == BR) {
				selectWeapon = HG;
			}
			else {
				selectWeapon++;
			}
		}
		else if (temp == 'q' || temp == 'Q') {
			if (selectWeapon == HG) {
				selectWeapon = BR;
			}
			else {
				selectWeapon--;
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
		tempMap[*y - 1][*x] = '0';
		tempMap[*y + _y][*x + _x] = 'p';
		tempMap[*y + _y - 1][*x + _x] = 'P';
		*x += _x;
		*y += _y;
		return TRUE;
	}
	else if (((mapObject == 'z' || mapObject == 'x' || mapObject == 'c' || mapObject == 'v' || mapObject == 'n') && (mapObject2 == '0' || mapObject2 == 'p')) || ((mapObject == 'n' || mapObject2 == 'z' || mapObject2 == 'x' || mapObject2 == 'c' || mapObject2 == 'v' || mapObject2 == 'n') && (mapObject == '0' || mapObject == 'P'))) {
		switch (mapObject) {
		case 'z':
			weapon[BR].bullet += 5;
			break;
		case 'x':
			weapon[AR].magazine++;
			break;
		case 'c':
			weapon[SG].magazine++;
			break;
		case 'v':
			weapon[SR].magazine++;
			break;
		case 'n':
			userHP++;
			break;
		}
		switch (mapObject2) {
		case 'z':
			weapon[BR].bullet += 5;
			break;
		case 'x':
			weapon[AR].magazine++;
			break;
		case 'c':
			weapon[SG].magazine++;
			break;
		case 'v':
			weapon[SR].magazine++;
			break;
		case 'n':
			if (userHP < maxHP)
				userHP++;
			break;
		}

		tempMap[*y][*x] = '0';
		tempMap[*y - 1][*x] = '0';
		tempMap[*y + _y][*x + _x] = 'p';
		tempMap[*y + _y - 1][*x + _x] = 'P';
		*x += _x;
		*y += _y;
		return TRUE;
	}
	return FALSE;
}

//게임 시작시 플레이어 위치 가져오는 함수
void userData(int* x, int* y) {
	for (int h = 0; h < MAPYMAX + 1; h++) {
		for (int w = 0; w < MAPXMAX + 1; w++) {
			if (tempMap[h][w] == 'p') {
				*x = w;
				*y = h;
				return;
			}
		}
	}
}


void wallSearch() {
	int wallnum = 0;
	for (int h = 0; h < MAPYMAX + 1; h++) {
		for (int w = 0; w < MAPXMAX + 1; w++) {
			if (tempMap[h][w] == '!') {
				wall[wallnum].x = w;
				wall[wallnum].y = h;
				wall[wallnum].hp = 100;
				wallnum++;
			}
		}
	}
}

void gameInit() {
	switch (userStage) {
	case 1:
		memcpy(tempMap, map1, sizeof(tempMap));
		break;
	case 2:
		memcpy(tempMap, map2, sizeof(tempMap));
		maxHP++;
		userHP = maxHP;
		break;
	case 3:
		memcpy(tempMap, map3, sizeof(tempMap));
		maxHP += 2;
		userHP = maxHP;
		break;
	}

	magazineCount = 0;
	monsterCount = 0;
	healthCount = 0;
	barrelCount = 0;
	selectWeapon = 0;

	memset(mon, 0, sizeof(mon));
	memset(wall, 0, sizeof(wall));
	memset(bar, 0, sizeof(bar));

	wallSearch();

	weapon[HG].bullet = 15;
	weapon[HG].damage = HGDAMAGE;
	weapon[HG].lastShootTime = 0;
	weapon[HG].weaponSetTime = 1;
	weapon[HG].magazine = 100;

	weapon[AR].bullet = 30;
	weapon[AR].damage = ARDAMAGE;
	weapon[AR].lastShootTime = 0;
	weapon[AR].weaponSetTime = 0;
	weapon[AR].magazine = 1;

	weapon[SG].bullet = 7;
	weapon[SG].damage = SGDAMAGE;
	weapon[SG].lastShootTime = 0;
	weapon[SG].weaponSetTime = 2;
	weapon[SG].magazine = 1;

	weapon[SR].bullet = 5;
	weapon[SR].damage = SRDAMAGE;
	weapon[SR].lastShootTime = 0;
	weapon[SR].weaponSetTime = 3;
	weapon[SR].magazine = 1;

	weapon[BR].bullet = 20;
	weapon[BR].damage = BRDAMAGE;
	weapon[BR].lastShootTime = 0;
	weapon[BR].weaponSetTime = 0;
	weapon[BR].magazine = 0;

	magazine[HG].oneMagazine = 15;
	magazine[AR].oneMagazine = 30;
	magazine[SG].oneMagazine = 7;
	magazine[SR].oneMagazine = 5;
	magazine[BR].oneMagazine = 100;
}

void game() {

	int x;
	int y;
	int changeData = TRUE;
	
	printStart(userStage);

	startTime = time(NULL);

	//게임 시작시 플레이어 위치 가져오기
	userData(&x, &y);

	gameInit();

	while (gameLoop) {

		runTime = time(NULL) - startTime;

		checkMonsterBug();

		if (frameCount % monsterFrameSync == 0)
			spawnMonster();
		if (frameCount % magazineFrameSync == 0)
			spawnMagazine();
		if (frameCount % healthFrameSync == 0)
			spawnHealth();
		if (frameCount % monsterMoveFrameSync == 0)
			monsterMove(&x, &y);
		if (isMonsterRemain() == FALSE&&monsterCount==MAXMONSTER) {
			gameLoop = FALSE;
			printClear(userStage);
			userStage++;
			break;
		}
		if (runTime - weapon[selectWeapon].reload > weapon[selectWeapon].weaponSetTime + 1)
			isReload = FALSE;

		Sleep(delay);

		drawMap(&x, &y);

		frameCount+=2;

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
				if (weapon[selectWeapon].magazine > 0 && (runTime - weapon[selectWeapon].reload > weapon[selectWeapon].weaponSetTime + 1)) {
					weapon[selectWeapon].magazine--;
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
				if (weapon[selectWeapon].bullet == 0) {
					weapon[selectWeapon].reload = runTime;
					isReload = TRUE;
				}
			}
			break;
		case DOWN:
			if (weapon[selectWeapon].bullet <= 0) {
				if (weapon[selectWeapon].magazine > 0 && (runTime - weapon[selectWeapon].reload > weapon[selectWeapon].weaponSetTime + 1)) {
					weapon[selectWeapon].magazine--;
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
				if (weapon[selectWeapon].bullet == 0) {
					weapon[selectWeapon].reload = runTime;
					isReload = TRUE;
				}
			}
			break;
		case LEFT:
			if (weapon[selectWeapon].bullet <= 0) {
				if (weapon[selectWeapon].magazine > 0 && (runTime - weapon[selectWeapon].reload > weapon[selectWeapon].weaponSetTime + 1)) {
					weapon[selectWeapon].magazine--;
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
				if (weapon[selectWeapon].bullet == 0) {
					weapon[selectWeapon].reload = runTime;
					isReload = TRUE;
				}
			}
			break;
		case RIGHT:
			if (weapon[selectWeapon].bullet <= 0) {
				if (weapon[selectWeapon].magazine > 0 && (runTime - weapon[selectWeapon].reload > weapon[selectWeapon].weaponSetTime + 1)) {
					weapon[selectWeapon].magazine--;
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
				if (weapon[selectWeapon].bullet == 0) {
					weapon[selectWeapon].reload = runTime;
					isReload = TRUE;
				}
			}
			break;
		}


	}
}
