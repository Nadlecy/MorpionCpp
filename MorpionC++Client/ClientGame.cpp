#include "ClientGame.h"

ClientGame::ClientGame() {
	window = new ClientWindow();
	inputs = new ClientInputManager(window);
	currentPlayerTurn = 'O';
	playing = true;
	for (int i = 0; i < 9; i++) {
		currentGrid.push_back(' ');
	}
}

void ClientGame::Place() {

	//change to send a place request



	/*
	bool hasPlaced = false;
	int boxIndex;

	while (!hasPlaced) {
		boxIndex = inputs->mouseX + inputs->mouseY;

		if (boxIndex < 0 || boxIndex > 8) {
			cout << "Please enter a valid number!";
			continue;
		}
		else if (currentGrid[boxIndex] != ' ') {
			cout << "This box is already taken!";
			continue;
		}
		else {
			currentGrid[boxIndex] = currentPlayerTurn;
			hasPlaced = true;
		}
	}*/
}

void ClientGame::End(char Winner) {
	window->Display(currentGrid);

	if (Winner == ' ')
		cout << "It's a draw!" << endl;
	else
		cout << Winner << " wins !" << endl;
}

bool ClientGame::AskReplay() {
	string answer;
	while (true) {
		cout << "Would you like to play again ? Y/N" << endl;
		cin >> answer;
		cout << endl;

		cin.clear();

		if (answer == "Yes" || answer == "yes" || answer == "Y" || answer == "y") {
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
/*
void ClientGame::Play() {
	while (true) {

		inputs->EventCheck();

		//Showing the grid
		window->Display(currentGrid);


		if (inputs->EventCheck()) {

			//Asking where the current player wants to play.
			Place();

			inputs->mouseX = NULL;
			inputs->mouseY = NULL;

		}
	}
	playing = AskReplay();
}*/