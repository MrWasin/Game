#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<conio.h>

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
		return buf[0];

}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
	gotoxy(x+7, y);
	printf("_");
	gotoxy(x+6, y + 1);
	printf("/_\\");
	gotoxy(x+6, y + 2);
	printf("[ ]");
	gotoxy(x+4, y + 3);
	printf("_/\\O/\\_");
	gotoxy(x+1, y + 4);
	printf("<{| ||_|| |}>");
	gotoxy(x+4, y + 5);
	printf("V\\| |/V");
	gotoxy(x+6, y + 6);
	printf("\\_/");
}
void erase_ship(int x, int y)
{
	gotoxy(x + 7, y);
	printf(" ");
	gotoxy(x + 6, y + 1);
	printf("   ");
	gotoxy(x + 6, y + 2);
	printf("   ");
	gotoxy(x + 4, y + 3);
	printf("       ");
	gotoxy(x + 1, y + 4);
	printf("             ");
	gotoxy(x + 4, y + 5);
	printf("       ");
	gotoxy(x + 6, y + 6);
	printf("   ");
}

void draw_bullet(int x, int y)
{
	gotoxy(x+5, y);
	printf("^");
}

void erase_bullet(int x, int y)
{
	gotoxy(x+5, y);
	printf(" ");
}

void START_spawn()
{
	int sn, sy, i;
	for (i = 0; i < 60; i++) {
		sn = (rand() % 61) + 10;
		sy = (rand() % 10) + 2;
		while (cursor(sn, sy) == '*') {
			sn = (rand() % 61) + 10;
			sy = (rand() % 4) + 2;
		}
		gotoxy(sn, sy);
		printf("*");
	}
}

int main()
{
	setcursor(0);
	char ch = ' ';
	int x = 33, y = 40;
	char direction{};
	int bullets[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int shotsX[10], shotsY[10];
	srand(time(NULL));
	START_spawn();
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'q' && x > 0 && y > 0) { direction = 'Q'; }
			if (ch == 'e' && x < 65 && y > 0) { direction = 'E'; }
			if (ch == 'z' && x > 0 && y < 52) { direction = 'Z'; }
			if (ch == 'c' && x < 65 && y < 52) { direction = 'C'; }
			if (ch == 'a' && x > 0) { direction = 'L'; }
			if (ch == 'd' && x < 65) { direction = 'R'; }
			if (ch == 'w' && y > 0) { direction = 'F'; }
			if (ch == 's' && y < 52) { direction = 'B'; }
			if (ch == 'x') { direction = 'S'; }
			if (ch == ' ') {
				for (int i = 0; i < 10; i++) {
					if (bullets[i] == 0) {
						bullets[i] = 1;
						shotsX[i] = x + 2;
						shotsY[i] = y;
						break;
					}
				}
			}
			fflush(stdin);
		}

		if (direction == 'Q' && x > 0 && y > 0) { erase_ship(x, y); draw_ship(--x, --y); }
		if (direction == 'E' && x < 65 && y > 0) { erase_ship(x, y); draw_ship(++x, --y); }
		if (direction == 'Z' && x > 0 && y < 52) { erase_ship(x, y); draw_ship(--x, ++y); }
		if (direction == 'C' && x < 65 && y < 52) { erase_ship(x, y); draw_ship(++x, ++y); }
		if (direction == 'L' && x > 0) { erase_ship(x, y); draw_ship(--x, y); }
		if (direction == 'R' && x < 65) { erase_ship(x, y); draw_ship(++x, y); }
		if (direction == 'F' && y > 0) { erase_ship(x, y); draw_ship(x, --y); }
		if (direction == 'B' && y < 52) { erase_ship(x, y); draw_ship(x, ++y); }
		if (direction == 'S') { erase_ship(x, y); draw_ship(x, y); }
		for (int i = 0; i < 10; i++) {
			if (bullets[i] == 1) {
				if (shotsY[i] < 52) {
					erase_bullet(shotsX[i], shotsY[i]);
				}
				if (shotsY[i] > 0) {
					draw_bullet(shotsX[i], --shotsY[i]);
				}
				else {
					bullets[i] = 0;
				}
			}
		}

		Sleep(100);
	} while (ch != 'b');

	return 0;
}




