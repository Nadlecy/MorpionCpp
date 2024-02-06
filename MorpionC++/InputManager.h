#pragma once
#include <SFML/Graphics.hpp>
class GameWindow;

class InputManager
{
public:
	GameWindow* Window;
	sf::Event oEvent;
	int mouseX;
	int mouseY;

	InputManager(GameWindow* window);

	void EventCheck();

	bool Event();
};

