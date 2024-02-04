#pragma once
#include "Grid.h"

#include <iostream>

using namespace std;

class Game
{
	string playerName1;
	string playerName2;

	Grid* currentGrid;
	int currentPlayer;

	Game();

	void NewGame();
};

