#include "Grid.h"

//creates a new grid composed of 9 empty boxes
Grid::Grid() {
	for (int i = 0; i < 9; i++)
	{
		boxList.push_back(new GridBox());
	}
}

//shows the current state of the grid in the console
void Grid::Display() {
	for (int line = 0; line < 3; line++) {
		for (int column = 0; column < 3; column++) {
			cout << boxList[line * 3 + column]->GetValue();
		}
		cout << endl;
	}
}

//Checks if the grid is full
bool Grid::IsFull() {
	for (int i = 0; i < 9; i++) {
		if (boxList[i]->GetValue() == ' ')
			return false;
	}
	return true;
}

//Returns the character of the winner, if either player wins.
char Grid::WinCheck() {
	//checking the lines
	for (int i = 0; i < 3; i++) {
		if (boxList[i * 3]->GetValue() == boxList[i * 3 + 1]->GetValue() == boxList[i * 3 + 2]->GetValue())
			cout << "gagné, " << boxList[i * 3]->GetValue();
			return boxList[i * 3]->GetValue();
	}

	//checking the columns
	for (int i = 0; i < 3; i++) {
		if (boxList[i]->GetValue() == boxList[i + 3]->GetValue() == boxList[i + 6]->GetValue())
			cout << "gagné, " << boxList[i]->GetValue();
			return boxList[i]->GetValue();
	}

	//checking the diagonals
	if ((boxList[0]->GetValue() == boxList[4]->GetValue() == boxList[8]->GetValue()) || (boxList[2]->GetValue() == boxList[4]->GetValue() == boxList[6]->GetValue()))
		return boxList[4]->GetValue(); //if someone wins via a diagonal, the winner will always have their symbol in the middle of the grid.

	//if this point is reached, no win condition was met.
	return ' ';
}