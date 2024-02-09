#include "ServerData.h"

ServerData::ServerData() {
}

bool ServerData::CheckIfPlayer(string playerName) {
	for (int i = 0; i < playerList.size(); i++)
	{
		if (playerList[i]["username"] == playerName) {
			return true;
		}
	}
	return false;
}

void ServerData::NewPlayer(Json::Value* newPlayerData) {
	playerList.append(&newPlayerData);
}