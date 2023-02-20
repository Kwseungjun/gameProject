#ifndef _GAME_H

#define _GAME_H

#define ATTACK 4
#define HG 0
#define AR 1
#define SG 2
#define SR 3
#define MAXMONSTER 30

typedef struct {
	int x, y;
	int hp;
	int monsterType;
} MONSTER;

int frameCount;
int delay;
int monsterFrameSync;
int monsterCount;

int move(int* x, int* y, int _x, int _y);
int keyControl();
void drawMap(int* x, int* y);
void game();
void userData(int* x, int* y);

MONSTER mon[MAXMONSTER];

#endif