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
	}
}

bool InputManager::Event() {
	if (oEvent.type == sf::Event::MouseButtonReleased) {
		if (oEvent.mouseButton.button == sf::Mouse::Left) {

			mouseX = (oEvent.mouseButton.x - 100) / (Window->windowH / 3); // a modifier le 100 pour rendre la page responsive ( car il y a des bords a gauche et a droit qu'il ne faut pas compter)
			mouseY = oEvent.mouseButton.y / (Window->windowH / 3) * 3;

			return true;
		}
	}
	return false;
}
