#include "main.h"
#include "displayControl.h"
#include "asciiArt.h"
#include "game.h"

//ó�� ���� �޴�
void mainMenu(int x, int y) {
	gotoxy(x, y);
	printscr("����");
	gotoxy(x, y + 2);
	printscr("����");
	gotoxy(x, y + 4);
	printscr("����");
}

//Ÿ��Ʋ
void title(int x, int y) {

	gotoxy(66, 1); printscr("                            ������                              ");
	gotoxy(66, 2); printscr("                          ��������                            ");
	gotoxy(66, 3); printscr("                    ��������������                      ");
	gotoxy(66, 4); printscr("                    ��������������                      ");
	gotoxy(66, 5); printscr("                        ��              ��                            ");
	gotoxy(66, 6); printscr("                        ��              ��                            ");
	gotoxy(66, 7); printscr("                        ���          ���                            ");
	gotoxy(66, 8); printscr("        ���    ��      ����������                            ");
	gotoxy(66, 9); printscr("        �����          ��          ��                              ");
	gotoxy(66, 10); printscr("          ����            ������                              ");
	gotoxy(66, 11); printscr("            ����        ��          ��                            ");
	gotoxy(66, 12); printscr("              ����  ���              ����                      ");
	gotoxy(66, 13); printscr("                ����                      ���                    ");
	gotoxy(66, 14); printscr("                ���                          ������������");
	gotoxy(66, 15); printscr("            ����                              �������        ");
	gotoxy(66, 16); printscr("        ������                              ���  ��  �����  ");
	gotoxy(66, 17); printscr("      ��    ��                                      ���  �����  ");
	gotoxy(66, 18); printscr("    ��    ���      ���                ���        �����        ");
	gotoxy(66, 19); printscr("  ��    ��  ��      ��  ��              ��  ��      ��              ");
	gotoxy(66, 20); printscr("  ��  �����    ��    ��              ��    ��    ���            ");
	gotoxy(66, 21); printscr("  ����  ��    ���    ��              ��    ���    ��            ");
	gotoxy(66, 22); printscr("          ��    ��      ��              ���    ��    ��            ");
	gotoxy(66, 23); printscr("          ��    ��      ��              ����  ��    ������    ");
	gotoxy(66, 24); printscr("          ��    ��      ������������  ��    ������    ");
	gotoxy(66, 25); printscr("          ��    ��      ��              ������    ��    ���    ");
	gotoxy(66, 26); printscr("          ����        ��      ��      ��  ���  ����    ����  ");
	gotoxy(66, 27); printscr("          ���          ��    ����    ��  ���    ���  ����    ");
	gotoxy(66, 28); printscr("    ������          ��  ��      ��  ������  �������    ");
	gotoxy(66, 29); printscr("    ������          ��  ��      ��  ��  ���    �������    ");
	gotoxy(66, 30); printscr("    ���                ��  ��        ��  ��                ���    ");
	gotoxy(66, 31); printscr("    ���                ��  ��        ��  ��                ����  ");
	gotoxy(66, 32); printscr("    ���                ��  ��          ��  ��              ���    ");
	gotoxy(66, 33); printscr("                        ��  ��          ��  ��              ��      ");
	gotoxy(66, 34); printscr("                        ��  ��        ����                        ");
	gotoxy(66, 35); printscr("                        ��  ��      ����������              ");
	gotoxy(66, 36); printscr("                        ��  ��    ��  �����    ��  ��            ");
	gotoxy(66, 37); printscr("                        ��  ��    ��  ��          ��  ��            ");
	gotoxy(66, 38); printscr("                      ����      ��  ��          ��  ��            ");
	gotoxy(66, 39); printscr("                      ����        ����������              ");

/*
		gotoxy(66, 1); printscr("�����������������������������������");
		gotoxy(66, 2); printscr("�����������������������������������");
		gotoxy(66, 3); printscr("�����������������������������������");
		gotoxy(66, 4); printscr("�����������������������������������");
		gotoxy(66, 5); printscr("������������������������������������");
		gotoxy(66, 6); printscr("������������������������������������");
		gotoxy(66, 7); printscr("������������������������������������");
		gotoxy(66, 8); printscr("������������������������������������");
		gotoxy(66, 9); printscr("������������������������������������");
		gotoxy(66, 10); printscr("�����������������������������������");
		gotoxy(66, 11); printscr("�����������������������������������");
		gotoxy(66, 12); printscr("�����������������������������������");
		gotoxy(66, 13); printscr("�����������������������������������");
		gotoxy(66, 14); printscr("�����������������������������������");
		gotoxy(66, 15); printscr("�����������������������������������");
		gotoxy(66, 16); printscr("�����������������������������������");
		gotoxy(66, 17); printscr("�����������������������������������");
		gotoxy(66, 18); printscr("�����������������������������������");
		gotoxy(66, 19); printscr("�����������������������������������");
		gotoxy(66, 20); printscr("�����������������������������������");
		gotoxy(66, 21); printscr("�����������������������������������");
		gotoxy(66, 22); printscr("�����������������������������������");
		gotoxy(66, 23); printscr("�����������������������������������");
		gotoxy(66, 24); printscr("�����������������������������������");
		gotoxy(66, 25); printscr("�����������������������������������");
		gotoxy(66, 26); printscr("�����������������������������������");
		gotoxy(66, 27); printscr("�����������������������������������");
		gotoxy(66, 28); printscr("�����������������������������������");
		gotoxy(66, 29); printscr("�����������������������������������");
		gotoxy(66, 30); printscr("�����������������������������������");
		gotoxy(66, 31); printscr("�����������������������������������");
		gotoxy(66, 32); printscr("�����������������������������������");
		gotoxy(66, 33); printscr("�����������������������������������");
		gotoxy(66, 34); printscr("�����������������������������������");
		gotoxy(66, 35); printscr("�����������������������������������");
		gotoxy(66, 36); printscr("�����������������������������������");
		gotoxy(66, 37); printscr("�����������������������������������");
		gotoxy(66, 38); printscr("�����������������������������������");
		gotoxy(66, 39); printscr("�����������������������������������");
*/

	gotoxy(0, 0);
	printscr("                                                              \n");
	printscr("                                                              \n");
	printscr("                                                              \n");
	printscr("                                                              \n");


	printscr("            ������                                        \n");
	printscr("          ���        ��                                      \n");
	printscr("        ���                                                  \n");
	printscr("        ���                    ��      ��      ��  ����    \n");
	printscr("        ���    �������    ��      ��      ���      ��  \n");
	printscr("        ���        ���        ��      ��      ��        ��  \n");
	printscr("          ���      ���        ��      ��      ��        ��  \n");
	printscr("            �������          ����  ��    ��        ��  \n");

	printscr("                                                              \n");
	printscr("                                                              \n");


	printscr("  ����            ��  ��                                    \n");
	printscr("��      ��          ��  ��                                    \n");
	printscr("��            ��    ��  ��    ���      ���  ��      ��    ��  ��\n");
	printscr("��          ��  ��  ��  ��  �����  ��    ����  ��  ��  ���\n");
	printscr("���    ��  ��  ��  ��  ��  ��        ��      ��    ��  ��  ��  \n");
	printscr("  ����      ��    ��  ��    ���      ���  ���    ��    ��  \n");

	mainMenu(x, y);
}
//�޴� Ű ��Ʈ��(khbit ����)
int keyMenuControl()
{
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
		return UP2;
	else if (temp == 's' || temp == 'S')
		return DOWN2;
	else if (temp == ESC)
		exit(1);
	else if (temp == ' ')
		return SUBMIT;
}

//w,s�� ��, �Ʒ� ������ �����̽��ٷ� ����
int menuControl(int keyData, int* x, int* y, int yMin, int yMax) {
	switch (keyData) {
	case UP2:
		if (*y > yMin) {
			gotoxy(*x - 2, *y);
			printscr(" ");
			*y -= 2;
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		else if (*y == yMin) {
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		break;

	case DOWN2:
		if (*y < yMax) {
			gotoxy(*x - 2, *y);
			printscr(" ");
			*y += 2;
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		else if (*y == yMax) {
			gotoxy(*x - 2, *y);
			printscr(">");
		}
		break;

	case ESC:
		exit(1);

	case SUBMIT:
		return *y - yMin;
	}
}
//�޴����� �Լ�
int menuChoice() {

	int x = 30;
	int y = 27;
	int select;

	scr_clear();
	title(x, y);
	gotoxy(28, 27);
	printscr(">");
	scr_switch();

	while (TRUE) {
		int keyData = keyMenuControl();

		scr_clear();
		title(30, 27, 0);

		select = menuControl(keyData, &x, &y, 27, 31);
		if (select == 0 || select == 2 || select == 4)
			return select;
		scr_switch();
	}
}

int printRetry(int x, int y) {
	g(XMIN, YMIN);
	a(XMIN + 11, YMIN);
	m(XMIN + 22, YMIN);
	e(XMIN + 33, YMIN);
	o(XMIN + 50, YMIN);
	v(XMIN + 61, YMIN);
	e(XMIN + 72, YMIN);
	r(XMIN + 83, YMIN);

	gotoxy(x, y); printscr("�ٽ� �õ�");
	gotoxy(x, y + 2); printscr("���� �޴�");

}

int retryMenu() {

	int x = 68;
	int y = 26;
	int select;

	scr_clear();
	printRetry(x, y);
	gotoxy(x - 2, y);
	printscr(">");
	scr_switch();
	
	while (TRUE) {
		int keyData = keyMenuControl();

		scr_clear();
		printRetry(68,26);

		select = menuControl(keyData, &x, &y, 26, 28);
		if (select == 0) {
			isRetry = TRUE;
			return select;
		}
		else if (select == 2) {
			isRetry = FALSE;
			return select;
		}
		scr_switch();
	}
}


void how() {
	scr_clear();
	gotoxy(0, 3);
	printscr("      W             \n");
	printscr("    A   D  WASD�� ���� ĳ���͸� �����Դϴ�.        \n");
	printscr("      S                                                       \n");

	gotoxy(0, 7); printscr("       ��");
	gotoxy(0, 8); printscr("     ���ࢹ      ����⸦ ���� ���� �� �߻��մϴ�");
	gotoxy(0, 9); printscr("       ��");

	gotoxy(65, 2); printscr("�� �� �� �� �븦 ���� ���⸦ �ٲߴϴ�.");
	gotoxy(65, 3); printscr("E ��ư�� ���� ���� ����� �Ѿ�ϴ�.");

	gotoxy(65, 6); printscr("���� HG");
	gotoxy(65, 7); printscr("���� AR");
	gotoxy(65, 8); printscr("���� SG");
	gotoxy(65, 9); printscr("���� RF");
	gotoxy(65, 10); printscr("���� ��� ��ġ �� ������ ���߽�ų �� �ֽ��ϴ�.");


	gotoxy(5, 18); printscr("��(50)   ");
	gotoxy(5, 20); printscr("��(80)   ");
	gotoxy(5, 22); printscr("��(100)");
	gotoxy(5, 24); printscr("��(200)");

	gotoxy(10, 28); printscr("EP 1 The Escape");
	gotoxy(10, 30); printscr("EP 2 No Parking");


	gotoxy(60, 19); printscr("                            ��");
	gotoxy(60, 20); printscr("        ��           ��        ��");
	gotoxy(60, 21); printscr("      ����                           ��");
	gotoxy(60, 22); printscr("��  ������    ��               ��");
	gotoxy(60, 23); printscr("�٢�������         ��               ��      ��");
	gotoxy(60, 24); printscr("    ������                ��");
	gotoxy(60, 25); printscr("      ����            ��        ��");
	gotoxy(60, 26); printscr("        ��          ��                   ��");
	gotoxy(60, 27); printscr("                         ��                   ��");




	scr_switch();
	_getch();
}