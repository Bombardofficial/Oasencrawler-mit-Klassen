#pragma once
#include <string>
//#include <string.h> --> #include <cstring>
//#include "world.h"

class world;

class player
{
public:
	player(int life) : life(life), relicscounter(relicscounter) {} //constructor

	world* w;
	int life; //=5
	int relicscounter;
	int pos_X = 0;
	int pos_Y = 0;
	bool s_potion;
	bool b_potion;
	int potioncounter;
	int a;
	int b;
	int c;
	bool won();
	void richtung();
	void inc_life() { life++; }
	void dec_life() { life--; }
	void got_relics() { relicscounter++; }
	bool researcher;
	bool adventurer;
	
	void setWorld(world* w);
};

