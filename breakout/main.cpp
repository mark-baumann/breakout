#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 52 //Spielrand in der Breite
#define SCREEN_HEIGHT 20 //Spielrand in der Länge

#define MINX 2 //minimale x Koordinate 
#define MINY 2 //minimale y Koordinate	
#define MAXX 49 //maximale x Koordinate
#define MAXY 19 //maximale y Koordinate

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int bricks[24][2] = {
						{2,7},{2,12},{2,17},{2,22},{2,27},{2,32},{2,37},{2,42},
						{4,7},{4,12},{4,17},{4,22},{4,27},{4,32},{4,37},{4,42},
						{6,7},{6,12},{6,17},{6,22},{6,27},{6,32},{6,37},{6,42}
};  

int visibleBricks[24] = { 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1 }; 
int boardPos[2] = { 18,22 }; 
int ballPos[2] = { 17,26 };
int startBall = 0; 
int dir = 1; // 1- TopRight, 2- TopLeft, 3- BottomLeft, 4-BottomRight
int bricksLeft = 24;
int win = 0;
int lose = 0;

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}



void drawBorder() {
	gotoxy(0, 0); cout << "----------------------------------------------------"; //erstelle den oberen und unteren Rand
	gotoxy(0, SCREEN_HEIGHT); cout << "----------------------------------------------------";

	for (int i = 0; i < SCREEN_HEIGHT; i++) { //Die Striche nur so lang wie die Höhe des Spielfeld....
		gotoxy(0, i); cout << "|"; //erstelle den linken und rechten Rand
		gotoxy(SCREEN_WIDTH, i); cout << "|";
	}
}

void drawBricks() {
	for (int i = 0; i < 24; i++) {
		if (visibleBricks[i] == 1) { //abfrage ist nötig weil sonst die bricks nicht verschwinden wenn man sie trifft
			gotoxy(bricks[i][1], bricks[i][0]); //zeichne die bricks
			cout << "±±±±";
		}
	}
}

void ballHitSlider() {
	if (ballPos[1] >= boardPos[1] && ballPos[1] <= boardPos[1] + 8) { //+8 damit das ganze Spielfeld mit dem Slider bedeckt wird
		if (ballPos[0] == boardPos[0] - 1) { //wenn der Ball die gleiche Position hat wie der Slider
			if (dir == 3) //wenn der Ball unten Links ist dann bringe ihn nach oben Links. Angenommen die Wände gibt es noch nicht...
				dir = 2;
			else if (dir == 4) //wenn der Ball von rechts unten ist, bringe ihn nach rechts oben
				dir = 1;
		}
	}
}

void ballHitBrick() {
	for (int i = 0; i < 24; i++) {
			if (ballPos[1] >= bricks[i][1] && ballPos[1] <= bricks[i][1] +8) { //+8 damit wieder das ganze SPielfled abgedeckt wird
				if (ballPos[0] == bricks[i][0]) {//wenn der Ball einen Brick trifft setze diese auf false
					visibleBricks[i] = 0;
					bricksLeft--;
				}
		}
	}
}

void play() {
	while (1) {
		system("cls");  
		drawBricks(); 
		drawBorder();

		gotoxy(boardPos[1], boardPos[0]); //Slider ausgeben
		cout << "±±±±±±±±±";

		gotoxy(ballPos[1], ballPos[0]); //Ball ausgeben, 1 ist der zweite wert (x), 0 ist der erste Wert (y)
		cout << "0";

		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'd' || ch == 'D' ) { //d nach rechts
					boardPos[1] = boardPos[1] + 2;
			}
			if (ch == 'a' || ch == 'A' ) { //a nach links
					boardPos[1] = boardPos[1] - 2;
			}
			if (ch == 32) { //Leertaste = Spielbeginn
				startBall = 1;
			}
			if (ch == 'b') { //halte das Spiel an
				break;
			}
		}

		if (startBall == 1) {
			if (dir == 1) { // TOP RIGHT
				ballPos[0] = ballPos[0] - 1;
				ballPos[1] = ballPos[1] + 2;
				if (ballPos[1] > MAXX) {
					dir = 2;
				}
				else if (ballPos[0] < MINY) {
					dir = 4;
				}
			}
			else if (dir == 2) { // TOP LEFT
				ballPos[0] = ballPos[0] - 1;
				ballPos[1] = ballPos[1] - 2;
				if (ballPos[0] < MINY) {
					dir = 3;
				}
				else if (ballPos[1] < MINX) {
					dir = 1;
				}
			}
			else if (dir == 3) { // BOTTOM LEFT
				ballPos[0] = ballPos[0] + 1;
				ballPos[1] = ballPos[1] - 2;

			}
				
				else if (ballPos[1] < MINX) {
					dir = 4;
				}
			
			else if (dir == 4) { // BOTTOM RIGHT
				ballPos[0] = ballPos[0] + 1;
				ballPos[1] = ballPos[1] + 2;
				if (ballPos[1] > MAXX) {
					dir = 3;
				}
			}

			ballHitSlider();
		}

		ballHitBrick();	
	}
}

int main()
{
	play();
	cout << "\n";
	return 0;
}
