#pragma once

#include <vector>
#include <iostream>

#include "ServerGridBox.h"

using namespace std;

class ServerGrid
{
public:
	vector<ServerGridBox*> boxList;

	ServerGrid();

	void Display();
	bool IsFull();
	char WinCheck();
};

