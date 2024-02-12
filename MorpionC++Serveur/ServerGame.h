#pragma once

#include <iostream>
#include <json/json.h>

#include "ServerGrid.h"

using namespace std;

class ServerGame
{
public:
	//server values
	Json::Value playerList;
	Json::Value actionList;

	//game values
	ServerGrid* currentGrid;
	char currentTurnSymbol;
	
	bool playing;

	ServerGame();
	
	//server functions
	bool CheckIfPlayer(string playerName);
	Json::Value GetPlayerData(string playerName); 
	Json::Value GetPlayerDataFromSymbol(char symbol);
	void NewPlayer(string playerName);

	//game functions
	void ChangeTurn();
	bool Place(int boxIndex);
	Json::Value End(char Winner);
	void Reset();
	void Play();
};

