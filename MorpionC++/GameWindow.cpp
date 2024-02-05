#include "GameWindow.h"

GameWindow::GameWindow() {
	windowW = 800;
	windowH = 600;
    oWindow = new sf::RenderWindow(sf::VideoMode(windowW, windowH), "Morpion", sf::Style::Default);
	if (windowH < windowW)
		gameSquareS = windowH;
	else
		gameSquareS = windowW;

	oCircle = new sf::CircleShape(gameSquareS/6 - gameSquareS / 30);
	oCrossBit = new sf::RectangleShape(sf::Vector2f(gameSquareS/3 - gameSquareS / 60, gameSquareS / 30));

	oCircle->setOutlineThickness(gameSquareS / 60);
	oCircle->setOutlineColor(sf::Color(0, 128, 255));
	oCircle->setFillColor(sf::Color::Transparent);

	oCrossBit->setFillColor(sf::Color(255, 0, 128));
}

void GameWindow::DrawCircle(int posX, int posY) {
	int X = (windowW - gameSquareS) / 2 + (gameSquareS / 3) * posX;
	int Y = (windowH - gameSquareS) / 2 + (gameSquareS / 3) * posY;
	oCircle->setPosition(sf::Vector2f(X, Y));
	oWindow->draw(*oCircle);
}

void GameWindow::DrawCross(int posX, int posY) {

}

void GameWindow::Display(Grid* grid) {

	for (int line = 0; line < 3; line++) {
		for (int column = 0; column < 3; column++) {
			if (grid->boxList[line * 3 + column]->GetValue() == 'O') {
				DrawCircle(column, line);
			}
		}
		cout << endl;
	}

    //Updates the window.
    oWindow->display();
}
