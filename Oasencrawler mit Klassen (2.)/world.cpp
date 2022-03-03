#include "world.h"
#include "player.h"
#include <iostream>

using namespace std;
void world::generate_elements()
{
	for (int zeile = 0; zeile < 5; zeile++)
	{
		for (int spalten = 0; spalten < 5; spalten++)
		{
			
			int place = rand() % level_rand + 1;
			if (place < 5) {
				oasis[zeile][spalten] = 0; //empty
			}
			else if (place == 5) {
				oasis[zeile][spalten] = 1; //relic
				world[zeile][spalten] = '$'; //to show where the relics are
				max_relics++;
			}
			else if (place == 6) {
				oasis[zeile][spalten] = 2; //well
			}
			else {
				oasis[zeile][spalten] = 3; //danger
			}
		}
	}
	if (max_relics == 0) { // if the game does not rolled any relic
		oasis[rand() % 5][rand() % 5] = 1;
		max_relics++;
	}
}

void world::generate_world()
{
	char buchstabe = '#'; //the symbol of the player in the world
	
	for (int zeile = 0; zeile < 5; zeile++)
	{
		for (int spalten = 0; spalten < 5; spalten++)
		{
			world[spalten][zeile] = '.';
		}
	}

	 world[p->pos_X][p->pos_Y] = buchstabe;
	 
}

void world::printWorld()
{
	for (int zeile = 0; zeile < 5; zeile++) {

		for (int spalten = 0; spalten < 5; spalten++) {

			cout << world[spalten][zeile];
		}
		if (zeile != 5) {
			cout << "\n";
		}
	}
}


void world::elementcheck() //check if this field got relic,brunnen, or gefahren, then change it to an empty field
{
	if (oasis[p->pos_X][p->pos_Y] == 0) {
		if (p->potioncounter > 0) {
			//for the potion to work properly
			p->potioncounter--;
			cout << "Remaining steps as invisible: " << p->potioncounter << endl;
		}
		
	}
	if (oasis[p->pos_X][p->pos_Y] == 1) {
		
		if (p->potioncounter > 0) {
			p->potioncounter--;
			cout << "Remaining steps as invisible: " << p->potioncounter << endl;
		}
		relics();
		oasis[p->pos_X][p->pos_Y] == 0; // after passing through an area, it changes to an empty area
	}
	else if (oasis[p->pos_X][p->pos_Y] == 2) {
		
		if (p->potioncounter > 0) {
			p->potioncounter--;
			cout << "Remaining steps as invisible: " << p->potioncounter << endl;
		}
		brunnen();
		oasis[p->pos_X][p->pos_Y] == 0;
	}
	else if (oasis[p->pos_X][p->pos_Y] == 3) {

		if (p->potioncounter > 0) {
			cout << "There was a native, but did not see you, because of the potion." << endl;
			p->potioncounter--;
			cout << "You have " << p->potioncounter << " steps left." << endl;
			
		}
		
		if (p->potioncounter == 0) {
			gefahren();
		}
		oasis[p->pos_X][p->pos_Y] == 0;
	}
}



void world::gefahren()
{
	if (rand() % 3 == 1) { //function to decide the consequences of the next move
		int hidepos;
		cout << "A native is coming! You have to hide somewhere." << endl << "Where do you hide? Left(1) or right(2)? " << endl;
		do {
			cin >> hidepos;
			if (hidepos != 1 && hidepos != 2) {
				cout << "Not possible." << endl;
				if (cin.fail()) { // if the answer is not proper for the integer variable
					cin.clear();
					string s;
					cin >> s;
				}
			}
		} while (hidepos != 1 && hidepos != 2);
		
		if (rand() % 2 == 1 && hidepos == 1) {
			cout << "Nice! The native did not find you! Go and find the relics!" << endl;
		}
		else if (rand() % 2 == 1 && hidepos == 2) {
			cout << "Nice! The native did not find you! Go and find the relics!" << endl;
		}
		else {
			cout << "Run! The native has found you and damaged you!" << endl;
			p->dec_life();
			cout << "\nYour lifepoints: " << p->life << endl;
			cout << "Found relics: " << p->relicscounter << endl << endl;
		}
	}
	else {
		cout << "\nOh no! A native attacked ";
		if (rand() % 6 == 1) {
			cout << "and damaged you out of nowhere.\nYou lost a lifepoint." << endl;
			p->dec_life();
			cout << "\nYour lifepoints: " << p->life << endl;
			cout << "Found relics: " << p->relicscounter << endl << endl;
		}
		else {
			cout << "you, but you could run away." << endl;
		}
	}
	
}

void world::relics()
{
	if (p->relicscounter < max_relics) {
		cout << "\nYou found a relic. Nice!\nGo and find the others!" << endl;
		p->got_relics();
	}
	cout << "\nYour lifepoints: " << p->life << endl;
	cout << "Found relics: " << p->relicscounter << endl << endl;
}

void world::brunnen()
{
	cout << "\nYou found a well!\n";
	if (rand() % 3 == 1) {
		int bags;
		cout << "You also found a chest in there, but there is two bag. Which one will you open first? Big(1) or small(2)?" << endl;
		cout << "You should think it through, because the bigger can contain better loot, but also can be more dangerous!" << endl;
		do {
			cin >> bags;
			if (bags != 1 && bags != 2) {
				cout << "Not possible." << endl;
				if (cin.fail()) {
					cin.clear();
					string s;
					cin >> s;
				}
			}
		} while (bags != 1 && bags != 2);
		
		if (rand() % 2 == 1 && bags == 1) { //if we chose the big bag
			
			cout << "Nice! You have found a big invisility potion! You will be invisible for the natives during your next 4 steps!" << endl;
			
			p->potioncounter = p->potioncounter + 4;
		}
		else if (rand() % 2 == 1 && bags == 2) { //if we chose the small bag
			cout << "Nice! You have found an invisility potion! You will be invisible for the natives during your next 2 steps!" << endl;
			
			p->potioncounter = p->potioncounter + 2;
		}
		else { //if there was a danger anyway
			if (bags == 1) {
				cout << "Ouch! There was a snake in the bag and bit you." << endl;
				cout << "You lost 2 lifepoint." << endl;
				p->dec_life();
				p->dec_life();
				if (p->life <= 0) {
					cout << "\nUnfortunately the natives got you and you could not escape in time!" << endl;
					cout << "Game over!" << endl;
					exit(0);
				}
				
			}
			else if (bags == 2) {
				cout << "Ouch! There was a rat in the bag and bit you." << endl;
				cout << "You lost 1 lifepoint." << endl;
				p->dec_life();
				if (p->life <= 0) {
					cout << "\nUnfortunately the natives got you and you could not escape in time!" << endl;
					cout << "Game over!" << endl;
					exit(0);
				}
			}
			cout << "\nYour lifepoints: " << p->life << endl;
			cout << "Found relics: " << p->relicscounter << endl << endl;
		}


	}
	else {
		if (p->life == 5) {
			cout << "You have maximum lifepoints, so there is no extra for you." << endl;
		}
		else {
			cout << "You could chill a little bit and earned a life point. Keep it up!" << endl;
			p->inc_life();
			cout << "\nYour lifepoints: " << p->life << endl;
			cout << "Found relics: " << p->relicscounter << endl << endl;
		}
	}
}

void world::setPlayer(player* p) // setting the connection between the world and player classes
{
	this->p = p;
}
