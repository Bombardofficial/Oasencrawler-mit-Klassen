#pragma once

#include <string>
class world;
class player; //forditaskor

class game
{
public:
	world* w;
	player* p; //lefutaskor

	game();
	void start_game();
	void thegame();

	int level = 1;
	std::string name;
};
