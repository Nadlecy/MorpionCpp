#pragma once
#include "GridBox.h"

#include <vector>
#include <iostream>

using namespace std;

class Grid
{
public:
	vector<GridBox*> boxList;

	Grid();

	void Display();
	bool IsFull();
	char WinCheck();
};

