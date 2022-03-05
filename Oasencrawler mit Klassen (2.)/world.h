#pragma once
//#include "player.h"
class player;
class world
{
public:
	
	player* p;
	int oasis[5][5]; //layer for elements
	char world[5][5]; // layer for world
	int max_relics;
	void generate_elements();
	void generate_world();
	void printWorld();
	void elementcheck();
	
	int level_rand = 10; //it will be increased if we go to a higher level
	int native_dmg = 5;
	char buchstabe = '#';
	void gefahren();
	void relics();
	void brunnen();

	void setPlayer(player* p);


};

