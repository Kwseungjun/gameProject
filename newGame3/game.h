#ifndef _GAME_H

#define _GAME_H

#define ATTACK 4
#define MAXMONSTER 5
#define MAXWALL 30
#define MAXBARREL 800
#define HGINTERVAL 1
#define SGINTERVAL 2
#define SRINTERVAL 3

typedef struct {
	int x, y;
	int hp;
	int exist;
	int typeFrame;
} MONSTER;

typedef struct {
	int x, y;
	int hp;
} WALL;

typedef struct {
	int x, y;
	int hp;
	int exist;
} BARREL;

//���ӽ���
int gameLoop;
//�ӵ� ���� ����
int frameCount;
int delay;
int startTime;
int runTime, startTime;
//�÷��̾� ü�� ����
int maxHP;
int userHP;
//�ǰݽ� �����ð� ����
int isBarrier;
int barrierStartTime;

int keyControl();
int move(int* x, int* y, int _x, int _y);
void userData(int* x, int* y);
void wallSearch();
void gameInit();
void game();

MONSTER mon[MAXMONSTER];
WALL wall[MAXWALL];
BARREL bar[MAXBARREL];

#endif