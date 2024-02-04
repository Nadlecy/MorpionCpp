#pragma once
#include "Grid.h"

#include <iostream>

using namespace std;

class Game
{
public:
	Grid* currentGrid;
	char currentPlayerTurn;
	bool playing;

	Game();

	void ChangeTurn();
	void Place();
	void End(char Winner);
	bool AskReplay();
	void Reset();
	void Play();
};

