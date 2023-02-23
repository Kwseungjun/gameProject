#include "asciiArt.h"
#include "displayControl.h"
#include "map.h"

void stage(int x, int y) {
	textcolor(GREEN1, BLACK);
	gotoxy(x, y);   printscr(" ######  ########    ###     ######   ######## ");
	gotoxy(x, y+1); printscr("##    ##    ##      ## ##   ##    ##  ##       ");
	gotoxy(x, y+2); printscr("##          ##     ##   ##  ##        ##       ");
	gotoxy(x, y+3); printscr(" ######     ##    ##     ## ##   #### ######   ");
	gotoxy(x, y+4); printscr("      ##    ##    ######### ##    ##  ##       ");
	gotoxy(x, y+5); printscr("##    ##    ##    ##     ## ##    ##  ##       ");
	gotoxy(x, y+6); printscr(" ######     ##    ##     ##  ######   ######## ");
	textcolor(WHITE, BLACK);
	//x+50
}

void first(int x, int y) {
	textcolor(BLUE1, BLACK);
	gotoxy(x, y);     printscr("   ##   ");
	gotoxy(x, y + 1); printscr(" ####   ");
	gotoxy(x, y + 2); printscr("   ##   ");
	gotoxy(x, y + 3); printscr("   ##   ");
	gotoxy(x, y + 4); printscr("   ##   ");
	gotoxy(x, y + 5); printscr("   ##   ");
	gotoxy(x, y + 6); printscr(" ###### ");
	textcolor(WHITE, BLACK);
}

void second(int x, int y) {
	textcolor(YELLOW1, BLACK);
	gotoxy(x, y);     printscr(" #######  ");
	gotoxy(x, y + 1); printscr("##     ## ");
	gotoxy(x, y + 2); printscr("       ## ");
	gotoxy(x, y + 3); printscr(" #######  ");
	gotoxy(x, y + 4); printscr("##        ");
	gotoxy(x, y + 5); printscr("##        ");
	gotoxy(x, y + 6); printscr("######### ");
	textcolor(WHITE, BLACK);
}
void third(int x, int y) {
	textcolor(RED1, BLACK);
	gotoxy(x, y);     printscr(" #######  ");
	gotoxy(x, y + 1); printscr("##     ## ");
	gotoxy(x, y + 2); printscr("       ## ");
	gotoxy(x, y + 3); printscr(" #######  ");
	gotoxy(x, y + 4); printscr("       ## ");
	gotoxy(x, y + 5); printscr("##     ## ");
	gotoxy(x, y + 6); printscr(" ###### ");
	textcolor(WHITE, BLACK);
}

void start(int x, int y) {
	textcolor(CYAN1, BLACK);
	gotoxy(x, y);     printscr(" ######  ########    ###    ########  ######## ");
	gotoxy(x, y + 1); printscr("##    ##    ##      ## ##   ##     ##    ##    ");
	gotoxy(x, y + 2); printscr("##          ##     ##   ##  ##     ##    ##    ");
	gotoxy(x, y + 3); printscr(" ######     ##    ##     ## ########     ##    ");
	gotoxy(x, y + 4); printscr("      ##    ##    ######### ##   ##      ##    ");
	gotoxy(x, y + 5); printscr("##    ##    ##    ##     ## ##    ##     ##    ");
	gotoxy(x, y + 6); printscr(" ######     ##    ##     ## ##     ##    ##    ");
	textcolor(WHITE, BLACK);
}

void clear(int x, int y) {
	textcolor(MAGENTA1, BLACK);
	gotoxy(x, y);     printscr(" ######  ##       ########    ###    ########    #### ");
	gotoxy(x, y + 1); printscr("##    ## ##       ##         ## ##   ##     ##   #### ");
	gotoxy(x, y + 2); printscr("##       ##       ##        ##   ##  ##     ##   #### ");
	gotoxy(x, y + 3); printscr("##       ##       ######   ##     ## ########     ##  ");
	gotoxy(x, y + 4); printscr("##       ##       ##       ######### ##   ##          ");
	gotoxy(x, y + 5); printscr("##    ## ##       ##       ##     ## ##    ##    #### ");
	gotoxy(x, y + 6); printscr(" ######  ######## ######## ##     ## ##     ##   #### ");
	textcolor(WHITE, BLACK);
}

void printStart(int type) {
	for (int i = 0; i < 10; i++) {
		scr_clear();
		border();
		stage(XMIN + i, YMIN);
		scr_switch();
		Sleep(100);
	}
	switch (type) {
	case 1:
		scr_clear();
		border();
		stage(XMIN+10, YMIN);
		first(XMIN+60, YMIN);
		scr_switch();
		break;
	case 2:
		scr_clear();
		border();
		stage(XMIN + 10, YMIN);
		second(XMIN + 60, YMIN);
		scr_switch();
		break;
	case 3:
		scr_clear();
		border();
		stage(XMIN + 10, YMIN);
		third(XMIN + 60, YMIN);
		scr_switch();
		break;
	}
	Sleep(1000);
	scr_clear();
	border();
	start(XMIN + 17, YMIN);
	scr_switch();
	Sleep(1500);
}

void printClear(int type) {
	scr_clear();
	border();
	stage(XMIN + 10, YMIN-3);
	scr_switch();
	Sleep(1000);
	
	switch (type) {
	case 1:
		scr_clear();
		border();
		stage(XMIN + 10, YMIN-3);
		first(XMIN + 60, YMIN-3);
		scr_switch();
		Sleep(1000);
		scr_clear();
		border();
		stage(XMIN + 10, YMIN - 3);
		first(XMIN + 60, YMIN - 3);
		clear(XMIN + 11, YMIN + 6);
		scr_switch();
		Sleep(3000);
		break;
	case 2:
		scr_clear();
		border();
		stage(XMIN + 10, YMIN-3);
		second(XMIN + 60, YMIN-3);
		scr_switch();
		Sleep(1000);
		scr_clear();
		border();
		stage(XMIN + 10, YMIN - 3);
		second(XMIN + 60, YMIN - 3);
		clear(XMIN + 11, YMIN + 6);
		scr_switch();
		Sleep(3000);
		break;
	case 3:
		scr_clear();
		border();
		stage(XMIN + 10, YMIN-3);
		third(XMIN + 60, YMIN-3);
		scr_switch();
		Sleep(1000);
		scr_clear();
		border();
		stage(XMIN + 10, YMIN - 3);
		third(XMIN + 60, YMIN - 3);
		clear(XMIN + 11, YMIN + 6);
		scr_switch();
		Sleep(3000);
		break;
	}
	
}