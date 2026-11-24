#pragma once
#include <string>

const unsigned int MAX_PLAYER_HP = 40;
const unsigned int MAX_ENEMY_HP = 30;
const unsigned int DELAY = 3;
const unsigned int TROLL_DAMAGE = 15;
bool g_gameOn = true;

std::string NameCharacter();
void Init();
void Navigation();
void Entrance(std::string name);
void EmptyRoom(std::string name);
void BossRoom(std::string name);
void Victory(std::string name);
void Defeat(std::string name, char how);

bool g_fromDeadEnd = false;
int g_equipped = 0;

struct weapon {
	int damage[2] = { 5,15 };
	std::string name[2] = { "Sword", "Warhammer" };
};

enum Rooms {
	FirstRoom,
	DeadEnd,
	EnemyRoom
};


enum weaponsList {
	Sword,
	Warhammer
};

