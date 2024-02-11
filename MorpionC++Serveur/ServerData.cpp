#include "ServerData.h"

ServerData::ServerData() {
	playerList;
	actionList;
}

bool ServerData::CheckIfPlayer(string playerName) {
	/*Checks if there is any player with this name in playerList*/

	for (int i = 0; i < playerList.size(); i++)
	{
		if (playerList[i]["username"].toStyledString() == playerName) {
			return true;
		}
	}
	return false;
}

void ServerData::NewPlayer(string playerName) {
	/*Adds a new player in the playerList json*/

	//we have to make a variable of the current size here or it'll change once we add the first chunk of data.
	int newPlrID = playerList.size();

	//setting their name
	playerList[newPlrID]["username"] = playerName;
	//initializing the score
	playerList[newPlrID]["score"] = 0;

	//determining the player's ID lets us decide if they're playing or spectating in this server
	playerList[newPlrID]["playerSessionID"] = newPlrID;
}


/* JSON for new player should be like : 

{
	"username" : playerName (string)
	"score" : 0 (int)
	"playerSessionID" : (int)
}

for old player : 

{
	"username" : playerName (string)
	"score" : /player score/ (int)
	"playerSessionID" : [] (int)

}

*/