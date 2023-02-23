#ifndef _MAP_DATA

#define _MAP_DATA

#include "main.h"

#define MAPXMAX 99
#define MAPYMAX 39
#define MAPXHALF 25
#define MAPYHALF 12
#define MAPXSTART 10

char map1[MAPYMAX + 1][MAPXMAX + 1];
char map2[MAPYMAX + 1][MAPXMAX + 1];
char map3[MAPYMAX + 1][MAPXMAX + 1];
char tempMap[MAPYMAX + 1][MAPXMAX + 1];

void border();
void drawMap(int* x, int* y);
void drawInfo();

#endif