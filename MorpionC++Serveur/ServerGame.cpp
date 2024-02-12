#include "ServerGame.h"

ServerGame::ServerGame() {
	//server data
	playerList;
	actionList;

	//game data
	currentGrid = new ServerGrid();
	currentTurnSymbol = '0';
	playing = true;

}

//////////////////////////////
// 
//Server-specific functions
//
//////////////////////////////

bool ServerGame::CheckIfPlayer(string playerName) {
	/*Checks if there is any player with this name in playerList*/

	for (int i = 0; i < playerList.size(); i++)
	{
		if (playerList[i]["username"].toStyledString() == playerName) {
			return true;
		}
	}
	return false;
}

Json::Value ServerGame::GetPlayerData(string playerName) {
	/*Checks if there is anGetPlayerDatay player with this name in playerList*/

	for (int i = 0; i < playerList.size(); i++)
	{
		if (playerList[i]["username"].toStyledString() == playerName) {
			return playerList[i];
		}
	}
	return false;
}


Json::Value ServerGame::GetPlayerDataFromSymbol(char symbol) {
	/*Checks if there is anGetPlayerDatay player with this turnSymbol in playerList*/

	for (int i = 0; i < playerList.size(); i++)
	{
		if (playerList[i]["turnSymbol"].toStyledString().at(0) == symbol) {
			return playerList[i];
		}
	}
	return false;
}


void ServerGame::NewPlayer(string playerName) {
	/*Adds a new player in the playerList json*/

	//we have to make a variable of the current size here or it'll change once we add the first chunk of data.
	int newPlrID = playerList.size();


	//determining the player's ID lets us decide if they're playing or spectating in this server
	playerList[newPlrID]["playerSessionID"] = newPlrID;
	//setting their name
	playerList[newPlrID]["username"] = playerName;
	//initializing the score
	playerList[newPlrID]["score"] = 0;

	//determining the player's symbol from their ID for the session. First two players to join get to play.
	switch (newPlrID){
	case 0:
		playerList["turnSymbol"] = 'O';
		break;
	case 1:
		playerList["turnSymbol"] = 'X';
		break;
	default:
		playerList["turnSymbol"] = ' ';
	}

	/* Player JSON template :
	{
		"playerSessionID" : (int)
		"username" : playerName (string)
		"score" : 0 (int)
		"turnSymbol" : (char)
	}
	*/
}


//////////////////////////////
//
//Functions that were in the offline version of the game
//
//////////////////////////////

void ServerGame::ChangeTurn() {
	if (currentTurnSymbol == 'O') {
		currentTurnSymbol = 'X';
	}
	else if (currentTurnSymbol == 'X') {
		currentTurnSymbol = 'O';
	}
}

//should take parameters acquired from a player's request: the box's index
bool ServerGame::Place(int boxIndex) {
	//checks if the spot is occupied
	//if it isnt, add the current player's symbol.
	

	if (boxIndex < 0 || boxIndex > 8) {
		cout << "Please enter a valid number!";
		return false;
	}
	else if (currentGrid->boxList[boxIndex]->GetValue() != ' ') {
		cout << "This box is already taken!";
		return false;
	}
	else {
		currentGrid->boxList[boxIndex]->SetValue(currentTurnSymbol);

		//a return true will send a request to update the players' view outside of this function.
		return true;
	}

}

Json::Value ServerGame::End(char Winner) {
	/*this function should return an adequate json, telling the players how the game ended, ie :
	{
		gameWinner: "draw/playername1/playername2"
	}
	the clientside will figure out how to display adequate text on its own
	*/

	Json::Value gameResult;
	Json::Value winnerData;
	gameResult["requestType"] = "end";

	if (Winner == ' ') {
		cout << "It's a draw!" << endl;
		gameResult["winner"] = "draw";
	}
	else {
		cout << Winner << " wins !" << endl;
		gameResult["winner"] = Winner;

		//change the winner's score
		winnerData = GetPlayerDataFromSymbol(Winner);
		winnerData["score"] = winnerData["score"].asInt() + 1;

		playerList[winnerData["playerSessionID"].asInt()] = winnerData;
	}
	return gameResult;
}

void ServerGame::Reset() {
	delete currentGrid;
	currentGrid = new ServerGrid();
}

void ServerGame::Play() {
/*	
	while (true) {

		//await player input via requests (change the "EventCheck()" line below)
		//inputs->EventCheck();

		//Showing the grid via request to players
		//window->Display(currentGrid);
		
		
		currentGrid->Display();

		//Checking if there is still room to play.
		if (currentGrid->IsFull()) {
			End(' ');
			break;
		}

		//A victory check happens at the end of every turn, so the moment the WinCheck succeeds, the current player is logically the winner.
		if (currentGrid->WinCheck() != ' ') {
			cout << currentGrid->WinCheck();
			End(currentTurnSymbol);
			break;
		}

		if (inputs->EventCheck()) {

			//Asking where the current player wants to play.
			Place();

			//Switching turns.
			ChangeTurn();

			inputs->mouseX = NULL;
			inputs->mouseX = NULL;

		}
	}
	playing = AskReplay();
	*/
}