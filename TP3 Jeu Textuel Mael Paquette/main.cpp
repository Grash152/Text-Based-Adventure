
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <mmsystem.h>
#include "main.h"
#include "conio.h"

#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace this_thread;
using namespace chrono;

positionLocal g_position;
positionGlobal g_room;
weapon equippedWeapon;

int main()
{
	Init();

	while(true) {
		for (int y = 0; y < HAUTEUR_LOCALE; y++) {
			for (int x = 0; x < LARGEUR_LOCALE; x++) {
				g_currentMap[x][y] = g_bufferMap[x][y];
			}
		}
		Frame(g_nomPerso, g_position.x, g_position.y, false);
		if (_kbhit()) {
				Inputs(g_position.x, g_position.y);
			
		}

		
	}
	return 0;
}

#pragma region InitialisationDuJeu;

void Init() {
	srand(time(NULL));
	InitMapLocale();
	InitMapGlobale();
	g_nomPerso = NomPersonnage();
	RoomMaker();
	HANDLE hStdOut = NULL;
	CONSOLE_CURSOR_INFO curInfo;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hStdOut, &curInfo);
	curInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &curInfo);

	PlaySound(TEXT("Overworld.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void InitMapLocale() {
	for (int y = 0; y < HAUTEUR_LOCALE; y++) {
		for (int x = 0; x < LARGEUR_LOCALE; x++) {
			if (y == 0 || y == HAUTEUR_LOCALE - 1) {
				g_currentMap[x][y] = MUR_HORIZONTALE;
				g_bufferMap[x][y] = MUR_HORIZONTALE;
			}
			else if (x == 0 || x == LARGEUR_LOCALE - 1) {
				g_currentMap[x][y] = MUR_VERTICALE;
				g_bufferMap[x][y] = MUR_VERTICALE;
			}
			else {
				g_currentMap[x][y] = ' ';
				g_bufferMap[x][y] = ' ';
			}
		}
	}
	g_currentMap[0][0] = MUR_COIN_00;
	g_currentMap[0][HAUTEUR_LOCALE - 1] = MUR_COIN_0Y;
	g_currentMap[LARGEUR_LOCALE - 1][0] = MUR_COIN_X0;
	g_currentMap[LARGEUR_LOCALE - 1][HAUTEUR_LOCALE - 1] = MUR_COIN_XY;
	g_bufferMap[0][0] = MUR_COIN_00;
	g_bufferMap[0][HAUTEUR_LOCALE - 1] = MUR_COIN_0Y;
	g_bufferMap[LARGEUR_LOCALE - 1][0] = MUR_COIN_X0;
	g_bufferMap[LARGEUR_LOCALE - 1][HAUTEUR_LOCALE - 1] = MUR_COIN_XY;

}

void InitMapGlobale() {
	g_globalMap[2][4] = Entrance;
	g_globalMap[1][4] = FirstRoom;
	g_globalMap[2][3] = SecondRoom;
	g_globalMap[3][3] = BossRoom;

}

string NomPersonnage()
{
	string name = " ";
	char confirmation = ' ';
	cout << "Enter your character's name: ";
	cin >> name;
	cout << "Your name is: " << name << ", correct? Y/N" << endl;
	while (true) {
		cin >> confirmation;
		if (confirmation == 'y' || confirmation == 'Y')
		{
			cout << "Great! Welcome " << name << endl;
			return name;
		}
		else if (confirmation == 'n' || confirmation == 'N')
		{
			NomPersonnage();
		}
		else
		{
			cout << "I'm sorry, i didn't understand" << endl << "Your name is: " << name << ", correct? Y/N" << endl;
		}
	}
}

#pragma endregion

void Frame(string name, int posX, int posY, bool transit) {
	cout << "\033[H";
	cout << "Your name : " << name << "                            " << endl;
	for (int y = 0; y < HAUTEUR_LOCALE; y++) {
		cout << "                               ";
		for (int x = 0; x < LARGEUR_LOCALE; x++) {
			if (x == posX && y == posY)
				cout << PERSONNAGE;
			else if (transit == false) {
				cout << g_currentMap[x][y];
			}
			else
				cout << g_transitMap[x][y];
		}
		cout << endl;
	}
	cout << "Current Weapon : " << equippedWeapon.name[input] << endl;
	cout << "Coordinates : [" << g_room.x << "] . [" << g_room.y << "]";
}

char Inputs(int &x, int &y)
{
	input = _getch();
	switch (input) {
	case 'w':
		if (g_currentMap[x][y - 1] == ' ' && y != 0)
			y -= 1;
		else if (y==0) {
			g_room.y --;
			Transition('w');
		}
		break;

	case 's':
		if (g_currentMap[x][y + 1] == ' ' && y != HAUTEUR_LOCALE - 1)
			y += 1;
		else if(y==HAUTEUR_LOCALE) {
			g_room.y++;
			Transition('s');
		}
		break;

	case 'd':
		if (g_currentMap[x + 1][y] == ' ' && x != LARGEUR_LOCALE - 1)
			x += 1;
		else if(x== LARGEUR_LOCALE - 1) {
			g_room.x++;
			Transition('d');
		}

		break;
	case 'a':
		if (g_currentMap[x - 1][y] == ' ' && x != 0)
			x-= 1;
		else if (x==0){
			g_room.x--;
			Transition('a');

		}
		break;

	case '1':
		input = Sword;
		break;
	case '2':
		input = Warhammer;
		break;
	default:
		break;
	}

	return 0;
}

#pragma region Transition&RoomMaking

void Transition(char direction) {
	

	RoomMaker();
	bool frame = true;
	if (direction == 'a') {
		g_currentMap[0][0] = 203;
		g_currentMap[0][HAUTEUR_LOCALE - 1] = 202;
		int i = 1;
		int ii = 0;
		int iii = 1;

		while (iii < LARGEUR_LOCALE) {
			int XX = LARGEUR_LOCALE - 2 - iii;
			int x = 0;
			for (;x + iii < LARGEUR_LOCALE; x++) {
				for (int y = 0;y < HAUTEUR_LOCALE; y++) {
					g_transitMap[x + iii][y] = g_currentMap[x][y];
				}
			}
			for (int X = 0;X < iii;X++) {
				for (int y = 0; y < HAUTEUR_LOCALE; y++) {
					g_transitMap[X][y] = g_bufferMap[XX][y];
				}
				XX++;
			}
			if (i < LARGEUR_LOCALE)
				g_position.x = i;
			i++;
			iii++;
			Frame(g_nomPerso, g_position.x, g_position.y, frame);
			if (iii == LARGEUR_LOCALE - 1) {
				frame = false;
				for (int y = 0; y < HAUTEUR_LOCALE; y++) {
					for (int x = 0; x < LARGEUR_LOCALE; x++) {
						g_currentMap[x][y] = g_bufferMap[x][y];
					}
				}
			}
			while (_kbhit())
				char ignoreInput = _getch();
		}
	}
	if (direction == 'd') {
		g_currentMap[LARGEUR_LOCALE - 1][0] = 203;
		g_currentMap[LARGEUR_LOCALE - 1][HAUTEUR_LOCALE - 1] = 202;
		int i = LARGEUR_LOCALE - 1;
		int ii = 0;
		int iii = 0;
		while (iii < LARGEUR_LOCALE) {
			int XX = iii;
			int x = LARGEUR_LOCALE - 1;
			for (;x - iii > 0; x--) {
				for (int y = 0;y < HAUTEUR_LOCALE; y++) {
					g_transitMap[x - iii][y] = g_currentMap[x][y];
					g_transitMap[0][y] = g_currentMap[x][y];
				}
			}
			for (int X = LARGEUR_LOCALE - 1;X > LARGEUR_LOCALE - 1 - iii;X--) {
				for (int y = 0; y < HAUTEUR_LOCALE; y++) {
					g_transitMap[X][y] = g_bufferMap[XX][y];
				}
				XX--;
			}
			if (i != -1)
				g_position.x = i;
			i--;
			iii++;
			Frame(g_nomPerso, g_position.x, g_position.y, frame);
			if (iii == LARGEUR_LOCALE - 1) {
				frame = false;
				for (int y = 0; y < HAUTEUR_LOCALE; y++) {
					for (int x = 0; x < LARGEUR_LOCALE; x++) {
						g_currentMap[x][y] = g_bufferMap[x][y];
					}
				}
			}
			while (_kbhit())
				char ignoreInput = _getch();
		}
	}
	if (direction == 'w') {
		g_currentMap[0][0] = 204;
		g_currentMap[LARGEUR_LOCALE - 1][0] = 185;
		int i = 1;
		int ii = 0;
		int iii = 1;

		while (iii < HAUTEUR_LOCALE) {
			int YY = HAUTEUR_LOCALE - 1 - iii;
			int y = 0;
			for (;y + iii < HAUTEUR_LOCALE; y++) {
				for (int x = 0;x < LARGEUR_LOCALE; x++) {
					g_transitMap[x][y + iii] = g_currentMap[x][y];
				}
			}
			for (int Y = 0;Y < iii;Y++) {
				for (int x = 0; x < LARGEUR_LOCALE; x++) {
					g_transitMap[x][Y] = g_bufferMap[x][YY];
				}
				YY++;
			}
			if (i < HAUTEUR_LOCALE)
				g_position.y = i;
			i++;
			iii++;
			Frame(g_nomPerso, g_position.x, g_position.y, frame);
			if (iii == HAUTEUR_LOCALE) {
				frame = false;
				for (int y = 0; y < HAUTEUR_LOCALE; y++) {
					for (int x = 0; x < LARGEUR_LOCALE; x++) {
						g_currentMap[x][y] = g_bufferMap[x][y];
					}
				}
			}
			while (_kbhit())
				char ignoreInput = _getch();
		}
	}
	if (direction == 's') {
		g_currentMap[0][HAUTEUR_LOCALE - 1] = 204;
		g_currentMap[LARGEUR_LOCALE - 1][19] = 185;
		int i = HAUTEUR_LOCALE - 1;
		int ii = 0;
		int iii = 0;
		while (iii < HAUTEUR_LOCALE) {
			int YY = iii;
			int y = HAUTEUR_LOCALE - 1;
			for (;y > 0; y--) {
				for (int x = 0;x < LARGEUR_LOCALE; x++) {
					g_transitMap[x][y - iii] = g_currentMap[x][y];
				}
			}
			for (int Y = 19;Y > 19 - iii;Y--) {
				for (int x = 0; x < LARGEUR_LOCALE; x++) {
					g_transitMap[x][Y] = g_bufferMap[x][YY];
				}
				YY--;
			}
			if (i != -1)
				g_position.y = i;
			i--;
			iii++;
			Frame(g_nomPerso, g_position.x, g_position.y, frame);
			if (iii == HAUTEUR_LOCALE) {
				frame = false;
				for (int y = 0; y < HAUTEUR_LOCALE; y++) {
					for (int x = 0; x < LARGEUR_LOCALE; x++) {
						g_currentMap[x][y] = g_bufferMap[x][y];
					}
				}
			}
		}
		while (_kbhit())
			char ignoreInput = _getch();
	}

}


void RoomMaker() {

	switch (g_globalMap[g_room.x][g_room.y])
	{
	case Entrance:
		BufferClean();
		Porte(1, 0, 0, 1);
		g_bufferMap[13][10] = 153;
		break;
	case FirstRoom:
		BufferClean();
		Porte(0, 0, 1, 0);
		g_bufferMap[40][8] = 156;
		break;
	case SecondRoom:
		BufferClean();
		Porte(0, 1, 1, 0);
		g_bufferMap[24][14] = 158;
		break;
	case BossRoom:
		BufferClean();
		Porte(0, 0, 0, 1);
		g_bufferMap[57][10] = 178;
		break;
	case FourWayCrossroad:
		BufferClean();
		Porte(1, 1, 1, 1);
		break;
	default:
		break;
	}
}

void Porte(bool haut, bool bas, bool droite, bool gauche) {
	if (haut) {
		for (int i = (LARGEUR_LOCALE/2 - 4); i <= (LARGEUR_LOCALE / 2 + 4); i++) {
			g_bufferMap[i][0] = ' ';
		}
	}
	else {
		for (int i = (LARGEUR_LOCALE / 2 - 4); i <= (LARGEUR_LOCALE / 2 + 4); i++) {
			g_bufferMap[i][0] = MUR_HORIZONTALE;
		}
	}
	if (bas) {
		for (int i = (LARGEUR_LOCALE / 2 - 4); i <= (LARGEUR_LOCALE / 2 + 4); i++) {
			g_bufferMap[i][HAUTEUR_LOCALE - 1] = ' ';
		}
	}
	else {
		for (int i = (LARGEUR_LOCALE / 2 - 4); i <= (LARGEUR_LOCALE / 2 + 4); i++) {
			g_bufferMap[i][HAUTEUR_LOCALE - 1] = MUR_HORIZONTALE;
		}
	}
	if (droite) {
		for (int i = (HAUTEUR_LOCALE / 2 - 2); i <= (HAUTEUR_LOCALE / 2 + 2); i++) {
			g_bufferMap[LARGEUR_LOCALE - 1][i] = ' ';
		}
	}
	else {
		for (int i = (HAUTEUR_LOCALE / 2 - 2); i <= (HAUTEUR_LOCALE / 2 + 2); i++) {
			g_bufferMap[LARGEUR_LOCALE - 1][i] = MUR_VERTICALE;
		}
	}
	if (gauche) {
		for (int i = (HAUTEUR_LOCALE / 2 - 2); i <= (HAUTEUR_LOCALE / 2 + 2); i++) {
			g_bufferMap[0][i] = ' ';
		}
	}
	else {
		for (int i = (HAUTEUR_LOCALE / 2 - 2); i <= (HAUTEUR_LOCALE / 2 + 2); i++) {
			g_bufferMap[0][i] = MUR_VERTICALE;
		}
	}
}

void BufferClean() {
	for (int x = 0; x < LARGEUR_LOCALE; x++) {
		for (int y = 0;y < HAUTEUR_LOCALE; y++) {
			if (g_bufferMap[x][y] != ' ' && g_bufferMap[x][y] != MUR_VERTICALE && g_bufferMap[x][y] != MUR_HORIZONTALE && g_bufferMap[x][y] != MUR_COIN_00 && g_bufferMap[x][y] != MUR_COIN_0Y && g_bufferMap[x][y] != MUR_COIN_X0 && g_bufferMap[x][y] != MUR_COIN_XY) {
				g_bufferMap[x][y] = ' ';
			}
		}
	}
}

#pragma endregion

