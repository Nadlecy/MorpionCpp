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

		else if (oEvent.type == sf::Event::MouseButtonPressed) {
			if (oEvent.mouseButton.button == sf::Mouse::Left) {

				mouseX = oEvent.mouseButton.x;
				mouseY = oEvent.mouseButton.y;

				std::cout << "the right button was pressed" << std::endl;
				std::cout << "mouse x: " << mouseX << std::endl;
				std::cout << "mouse y: " << mouseY << std::endl;
			}
		}
	}
}
