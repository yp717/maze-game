#include "main.h" // includes the main variable file for global variables
#include <iostream> // for cin and cout
#include <ctime> // for random number generation

using namespace std;

void getPlayerInput();
void updateMaze();
void updateMazeWithoutEnemies();
void solveMaze();

// TODO: change combat names
void goblinCombat();
void caveTrollCombat();
void orcCombat();

// TODO: change character properties
struct GameUser {
	string name;
	int health;
	int attack;
	int arrows;
	int rangedAttack;
	int attackBonus;
	int mana;
	string race;
} _player;

struct RaceOne {
	int health = 50;
	int attack = 2;
	int arrows = 5;
	int rangedAttack = 4;
	int attackBonus = 1;
	int mana = 100;
	string race = "Elf";
} _elf; //Elf

struct RaceTwo {
	int health = 100;
	int attack = 4;
	int arrows = 0;
	int rangedAttack = 1;
	int attackBonus = 2;
	int mana = 0;
	string race = "Human";
} _human; // Human

struct RaceThree {
	int health = 50;
	int attack = 5;
	int arrows = 0;
	int rangedAttack = 1;
	int attackBonus = 2;
	int mana = 0;
	string race = "Dwarf";
} _dwarf; // Dwarf

struct EnemyOne {
	int health = 20;
	string name = "Goblin";
	char icon = '@';
	int attack = 3;
	int arrows = 0;
	int rangedAttack = 0;
	int attackBonus = 0;
	int mana = 0;
} _goblin; // Goblin

struct EnemyTwo {
	int health = 50;
	string name = "Cave Troll";
	char icon = '%';
	int attack = 5;
	int arrows = 0;
	int rangedAttack = 0;
	int attackBonus = 0;
	int mana = 0;
} _caveTroll; // Cave Troll

struct EnemyThree {
	int health = 40;
	string name = "Orc";
	char icon = '$';
	int attack = 4;
	int arrows = 0;
	int rangedAttack = 0;
	int attackBonus = 0;
	int mana = 0;
} _orc; // Orc

int posX;
int posY;
int exitPosX;
int exitPosY;
int prevX;
int prevY;
int enemy1PosX;
int enemy1PosY;
int enemy2PosX;
int enemy2PosY;
int enemy3PosX;
int enemy3PosY;

bool goblinDead, caveTrollDead, orcDead;
bool gameOver, firstGame;

bool playerDead;

int tokens;

// specify maze height and width
const char HEIGHT = 21, WIDTH = 41;
// icons to represent characters in the game - could these be emojis?
const char player = 'X';
const char endExit = 'E';
char goblinIcon = 'G';
char caveTrollIcon = 'C';
char orcIcon = '0';
// char undeadWarriorIcon = 'w';
char deadIcon = ' ';

// declare the maze here
// should only have a unique solution
// TODO: fog of war and random initialisation
// should also be in a separate file
unsigned char maze[HEIGHT][WIDTH] = {
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

int main () {
	srand((unsigned)time(NULL));

	char newGameChoice, solverChoice;
	string name;
	char chooseRace;
	int chooseToken;

	::tokens = rand()%4+2;

	::posX = 19;
	::posY = 7;
	exitPosX = 19;
	exitPosY = 39;

	::enemy1PosX = 18;
	::enemy1PosY = 23;

	::enemy2PosX = 5;
	::enemy3PosY = 3;

	::goblinDead = false;
	::caveTrollDead = false;
	::orcDead = false;

	::firstGame = true;
	::gameOver = false;

	::playerDead = false;

	maze[enemy1PosX][enemy1PosY] = goblinIcon;
	maze[enemy2PosX][enemy2PosY] = caveTrollIcon;
	maze[enemy3PosX][enemy3PosY] = orcIcon;

	// print a welcome statement for the user
	cout << "*********************************************\n";
	cout << "*                                           *\n";
	cout << "*           Welcome to Maze Game            *\n";
	cout << "*                                           *\n";
	cout << "*********************************************\n";

	// session initialisation
	cout << "Enter your name: " << endl;

	cin >> name;

	_player.name = name;

	cout << "Welcome " << _player.name;
	cout << "\n What class do you wish to play?" << endl;
	cout << "(e) - Elf, (h) - Human, or (d) - Dwarf" << endl;

	cin >> chooseRace;

	switch (chooseRace) {
		case 'e':
			_player.race = _elf.race;
			_player.health = _elf.health;
			_player.mana = _elf.mana;
			_player.attack = _elf.attack;
			_player.rangedAttack = _elf.rangedAttack;
			_player.arrows = _elf.arrows;
			_player.attackBonus = _elf.attackBonus;

			break;

		case 'h':
			_player.race = _human.race;
			_player.health = _human.health;
			_player.mana = _human.mana;
			_player.attack = _human.attack;
			_player.rangedAttack = _human.rangedAttack;
			_player.arrows = _human.arrows;
			_player.attackBonus = _human.attackBonus;

			break;

		case 'd':
			_player.race = _dwarf.race;
			_player.health = _dwarf.health;
			_player.mana = _dwarf.mana;
			_player.attack = _dwarf.attack;
			_player.rangedAttack = _dwarf.rangedAttack;
			_player.arrows = _dwarf.arrows;
			_player.attackBonus = _dwarf.attackBonus;

			break;

		default:
			break;
	}

	cout << "You have chosen to play as " << _player.name << " the " << _player.race << "!\n" << endl;
	cout << "Your basic stats are: " << endl;
	cout << "Health: " << _player.health << endl;
	cout << "Mana: " << _player.mana << endl;
	cout << "Damage: " << _player.attack << endl;
	cout << "Range Attack: " << _player.rangedAttack << endl;
	cout << "Arrows: " << _player.arrows << endl;
	cout << "Attack Bonus: " << _player.attackBonus << endl;
	cout << endl;
	cout << "Fear not! You have been given " << tokens << " tokens, which you can use to boost your powers!\n" << endl;
	cout << "One(1) token can be used to get:\n"
		<< "1 attack bonus\n"
		<< "3 arrows\n"
		<< "10 mana\n"
		<< "10 health\n"
		<< "1 rnaged attack\n"
		<< "1 damage\n" << endl;

	cout << "\nChoose; \n1 for attackbonus\n2 for arrows\n3 for mana\n4 for health\n5 for ranged attack\n6 for damage" << endl;

	for (tokens; tokens > 0; tokens--) {
		cout << "Tokens left: " << tokens << endl;

		cin >> chooseToken;

		switch (chooseToken) {
			case 1:
				_player.attackBonus++;
				cout << "Attack bonus: " << _player.attackBonus << endl;
				break;

			case 2:
				_player.arrows+=3;
				cout << "Arrows: " << _player.arrows << endl;
				break;

			case 3:
				_player.mana+=10;
				cout << "Mana: " << _player.mana << endl;
				break;

			case 4:
				_player.health+=10;
				cout << "Health: " << _player.health << endl;
				break;

			case 5:
				_player.rangedAttack++;
				cout << "Ranged attack: " << _player.rangedAttack << endl;
				break;

			case 6:
				_player.attack++;
				cout << "Damage: " << _player.attack << endl;
				break;

			default:
				break;
		}
	}

	cout << "\n" << endl;
	cout << _player.name << " your stats are now: " << endl;
	cout << "Health: " << _player.health << endl;
	cout << "Mana: " << _player.mana << endl;
	cout << "Damage: " << _player.attack << endl;
	cout << "Range Attack: " << _player.rangedAttack << endl;
	cout << "Arrows: " << _player.arrows << endl;
	cout << "Attack bonus" << _player.attackBonus << endl;
	cout << endl;
	cout << "You are now ready to venture into the unknown!" << endl;

	do {
		if (!firstGame) {
			cout << "Do you wish to play again?" << endl;
			cout << "y or n" << endl;
			cin >> newGameChoice;

			if (newGameChoice == 'y') {
				return main();
			} else {
				return 0;
			}
		}

		cout << "Do you wish to let the computer solve the maze?" << endl;
		cout << "y or n" << endl;
		cin >> solverChoice;

		if (solverChoice == 'y') {

			while (1) {
				sleep(1);

				updateMazeWithoutEnemies();
				solveMaze();

				if (maze[posX][posY] == endExit) {
					cout << "\n\nMAZE SOLVED!\n\n";
					break;
				}
			}

			::gameOver = true;
			::firstGame = false;
		} else {
			updateMaze();

			while (!playerDead) {
				getPlayerInput();

				updateMaze();

				if (maze[posX][posY] == endExit) {
					break;
				}

				if (maze[posX][posY] == maze[enemy1PosX][enemy1PosY] && !goblinDead) {
					// cout << "\n\nYou found a " << _goblin.name << endl;
					goblinCombat();
				}

				if (maze[posX][posY] == maze[enemy1PosX][enemy1PosY] && !caveTrollDead) {
					// cout << "\n\nYou found a " << _caveTroll.name << endl;
					caveTrollCombat();
				}

				if (maze[posX][posY] == maze[enemy1PosX][enemy1PosY] && !orcDead) {
					// cout << "\n\nYou found a " << _orc.name << endl;
					orcCombat();
				}

				// if (maze[posX][posY] == maze[enemy1PosX][enemy1PosY] && !goblinDead) {
				// 	cout << "\n\nYou found a " << _goblin.name << endl;
				// 	goblinCombat();
				// }
			}
			if (playerDead) {

			} else {
				cout << "\nYOU WON!\n" << endl;
				::gameOver = true;
				::firstGame = false;
				::playerDead = false;
			}

			/*
				1. Start at a random  cell in the grid.
				2. Look for a random neighbour cell you haven't been to yet.
				3. If you find one, move there, knocking down the wall between the cells.
					if you don't find one, bacl up to the previous cell.
				4. Repeat steps 2 and 3 until you've been to every cell in the grid.
			*/
		}


	} while (gameOver);

	return 0;
}

void goblinCombat() {
	cout << endl;
	cout << "\n" << endl;
	cout << "You found a " << _goblin.name << "!" << endl;
	cout << "Your stats are: " << "\t\t" << _goblin.name << "'s stats are: " << endl;
	cout << "Health: " << _player.health << "\t\t\t\t" << "Health: " << _goblin.health << endl;


	cout << "Mana: " << _player.mana << "\t\t\t\t" << "Mana: " << _goblin.health << endl;
	cout << "Damage: " << _player.attack << "\t\t\t\t" << "Damage: " << _goblin.attack << endl;
	cout << "Arrows: " << _player.arrows << "\t\t\t\t" << "Arrows: " << _goblin.arrows << endl;
	cout << "Range Attack: " << _player.rangedAttack << "\t\t" << "Ranged Attack: " << _goblin.rangedAttack << endl;
	cout << "Attack bonus" << _player.attackBonus << "\t\t\t" << "Attack Bonus: " << _goblin.attackBonus << endl;
	cout << "\n" << endl;
	cout << "What do you want to do?\n"
		<< "Press 1 to attack\n"
		<< "Press 2 to fire an arrow\n"
		<< "Press 3 to heal" << endl;

	while (_goblin.health > 0) {
		int goblinCombatChoice;
		cin >> goblinCombatChoice;

		switch (goblinCombatChoice) {
			case 1: {
				int doesAttackHit = rand()%6;
				int meleeDamage = _player.attack;

				if (doesAttackHit == 0) {
					cout << _player.name << " misses " << _goblin.name << endl;
				} else {
					meleeDamage *= _player.attackBonus;
					_goblin.health -=meleeDamage;

					if (_goblin.health < 0) {
						_goblin.health = 0;
					}

					cout << _player.name << " hits " << _goblin.name << " doing " << meleeDamage << " damage!" << endl;
					cout << _goblin.name << "'s health drops to " << _goblin.health << endl;
				}

				break;
			}
			case 2: {

				if (_player.arrows > 0) {
					_player.arrows--;

					int doesArrowHit = rand()%4;
					int rangeDamage = _player.rangedAttack;

					if (doesArrowHit == 0) {
						cout << _player.name << " misses " << _goblin.name << endl;
					} else {
						rangeDamage *= _player.attackBonus;
						_goblin.health -= rangeDamage;

						if (_goblin.health < 0) {
							_goblin.health = 0;
						}

						cout << _player.name << " shoots " << _goblin.name << " doing " << rangeDamage << " damage!" << endl;
						cout << _goblin.name << "'s health drops to " << _goblin.health << endl;
						cout << _player.name << " now has " << _player.arrows << " arrows left!" << endl;
					}
				} else {
					cout << _player.name << " is out of arrows!" << endl;
				}

				break;
			}
			case 3: {
				if (_player.mana > 0) {
					_player.mana-=10;

					int healHP = rand()%10+20;

					_player.health = _player.health + healHP;

					cout << _player.name << " heals for " << healHP << endl;
					cout << _player.name << " now has " << _player.health << " health and " << _player.mana << " mana!" <<endl;
				} else {
					cout << _player.name << " is out of mana!" << endl;
				}

				break;
			}
			default: {
				break;
			}
		}

		if (_goblin.health <= 0) {

			::goblinDead = true;
			cout << "\n" << _player.name << " killed " << _goblin.name << "\n" << endl;

			cout << "Press y to continue" << endl;
			char _continue;
			cin >> _continue;

			if (_continue == 'y') {
				updateMaze();
				break;
			}
		}

		int doesGoblinHit = rand()%10;
		int goblinDamage = _goblin.attack;

		if (doesGoblinHit == 0) {
			cout << _goblin.name << " misses " << _player.name << endl;
		} else {
			_player.health -= goblinDamage;

			if (_player.health < 0) {
				_player.health = 0;
			}

			cout << _goblin.name << " hits " << _player.name << " doing " << goblinDamage << " damage!" << endl;
			cout << _player.name << "'s health drop to " << _player.health << endl;

		}

		if (_player.health <= 0) {

			cout << "\n" << _goblin.name << " killed " << _player.name << "\n" << endl;

			cout << "YOU DIED!" << endl;
			cout << "Press y to continue" << endl;
			char _continue;
			cin >> _continue;

			if (_continue == 'y') {
				::playerDead = true;
				::gameOver = true;
				::firstGame = false;
				break;
			}
		} // player died
	}
}

void caveTrollCombat() {
	cout << endl;
	cout << "\n" << endl;
	cout << "You found a " << _caveTroll.name << "!" << endl;
	cout << "Your stats are: " << "\t\t" << _caveTroll.name << "'s stats are: " << endl;
	cout << "Health: " << _player.health << "\t\t\t\t" << "Health: " << _caveTroll.health << endl;


	cout << "Mana: " << _player.mana << "\t\t\t\t" << "Mana: " << _caveTroll.health << endl;
	cout << "Damage: " << _player.attack << "\t\t\t\t" << "Damage: " << _caveTroll.attack << endl;
	cout << "Arrows: " << _player.arrows << "\t\t\t\t" << "Arrows: " << _caveTroll.arrows << endl;
	cout << "Range Attack: " << _player.rangedAttack << "\t\t" << "Ranged Attack: " << _caveTroll.rangedAttack << endl;
	cout << "Attack bonus" << _player.attackBonus << "\t\t\t" << "Attack Bonus: " << _caveTroll.attackBonus << endl;
	cout << "\n" << endl;
	cout << "What do you want to do?\n"
		<< "Press 1 to attack\n"
		<< "Press 2 to fire an arrow\n"
		<< "Press 3 to heal" << endl;

	while (_caveTroll.health > 0) {
		int caveTrollCombatChoice;
		cin >> caveTrollCombatChoice;

		switch (caveTrollCombatChoice) {
			case 1: {
				int doesAttackHit = rand()%6;
				int meleeDamage = _player.attack;

				if (doesAttackHit == 0) {
					cout << _player.name << " misses " << _caveTroll.name << endl;
				} else {
					meleeDamage *= _player.attackBonus;
					_caveTroll.health -=meleeDamage;

					if (_caveTroll.health < 0) {
						_caveTroll.health = 0;
					}

					cout << _player.name << " hits " << _caveTroll.name << " doing " << meleeDamage << " damage!" << endl;
					cout << _caveTroll.name << "'s health drops to " << _caveTroll.health << endl;
				}

				break;
			}
			case 2: {

				if (_player.arrows > 0) {
					_player.arrows--;

					int doesArrowHit = rand()%4;
					int rangeDamage = _player.rangedAttack;

					if (doesArrowHit == 0) {
						cout << _player.name << " misses " << _caveTroll.name << endl;
					} else {
						rangeDamage *= _player.attackBonus;
						_caveTroll.health -= rangeDamage;

						if (_caveTroll.health < 0) {
							_caveTroll.health = 0;
						}

						cout << _player.name << " shoots " << _caveTroll.name << " doing " << rangeDamage << " damage!" << endl;
						cout << _goblin.name << "'s health drops to " << _caveTroll.health << endl;
						cout << _player.name << " now has " << _player.arrows << " arrows left!" << endl;
					}
				} else {
					cout << _player.name << " is out of arrows!" << endl;
				}

				break;
			}
			case 3: {
				if (_player.mana > 0) {
					_player.mana-=10;

					int healHP = rand()%10+20;

					_player.health = _player.health + healHP;

					cout << _player.name << " heals for " << healHP << endl;
					cout << _player.name << " now has " << _player.health << " health and " << _player.mana << " mana!" <<endl;
				} else {
					cout << _player.name << " is out of mana!" << endl;
				}

				break;
			}
			default: {
				break;
			}
		}

		if (_caveTroll.health <= 0) {

			::caveTrollDead = true;
			cout << "\n" << _player.name << " killed " << _caveTroll.name << "\n" << endl;

			cout << "Press y to continue" << endl;
			char _continue;
			cin >> _continue;

			if (_continue == 'y') {
				updateMaze();
				break;
			}
		}

		int doesCaveTrollHit = rand()%10;
		int caveTrollDamage = _caveTroll.attack;

		if (doesCaveTrollHit == 0) {
			cout << _caveTroll.name << " misses " << _player.name << endl;
		} else {
			_player.health -= caveTrollDamage;

			if (_player.health < 0) {
				_player.health = 0;
			}

			cout << _caveTroll.name << " hits " << _player.name << " doing " << caveTrollDamage << " damage!" << endl;
			cout << _player.name << "'s health drop to " << _player.health << endl;

		}

		if (_player.health <= 0) {

			cout << "\n" << _caveTroll.name << " killed " << _player.name << "\n" << endl;

			cout << "YOU DIED!" << endl;
			cout << "Press y to continue" << endl;
			char _continue;
			cin >> _continue;

			if (_continue == 'y') {
				::playerDead = true;
				::gameOver = true;
				::firstGame = false;
				break;
			}
		} // player died
	}
}

void orcCombat() {
	cout << endl;
	cout << "\n" << endl;
	cout << "You found a " << _orc.name << "!" << endl;
	cout << "Your stats are: " << "\t\t" << _orc.name << "'s stats are: " << endl;
	cout << "Health: " << _player.health << "\t\t\t\t" << "Health: " << _orc.health << endl;


	cout << "Mana: " << _player.mana << "\t\t\t\t" << "Mana: " << _orc.health << endl;
	cout << "Damage: " << _player.attack << "\t\t\t\t" << "Damage: " << _orc.attack << endl;
	cout << "Arrows: " << _player.arrows << "\t\t\t\t" << "Arrows: " << _orc.arrows << endl;
	cout << "Range Attack: " << _player.rangedAttack << "\t\t" << "Ranged Attack: " << _orc.rangedAttack << endl;
	cout << "Attack bonus" << _player.attackBonus << "\t\t\t" << "Attack Bonus: " << _orc.attackBonus << endl;
	cout << "\n" << endl;
	cout << "What do you want to do?\n"
		<< "Press 1 to attack\n"
		<< "Press 2 to fire an arrow\n"
		<< "Press 3 to heal" << endl;

	while (_orc.health > 0) {
		int orcCombatChoice;
		cin >> orcCombatChoice;

		switch (orcCombatChoice) {
			case 1: {
				int doesAttackHit = rand()%6;
				int meleeDamage = _player.attack;

				if (doesAttackHit == 0) {
					cout << _player.name << " misses " << _orc.name << endl;
				} else {
					meleeDamage *= _player.attackBonus;
					_orc.health -=meleeDamage;

					if (_orc.health < 0) {
						_orc.health = 0;
					}

					cout << _player.name << " hits " << _orc.name << " doing " << meleeDamage << " damage!" << endl;
					cout << _orc.name << "'s health drops to " << _orc.health << endl;
				}

				break;
			}
			case 2: {

				if (_player.arrows > 0) {
					_player.arrows--;

					int doesArrowHit = rand()%4;
					int rangeDamage = _player.rangedAttack;

					if (doesArrowHit == 0) {
						cout << _player.name << " misses " << _orc.name << endl;
					} else {
						rangeDamage *= _player.attackBonus;
						_orc.health -= rangeDamage;

						if (_orc.health < 0) {
							_orc.health = 0;
						}

						cout << _player.name << " shoots " << _orc.name << " doing " << rangeDamage << " damage!" << endl;
						cout << _goblin.name << "'s health drops to " << _orc.health << endl;
						cout << _player.name << " now has " << _player.arrows << " arrows left!" << endl;
					}
				} else {
					cout << _player.name << " is out of arrows!" << endl;
				}

				break;
			}
			case 3: {
				if (_player.mana > 0) {
					_player.mana-=10;

					int healHP = rand()%10+20;

					_player.health = _player.health + healHP;

					cout << _player.name << " heals for " << healHP << endl;
					cout << _player.name << " now has " << _player.health << " health and " << _player.mana << " mana!" <<endl;
				} else {
					cout << _player.name << " is out of mana!" << endl;
				}

				break;
			}
			default: {
				break;
			}
		}

		if (_orc.health <= 0) {

			::orcDead = true;
			cout << "\n" << _player.name << " killed " << _orc.name << "\n" << endl;

			cout << "Press y to continue" << endl;
			char _continue;
			cin >> _continue;

			if (_continue == 'y') {
				updateMaze();
				break;
			}
		}

		int doesOrcHit = rand()%10;
		int orcDamage = _orc.attack;

		if (doesOrcHit == 0) {
			cout << _orc.name << " misses " << _player.name << endl;
		} else {
			_player.health -= orcDamage;

			if (_player.health < 0) {
				_player.health = 0;
			}

			cout << _orc.name << " hits " << _player.name << " doing " << orcDamage << " damage!" << endl;
			cout << _player.name << "'s health drop to " << _player.health << endl;

		}

		if (_player.health <= 0) {

			cout << "\n" << _orc.name << " killed " << _player.name << "\n" << endl;

			cout << "YOU DIED!" << endl;
			cout << "Press y to continue" << endl;
			char _continue;
			cin >> _continue;

			if (_continue == 'y') {
				::playerDead = true;
				::gameOver = true;
				::firstGame = false;
				break;
			}
		} // player died
	}
}



void getPlayerInput() {
	char keyPress;
	cin >> keyPress;

	switch (keyPress) {
		case 'a':
			// move left
			if (maze[posX][posY-1] == '#') {
				cout << "ERROR!";
			} else {
				posY--;
			}
			break;

		case 'd':
			// move right
			if (maze[posX][posY+1] == '#') {
				cout << "ERROR!";
			} else {
				posY++;
			}
			break;

		case 'w':
			// move up
			if (maze[posX-1][posY] == '#') {
				cout << "ERROR!";
			} else {
				posX--;
			}
			break;

		case 's':
			// move down
			if (maze[posX+1][posY] == '#') {
				cout << "ERROR!";
			} else {
				posX++;
			}
			break;

		default:
			cout << "\n\nPress something!\n\n";
			break;
	}
}

void updateMaze() {
	unsigned char maze[HEIGHT][WIDTH] = {
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
	};

	if (!goblinDead) {
		maze[enemy1PosX][enemy1PosY] = goblinIcon;
	} else {
		maze[enemy1PosX][enemy1PosY] = deadIcon;
	}

	if (!caveTrollDead) {
		maze[enemy2PosX][enemy2PosY] = caveTrollIcon;
	} else {
		maze[enemy2PosX][enemy2PosY] = deadIcon;
	}

	if (!orcDead) {
		maze[enemy3PosX][enemy3PosY] = orcIcon;
	} else {
		maze[enemy3PosX][enemy3PosY] = deadIcon;
	}

	maze[posX][posY] = player;
	maze[exitPosX][exitPosY] = endExit;

	for (int y = 0; y < HEIGHT; y++) {
		cout << endl;
		for (int x = 0; x < WIDTH; x++) {
			cout << maze[y][x];
		}
	}
}

void updateMazeWithoutEnemies() {
	unsigned char maze[HEIGHT][WIDTH] = {
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
	};

	maze[exitPosX][exitPosY] = endExit;
	maze[posX][posY] = player;

	for (int y = 0; y < HEIGHT; y++) {
		cout << endl;
		for (int x = 0; x < WIDTH; x++) {
			cout << maze[y][x];
		}
	}
}

void solveMaze() {
	maze[posX][posY] = '.';

	if((maze[posX][posY+1] != '#') && (maze[posX][posY+1] != '.')) {
		posY = posY + 1;
	} else if ((maze[posX-1][posY] != '#') && (maze[posX-1][posY] != '.')) {
		posX = posX - 1;
	} else if ((maze[posX][posY-1] != '#') && (maze[posX][posY-1] != '.')) {
		posY = posY - 1;
	} else if ((maze[posX+1][posY] != '#') && (maze[posX+1][posY] != '.')) {
		posX = posX + 1;
	}
}
