#pragma once
#include <SFML/Graphics.hpp>

class ClientWindow;

class ClientInputManager
{
public:
	ClientWindow* Window;
	sf::Event oEvent;
	int mouseX;
	int mouseY;

	ClientInputManager(ClientWindow* window);

	bool EventCheck();
};

