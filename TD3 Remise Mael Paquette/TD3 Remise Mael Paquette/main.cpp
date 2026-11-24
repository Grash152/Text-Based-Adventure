#include <iostream>
#include <string>
#include <cstdlib>
#include "main.h"
#include "conio.h"
#include <thread>
#include <chrono>

using namespace std;
using namespace this_thread;
using namespace chrono;

weapon g_equippedWeapon;
Rooms g_currentRoom;

int main()
{
	
	Init();
	string name = NameCharacter();
	
	while (g_gameOn) {
		switch (g_currentRoom) {
		case FirstRoom:
			system("cls");
			Entrance(name);
			break;
		case DeadEnd:
			system("cls");
			EmptyRoom(name);
			break;
		case EnemyRoom:
			system("cls");
			BossRoom(name);
			break;
		}
	}
	return 0;
}

void Init() {
	srand(time(NULL));
	g_currentRoom = FirstRoom;
	g_fromDeadEnd = false;
}

string NameCharacter() {
	string entry;
	char confirm;
	while (true) {
		cout << "What is your character's name?\n";
		cin >> entry;
		cout <<"his name is, "<< entry << " correct ? Y / N\n";
		cin >> confirm;
		if (confirm == 'y' || confirm == 'Y')
			return entry;
		else if (confirm == 'n' || confirm == 'N')
			continue;
		else
			cout << "Sorry, i didn't get that" << entry << "is his name, correct ? Y/N \n";
	}

}

void Entrance(std::string name) {
	char input = ' ';
	while (true) {
		cout << "\033[H";
		if (g_fromDeadEnd == false) {
			cout << name << " is standing in a small room. \nThere is nothing around him except dust.\n\nOn the wall in front of him there is a \033[31mRed Door\033[0m, and a \033[34mBlue Door\033[0m on the wall to the left. \n\n What does he do ? \n\n";
			cout << "Current weapon : " << g_equippedWeapon.name[g_equipped] << " Press [1] for sword or [2] for warhammer             " << endl << endl;
			cout << "[W] Go for the \033[31mRed Door\033[0m     [A] Go for the \033[34mBlue Door\033[0m" << endl << endl;

			input = _getch();
			if (input == 'w') {
				cout << name << " approaches the \033[31mRed Door\033[0m and turns the knob. the door open and he enters the new room" << endl;
				g_currentRoom = EnemyRoom;
				break;
			}
			else if (input == 'a') {
				cout << name << " approaches the \033[34mBlue Door\033[0m and turns the knob. the door open and he enters the new room" << endl;
				g_currentRoom = DeadEnd;
				break;
			}
			else if (input == '1')
				g_equipped = Sword;
			else if (input == '2')
				g_equipped = Warhammer;
			else
				continue;
		}


		else if (g_fromDeadEnd == true) {
			cout << name << " is back in the dusty small room. \nOn the wall to his left  there is a \033[31mRed Door\033[0m, and a \033[34mBlue Door\033[0m on the wall behind him. \n\n What does he do ? \n\n";
			cout << "Current weapon : " << g_equippedWeapon.name[g_equipped] << " Press [1] for sword or [2] for warhammer               " << endl << endl;
			cout << "[A] Go for the \033[31mRed Door\033[0m     [S] Go for the \033[34mBlue Door\033[0m" << endl << endl;

			input = _getch();
			if (input == 'a') {
				cout << name << " approaches the \033[31mRed Door\033[0m and turns the knob. the door open and he enters the new room" << endl;
				g_currentRoom = EnemyRoom;
				break;
			}
			else if (input == 's') {
				cout << name << " approaches the \033[34mBlue Door\033[0m and turns the knob. the door open and he enters the previous room" << endl;
				g_currentRoom = DeadEnd;
				break;
			}
			else if (input == '1')
				g_equipped = Sword;
			else if (input == '2')
				g_equipped = Warhammer;
			else
				continue;
		}

	}
}

void EmptyRoom(std::string name){
	g_fromDeadEnd = true;
	char input = ' ';
	while (true)
	{
		cout << "\033[H";
		cout << name << " is standing in a big and empty room, there is clutter everywhere and no door except the \033[34mBlue Door\033[0m he came from \n\n What does he do?\n\n";
		cout << "Current weapon : " << g_equippedWeapon.name[g_equipped] << " Press [1] for sword or [2] for warhammer                " << endl << endl;
		cout << "[S] Go back through the \033[34mBlue Door\033[0m" << endl << endl;

		input = _getch();
		if (input == 's') {
			cout << name << " approaches the \033[34mBlue Door\033[0m and turns the knob. the door open and he enters the previous room" << endl;
			g_currentRoom = FirstRoom;
			break;
		}
		else if (input == '1')
			g_equipped = Sword;
		else if (input == '2')
			g_equipped = Warhammer;
		else
			continue;
	}
}

void BossRoom(std::string name){
	char input = ' ';
	int playerHp = MAX_PLAYER_HP;
	int enemyHp = MAX_ENEMY_HP;
	int turnNumber = 0;
	bool potion = true;
	
	while (true) {
		cout << "\033[H";
		cout << "As " << name << " enters the room, he hears a cry of challenge as a huge troll immediatly charges at him.\n\n";
		cout << name << " and the Troll have started a fight!" << endl << endl;
		cout << "Current weapon : " << g_equippedWeapon.name[g_equipped] << " Press [1] for sword or [2] for warhammer             " << endl << endl;
		cout << name << "'s HP : " << playerHp << "/" << MAX_PLAYER_HP << "        Troll's HP : " << enemyHp << "/" << MAX_ENEMY_HP << endl << endl;

		if (turnNumber % 2 == 1) {
			cout << "The troll attacks!                   \n\n";
			if (rand()%2 == 1) {
				cout << "The troll hits " << name << " for 15 damage!                                     ";
				if (playerHp - TROLL_DAMAGE <= 0) {
					playerHp = 0;
					Defeat(name, ' ');
					break;
				}
				else
					playerHp -= TROLL_DAMAGE;
			}
			else
				cout << "The troll misses                             ";
			sleep_for(seconds(DELAY));
			system("cls");
			turnNumber++;
		}
		else if (turnNumber % 2 == 0) {
			cout << "It's " << name << " turn to attack!                        \n\n";
			cout << "What does he do?                       \n\n";
			cout << "[A] Attack        [F] Flee        [P] Potion                      " << endl << endl;
			input = _getch();
			if (input == '1')
				g_equipped = Sword;
			else if (input == '2')
				g_equipped = Warhammer;
			else if (input == 'a'){
				cout << name << " uses his " << g_equippedWeapon.name[g_equipped] << " to deal " << g_equippedWeapon.damage[g_equipped] << " to the troll            ";
				sleep_for(seconds(DELAY));
				if (enemyHp - g_equippedWeapon.damage[g_equipped] <= 0) {
					enemyHp = 0;
					Victory(name);
					break;
				}
				else
					enemyHp -= g_equippedWeapon.damage[g_equipped];
				
				system("cls");
				turnNumber++;
				
			}
			else if (input == 'f') {
				cout << name << " gets scared and runs away!" << endl << endl;
				enemyHp -= g_equippedWeapon.damage[g_equipped];
				sleep_for(seconds(DELAY));
				Defeat(name, input);	
				break;
			}
			else if (input == 'p' && potion == true) {
				cout << name << " uses his Healt Potion to heal back to full health                          " << endl << endl;
				cout << name << " has lost item : Healt Potion                        ";
				playerHp = MAX_PLAYER_HP;
				potion = false;
				sleep_for(seconds(DELAY));
				system("cls");
				turnNumber++;
				
			}
			else if (input == 'p' && potion == false) {
				cout << name << " Doesn't have any potion left                            ";
				
			}
			
		}
	}
}

void Defeat(string name, char how) {
	char choice = ' ';
	system("cls");
	cout << " ::::::::      :::     ::::    ::::  ::::::::::       ::::::::  :::     ::: :::::::::: :::::::::  " << endl;
	cout << ":+:    :+:   :+: :+:   +:+:+: :+:+:+ :+:             :+:    :+: :+:     :+: :+:        :+:    :+: " << endl;
	cout << "+:+         +:+   +:+  +:+ +:+:+ +:+ +:+             +:+    +:+ +:+     +:+ +:+        +:+    +:+ " << endl;
	cout << ":#:        +#++:++#++: +#+  +:+  +#+ +#++:++#        +#+    +:+ +#+     +:+ +#++:++#   +#++:++#:  " << endl;
	cout << "+#+   +#+# +#+     +#+ +#+       +#+ +#+             +#+    +#+  +#+   +#+  +#+        +#+    +#+ " << endl;
	cout << "#+#    #+# #+#     #+# #+#       #+# #+#             #+#    #+#   #+#+#+#   #+#        #+#    #+# " << endl;
	cout << " ########  ###     ### ###       ### ##########       ########      ###     ########## ###    ### " << endl << endl << endl;

	sleep_for(seconds(DELAY));
	if (how == 'f') {
		cout << name << " ran away from the troll" << endl << endl;
	}
	else
		cout << name << " was beaten by the troll" << endl << endl;
	cout << "Do you want to try again? Y/N" << endl;

	cin >> choice;
	if (choice == 'n')
		g_gameOn = false;
	else if (choice == 'y')
		Init();
}


void Victory(string name) {
	char choice = ' ';
	system("cls");
	cout << "`8.`888b           ,8'  8 8888     ,o888888o.8888888 8888888888 ,o888888o.     8 888888888o. `8.`8888.      ,8' " << endl;
	cout << " `8.`888b         ,8'   8 8888    8888     `88.    8 8888    . 8888     `88.   8 8888    `88. `8.`8888.    ,8'  " << endl;
	cout << "  `8.`888b       ,8'    8 8888 ,8 8888       `8.   8 8888   ,8 8888       `8b  8 8888     `88  `8.`8888.  ,8'   " << endl;
	cout << "   `8.`888b     ,8'     8 8888 88 8888             8 8888   88 8888        `8b 8 8888     ,88   `8.`8888.,8'    " << endl;
	cout << "    `8.`888b   ,8'      8 8888 88 8888             8 8888   88 8888         88 8 8888.   ,88'    `8.`88888'     " << endl;
	cout << "     `8.`888b ,8'       8 8888 88 8888             8 8888   88 8888         88 8 888888888P'      `8. 8888      " << endl;
	cout << "      `8.`888b8'        8 8888 88 8888             8 8888   88 8888        ,8P 8 8888`8b           `8 8888      " << endl;
	cout << "       `8.`888'         8 8888 `8 8888       .8'   8 8888   `8 8888       ,8P  8 8888 `8b.          8 8888      " << endl;
	cout << "        `8.`8'          8 8888    8888     ,88'    8 8888    ` 8888     ,88'   8 8888   `8b.        8 8888      " << endl;
	cout << "         `8.`           8 8888     `8888888P'      8 8888       `8888888P'     8 8888     `88.      8 8888      " << endl << endl << endl;

	sleep_for(seconds(DELAY));

	cout << name << " has managed to beat the troll" << endl << endl;
	cout << "Do you want to try again? Y/N" << endl;

	cin >> choice;
	while (true) {
		if (choice == 'n') {
			g_gameOn = false;
			break;
		}
		else if (choice == 'y') {
			Init();
			break;
		}
		else
			cout << "Sorry, i didn't get that. Do you want to try again? Y/N";
	}
}