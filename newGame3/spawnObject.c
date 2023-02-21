#include "spawnObject.h"
#include "map.h"
#include "attack.h"
#include "game.h"

void spawnMonster() {
	while (TRUE) {
		if (monsterCount == MAXMONSTER)
			break;

		mon[monsterCount].x = rand(time(NULL)) % MAPXMAX;
		mon[monsterCount].y = rand(time(NULL)) % MAPYMAX;
		if (tempMap[mon[monsterCount].y][mon[monsterCount].x] == '0') {
			if (monsterCount % 4 == 0) {
				tempMap[mon[monsterCount].y][mon[monsterCount].x] = 'q';
				mon[monsterCount].hp = 100;
			}
			else if (monsterCount % 4 == 1) {
				tempMap[mon[monsterCount].y][mon[monsterCount].x] = 't';
				mon[monsterCount].hp = 200;
			}
			else if (monsterCount % 4 == 2) {
				tempMap[mon[monsterCount].y][mon[monsterCount].x] = 'e';
				mon[monsterCount].hp = 50;
			}
			else if (monsterCount % 4 == 3) {
				tempMap[mon[monsterCount].y][mon[monsterCount].x] = 'r';
				mon[monsterCount].hp = 80;
			}
			monsterCount++;
			break;
		}
	}
}

void spawnMagazine() {
	while (TRUE) {
		int x = rand(time(NULL)) % MAPXMAX;
		int y = rand(time(NULL)) % MAPYMAX;

		if (tempMap[y][x] == '0') {
			if (magazineCount % 4 == 0) {
				tempMap[y][x] = 'z';
			}
			else if (magazineCount % 4 == 1) {
				tempMap[y][x] = 'x';
			}
			else if (magazineCount % 4 == 2) {
				tempMap[y][x] = 'c';
			}
			else if (magazineCount % 4 == 3) {
				tempMap[y][x] = 'v';
			}
			magazineCount++;
			break;
		}
	}
}

void spawnHealth() {
	while (TRUE) {
		int x = rand(time(NULL)) % MAPXMAX;
		int y = rand(time(NULL)) % MAPYMAX;

		if (tempMap[y][x] == '0') {
			tempMap[y][x] = 'n';
			break;
		}
	}
}