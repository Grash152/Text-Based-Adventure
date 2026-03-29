#pragma once
#include <string>

const char PERSONNAGE = 219;
const char MUR_VERTICALE = 186;
const char MUR_HORIZONTALE = 205;
const char MUR_COIN_00 = 201;
const char MUR_COIN_0Y = 200;
const char MUR_COIN_X0 = 187;
const char MUR_COIN_XY = 188;
const unsigned int LARGEUR_LOCALE = 81;
const unsigned int HAUTEUR_LOCALE = 27;
const unsigned int LARGEUR_GLOBALE = 5;
const unsigned int HAUTEUR_GLOBALE = 5;
char g_currentMap[LARGEUR_LOCALE][HAUTEUR_LOCALE];
int g_globalMap[LARGEUR_GLOBALE][HAUTEUR_GLOBALE];
char g_transitMap[LARGEUR_LOCALE][HAUTEUR_LOCALE];

char g_bufferMap[LARGEUR_LOCALE][HAUTEUR_LOCALE];

char g_entrance[LARGEUR_LOCALE][HAUTEUR_LOCALE];
char g_room1[LARGEUR_LOCALE][HAUTEUR_LOCALE];

std::string g_nomPerso;
char input;

void Init();
void InitMapGlobale();
std::string NomPersonnage();
void Map(char &map);
void Equipement();
char Inputs(int &X, int &Y);
void InitMapLocale();
void Frame(std::string name, int posX, int posY, bool transit);
void Porte(bool haut, bool bas, bool droite, bool gauche);
void BufferClean();

void Transition(char direction);


void RoomMaker();

struct positionLocal {
	int x = 30;
	int y = 10;
};

struct positionGlobal {
	int x = 2;
	int y = 4;
};

struct weapon {
	int damage[2] = { 5,15 };
	std::string name[2] = { "Sword             ", "Warhammer             "};
};

enum Rooms {
	Entrance,
	FirstRoom,
	SecondRoom,
	BossRoom,
	FourWayCrossroad,
};


enum weaponsList {
	Sword,
	Warhammer
};