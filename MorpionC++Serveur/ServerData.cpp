#include "ServerData.h"

ServerData::ServerData() {
}

bool ServerData::CheckIfPlayer(string playerName) {
	for (int i = 0; i < playerList.size(); i++)
	{
		if (playerList[i]["username"].toStyledString() == playerName) {
			return true;
		}
	}
	return false;
}

void ServerData::NewPlayer(string playerName) {
	//playerList.append(playerName);

	playerList[playerList.size()]["username"] = playerName;
	playerList[playerList.size()]["score"] = 0;
	playerList[playerList.size()]["coup"] = Json::arrayValue;
}


/* JSON for new player should be like : 

{
	"username" : playerName (string)

	"score" : 0 (int)

	"coup" : [] (list)

}

for old player : 

{
	"username" : playerName (string)

	"score" : /player score/ (int)

	"coup" : [] (list)

}

*/