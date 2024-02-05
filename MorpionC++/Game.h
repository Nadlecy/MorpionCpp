#pragma once
#include "Grid.h"
#include "GameWindow.h"

#include <iostream>

using namespace std;

class Game
{
public:
	GameWindow* window;
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

