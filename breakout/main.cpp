#include <iostream>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

int SCREENWIDTH = 52;
int SCREENHEIGHT = 20;

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int bricks[24][2] = {
	{2,7},{2,12},{2,17},{2,22},{2,27},{2,32},{2,37},{2,42},
	{3,7},{3,12},{3,17},{3,22},{3,27},{3,32},{3,37},{3,42},
	{3,7},{4,12},{4,17},{4,22},{4,27},{4,32},{4,37},{4,42},

};




int visiblebicks[24] = { 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1 };
int ballPos[2] = { 17, 26 };
int startBall = 0;


void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void drawBorder(){
	gotoxy(0,0); cout << "-----------------------------------------------------";
	gotoxy(0, SCREENHEIGHT-1); cout << "-----------------------------------------------------";

	for (int i = 0; i < SCREENHEIGHT; i++) {
		gotoxy(0, i); cout << "|";
		gotoxy(SCREENWIDTH, i); cout << "|";
	}
}

int main() {
	drawBorder();
}