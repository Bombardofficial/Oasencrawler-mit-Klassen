#include "player.h"
#include <iostream>
#include "world.h"

using namespace std;


bool player::won()
{
	if (relicscounter == w->max_relics) {
		return true;
	}
	return false;
}

void player::richtung()
{
	char move;
	do {
		cout << "\nwalk to: ";
		cin >> move;

		switch (move) 
		{
		case 'w':
			if (pos_Y != 0) {
				w->world[pos_X][pos_Y] = '.'; //correcting the layers between moves
				w->world[pos_X][--pos_Y] = '#';
			}
			break;
		case 'a':
			if (pos_X != 0) {
				w->world[pos_X][pos_Y] = '.';
				w->world[--pos_X][pos_Y] = '#';
			}
			break;
		case 's':
			
			if (pos_Y != 4) {
				w->world[pos_X][pos_Y] = '.';
				w->world[pos_X][++pos_Y] = '#';

			}
			break;
		case 'd':
			if (pos_X != 4) {
				w->world[pos_X][pos_Y] = '.';
				w->world[++pos_X][pos_Y] = '#';
			}
			break;
		case '-':
			exit(0);
			break;
		}



	} while (move != 'w' && move != 'a' && move != 's' && move != 'd');
	

}

void player::setWorld(world* w) // setting the connection between the world and player classes
{
	this->w = w;
}
