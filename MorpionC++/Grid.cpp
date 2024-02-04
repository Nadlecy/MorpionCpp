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