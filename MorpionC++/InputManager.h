#pragma once
#include <SFML/Graphics.hpp>
class GameWindow;

class InputManager
{
public:
	GameWindow* Window;
	sf::Event oEvent;

	InputManager(GameWindow* window);

	void EventCheck();
};

