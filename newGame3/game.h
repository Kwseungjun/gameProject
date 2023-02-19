#ifndef _GAME_H

#define _GAME_H

int move(int* x, int* y, int _x, int _y);
int keyControl();
void drawMap(int* x, int* y);
void game();
void userData(int* x, int* y);

#define ATTACK 4
#define HG 0
#define AR 1
#define SG 2

#endif