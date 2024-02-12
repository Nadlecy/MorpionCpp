#pragma once

#include <vector>
#include <iostream>

using namespace std;

class ServerGridBox;

class ServerGrid
{
public:
	vector<ServerGridBox*> boxList;

	ServerGrid();

	void Display();
	bool IsFull();
	char WinCheck();
};

