#pragma once
#include <vector>

#include "GridBox.h"

using namespace std;

class Grid
{
	vector<GridBox*> boxList;

	Grid();

	void Display();
	bool IsFull();
	char WinCheck();
	
};

