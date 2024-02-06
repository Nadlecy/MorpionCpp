#include "InputManager.h"
#include "GameWindow.h"

#include <iostream>
#include <SFML/Graphics.hpp>

InputManager::InputManager(GameWindow* window) {
	Window = window;
}

void InputManager::EventCheck() {

	while (Window->oWindow->pollEvent(oEvent))
	{
		if (oEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			Window->oWindow->close();
		}

		else if (oEvent.type == sf::Event::MouseButtonReleased) {
			if (oEvent.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i position = sf::Mouse::getPosition(*Window->oWindow);
				std::cout << position.x  << endl;
				std::cout << position.y << endl;
			}
		}
	}
}
