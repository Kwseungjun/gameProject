#ifndef _GAME_H

#define _GAME_H

#define ATTACK 4
#define MAXMONSTER 30
#define HGINTERVAL 1
#define SGINTERVAL 2
#define SRINTERVAL 3

typedef struct {
	int x, y;
	int hp;
	int exist;
	int typeFrame;
} MONSTER;

int frameCount;
int delay;
int magazineFrameSync;
int monsterFrameSync;
int healthFrameSync;
int monsterMoveFrameSync;
int reloadFrameSync;
int monsterCount;
int magazineCount;
int healthCount;
int startTime;
int maxHP;
int userHP;
int gameLoop;
int isReload;

int move(int* x, int* y, int _x, int _y);
int keyControl();
void userData(int* x, int* y);
void monsterMove(int* x, int* y);
void gameInit();
void game();

MONSTER mon[MAXMONSTER];

#endif