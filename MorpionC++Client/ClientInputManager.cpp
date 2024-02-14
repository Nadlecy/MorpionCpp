#include "ClientInputManager.h"
#include "ClientWindow.h"

#include <iostream>
#include <SFML/Graphics.hpp>

ClientInputManager::ClientInputManager(ClientWindow* window) {
	Window = window;
	currentMessage = "";
}

void ClientInputManager::EmptyMessage() {
	currentMessage = "";
}

bool ClientInputManager::EventCheck(std::string username) {
	Json::Value board;

	while (Window->oWindow->pollEvent(oEvent))
	{
		if (oEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			Window->oWindow->close();
			return false;

		}
		else if (oEvent.type == sf::Event::MouseButtonReleased) {
			if (oEvent.mouseButton.button == sf::Mouse::Left) {

				mouseX = (oEvent.mouseButton.x - 100) / (Window->windowW / 3); // a modifier le 100 pour rendre la page responsive ( car il y a des bords a gauche et a droit qu'il ne faut pas compter)
				mouseY = oEvent.mouseButton.y / (Window->windowH / 3) * 3;
				cout << "clickyclicky";

				board["requestType"] = "Place";
				board["playerName"] = (mouseX + mouseY * 3);
				board["placeIndex"] = (mouseX + mouseY * 3);

				//making the Json into a string.
				Json::FastWriter fastWriter;
				std::string output = fastWriter.write(board);
				currentMessage = output.c_str();

				readyToSend = true;

				return true;
			}
		}
		mouseX, mouseY = NULL;
		return false;
	}
}
