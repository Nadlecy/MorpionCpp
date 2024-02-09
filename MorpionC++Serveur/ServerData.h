#pragma once

#include <json/json.h>
#include <vector>

using namespace std;

class ServerData
{
public:
	Json::Value playerList ;
	Json::Value actionList;
	Json::Value scoreList;
	
	ServerData();

	bool CheckIfPlayer(string playerName);
	void NewPlayer(string playerName);
};