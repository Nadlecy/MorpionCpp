#include "Game.h"

Game::Game() {
	window = new GameWindow();
	inputs = new InputManager(window);
	currentGrid = new Grid();
	currentPlayerTurn = 'O';
	playing = true;

}

void Game::ChangeTurn() {
	if (currentPlayerTurn == 'O') {
		currentPlayerTurn = 'X';
	}
	else if (currentPlayerTurn == 'X') {
		currentPlayerTurn = 'O';
	}
}

void Game::Place() {
	bool hasPlaced = false;
	int boxIndex = inputs->mouseX + inputs->mouseY;

	while (!hasPlaced) {
		//cout << "Player " << currentPlayerTurn << ", enter the index of the box you want to play " << endl;
		//cin >> boxIndex;
		//cout << endl;

		//cin.clear();

		if (boxIndex < 0 || boxIndex > 8) {
			cout << "Please enter a valid number!";
			continue;
		}
		else if (currentGrid->boxList[boxIndex]->GetValue() != ' ') {
			cout << "This box is already taken!";
			continue;
		}
		else {
			currentGrid->boxList[boxIndex]->SetValue(currentPlayerTurn);
			hasPlaced = true;
		}
	}
}

void Game::End(char Winner) {
	currentGrid->Display();
	window->Display(currentGrid);

	if (Winner == ' ')
		cout << "It's a draw!" << endl;
	else
		cout << Winner << " wins !" << endl;
}

bool Game::AskReplay() {
	string answer;
	while (true) {
		cout << "Would you like to play again ? Y/N" << endl;
		cin >> answer;
		cout << endl;

		cin.clear();

		if(answer == "Yes" || answer == "yes" || answer == "Y" || answer == "y"){
			return true;
		}
		else if (answer == "No" || answer == "no" || answer == "N" || answer == "n") {
			return false; 
		}
		else {
			cout << "Please answer with yes or no." << endl;
		}
	}
}

void Game::Reset() {
	delete currentGrid;
	currentGrid = new Grid();
	currentPlayerTurn = 'O';
}

void Game::Play() {
	while (true) {

		inputs->EventCheck();

		//Showing the grid
		window->Display(currentGrid);
		currentGrid->Display();

		//Checking if there is still room to play.
		if (currentGrid->IsFull()) {
			End(' ');
			break;
		}

		//A victory check happens at the end of every turn, so the moment the WinCheck succeeds, the current player is logically the winner.
		if (currentGrid->WinCheck() != ' ') {
			cout << currentGrid->WinCheck();
			End(currentPlayerTurn);
			break;
		}

		if (inputs->Event()) {

			//Asking where the current player wants to play.
			Place();

			//Switching turns.
			ChangeTurn();

			inputs->mouseX = NULL;
			inputs->mouseX = NULL;
		}
	}
	playing = AskReplay();
}