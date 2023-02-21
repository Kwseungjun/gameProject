#include "main.h"
#include "game.h"
#include "displayControl.h"
#include "map.h"
#include "attack.h"
#include "spawnObject.h"

int frameCount = 0;
int delay = 10;
int magazineFrameSync = 500;
int monsterFrameSync = 100;
int healthFrameSync = 1000;
int monsterMoveFrameSync = 10;
int reloadFrameSync = 100;
int magazineCount = 0;
int monsterCount = 0;
int healthCount = 0;
int startTime;
int maxHP = 5;
int userHP = 5;
int gameLoop = 1;
int isReload = FALSE;

MONSTER mon[MAXMONSTER];

//���� ������ ����� Ű ��Ʈ��
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

	//�̵��� ��ҿ� ��ֹ��� �ִ��� Ȯ��
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
			weapon[HG].magazine++;
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
			weapon[HG].magazine++;
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

		tempMap[*y][*x] = '0';
		tempMap[*y - 1][*x] = '0';
		tempMap[*y + _y][*x + _x] = 'p';
		tempMap[*y + _y - 1][*x + _x] = 'P';
		*x += _x;
		*y += _y;
		return TRUE;
	}
	//�ǰݽ� ü�°���
	/*
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
	*/
	return FALSE;
}

//���� ���۽� �÷��̾� ��ġ �������� �Լ�
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

void monsterMove(int* x, int* y) {
	int count = 0;
	int xDifferenceValue, yDifferenceValue;
	while (count < monsterCount) {
		if (frameCount % mon[count].typeFrame == 0) {
			if (mon[count].exist == TRUE) {

				xDifferenceValue = *x - mon[count].x;
				yDifferenceValue = *y - mon[count].y;

				if (abs(xDifferenceValue) > abs(yDifferenceValue)) {

					if (tempMap[mon[count].y][mon[count].x + 1] == 'P' || tempMap[mon[count].y][mon[count].x - 1] == 'P') {
						userHP -= 2;
						if (userHP <= 0)
							gameLoop = FALSE;
					}
					else if (tempMap[mon[count].y][mon[count].x + 1] == 'p' || tempMap[mon[count].y][mon[count].x - 1] == 'p') {
						userHP--;
						if (userHP <= 0)
							gameLoop = FALSE;
					}
					else if (xDifferenceValue > 0 && tempMap[mon[count].y][mon[count].x + 1] == '0') {
						tempMap[mon[count].y][mon[count].x + 1] = tempMap[mon[count].y][mon[count].x];
						tempMap[mon[count].y][mon[count].x] = '0';
						mon[count].x++;
					}
					else if (xDifferenceValue <= 0 && tempMap[mon[count].y][mon[count].x - 1] == '0') {
						tempMap[mon[count].y][mon[count].x - 1] = tempMap[mon[count].y][mon[count].x];
						tempMap[mon[count].y][mon[count].x] = '0';
						mon[count].x--;
					}
					else if (yDifferenceValue > 0 && tempMap[mon[count].y + 1][mon[count].x] == '0') {
						tempMap[mon[count].y + 1][mon[count].x] = tempMap[mon[count].y][mon[count].x];
						tempMap[mon[count].y][mon[count].x] = '0';
						mon[count].y++;
					}
					else if (yDifferenceValue <= 0 && tempMap[mon[count].y - 1][mon[count].x] == '0') {
						tempMap[mon[count].y - 1][mon[count].x] = tempMap[mon[count].y][mon[count].x];
						tempMap[mon[count].y][mon[count].x] = '0';
						mon[count].y--;
					}
				}

				else {
					if (tempMap[mon[count].y + 1][mon[count].x] == 'P' || tempMap[mon[count].y - 1][mon[count].x] == 'P') {
						userHP -= 2;
						if (userHP <= 0)
							gameLoop = FALSE;
					}
					else if (tempMap[mon[count].y + 1][mon[count].x] == 'p' || tempMap[mon[count].y - 1][mon[count].x] == 'p') {
						userHP--;
						if (userHP <= 0)
							gameLoop = FALSE;
					}
					else if (yDifferenceValue > 0 && tempMap[mon[count].y + 1][mon[count].x] == '0') {
						tempMap[mon[count].y + 1][mon[count].x] = tempMap[mon[count].y][mon[count].x];
						tempMap[mon[count].y][mon[count].x] = '0';
						mon[count].y++;
					}
					else if (yDifferenceValue <= 0 && tempMap[mon[count].y - 1][mon[count].x] == '0') {
						tempMap[mon[count].y - 1][mon[count].x] = tempMap[mon[count].y][mon[count].x];
						tempMap[mon[count].y][mon[count].x] = '0';
						mon[count].y--;
					}
					else if (xDifferenceValue > 0 && tempMap[mon[count].y][mon[count].x + 1] == '0') {
						tempMap[mon[count].y][mon[count].x + 1] = tempMap[mon[count].y][mon[count].x];
						tempMap[mon[count].y][mon[count].x] = '0';
						mon[count].x++;
					}
					else if (xDifferenceValue <= 0 && tempMap[mon[count].y][mon[count].x - 1] == '0') {
						tempMap[mon[count].y][mon[count].x - 1] = tempMap[mon[count].y][mon[count].x];
						tempMap[mon[count].y][mon[count].x] = '0';
						mon[count].x--;
					}
				}
			}
		}
		count++;
	}
}

void gameInit() {

	weapon[HG].bullet = 15;
	weapon[HG].damage = HGDAMAGE;
	weapon[HG].lastShootTime = 0;
	weapon[HG].weaponSetTime = 1;
	weapon[HG].magazine = 1;

	weapon[AR].bullet = 30;
	weapon[AR].damage = ARDAMAGE;
	weapon[AR].lastShootTime = 0;
	weapon[AR].weaponSetTime = 0;
	weapon[AR].magazine = 1;

	weapon[SG].bullet = 7;
	weapon[SG].damage = SGDAMAGE;
	weapon[SG].lastShootTime = 0;
	weapon[SG].weaponSetTime = 1;
	weapon[SG].magazine = 1;

	weapon[SR].bullet = 5;
	weapon[SR].damage = SRDAMAGE;
	weapon[SR].lastShootTime = 0;
	weapon[SR].weaponSetTime = 2;
	weapon[SR].magazine = 1;

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

	//���� ���۽� �÷��̾� ��ġ ��������
	userData(&x, &y);

	gameInit();

	while (gameLoop) {

		runTime = time(NULL) - startTime;


		//ĳ���� �����ӿ� ��ȭ�� ������ �� �ٽ� �׸���
		//if (changeData == TRUE)
			

		if (frameCount % monsterFrameSync == 0)
			spawnMonster();
		if (frameCount % magazineFrameSync == 0)
			spawnMagazine();
		if (frameCount % healthFrameSync == 0)
			spawnHealth();
		if (frameCount % monsterMoveFrameSync == 0)
			monsterMove(&x, &y);

		if (runTime - weapon[selectWeapon].reload > weapon[selectWeapon].weaponSetTime + 1)
			isReload = FALSE;

		Sleep(delay);

		drawMap(&x, &y);

		frameCount++;

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
			//����Ű�� ����
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
