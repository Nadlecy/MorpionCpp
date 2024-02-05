#include "GameWindow.h"

GameWindow::GameWindow() {
	windowW = 800;
	windowH = 600;
    oWindow = new sf::RenderWindow(sf::VideoMode(windowW, windowH), "Morpion", sf::Style::Default);
	if (windowH < windowW)
		gameSquareS = windowH;
	else
		gameSquareS = windowW;

	oCircle = new sf::CircleShape(gameSquareS/6 - gameSquareS/12);
	oCrossBit1 = new sf::RectangleShape(sf::Vector2f(gameSquareS / 3 - gameSquareS / 15, gameSquareS / 60));
	oCrossBit2 = new sf::RectangleShape(sf::Vector2f(gameSquareS / 3 - gameSquareS / 15, gameSquareS / 60));

	oCircle->setOutlineThickness(gameSquareS / 60);
	oCircle->setOutlineColor(sf::Color(0, 128, 255));
	oCircle->setFillColor(sf::Color::Transparent);
	oCircle->setOrigin(sf::Vector2f(oCircle->getRadius()/2 + gameSquareS / 60, oCircle->getRadius() / 2 + gameSquareS / 60));

	oCrossBit1->setFillColor(sf::Color(255, 0, 128));
	oCrossBit1->setOrigin(sf::Vector2f(gameSquareS / 3 - gameSquareS / 60 / 2, gameSquareS / 30 / 2));
	oCrossBit2->setFillColor(sf::Color(255, 0, 128));
	oCrossBit2->setOrigin(sf::Vector2f(gameSquareS / 3 - gameSquareS / 60 / 2, gameSquareS / 30 / 2));
}

void GameWindow::DrawCircle(int posX, int posY) {
	int X = (windowW - gameSquareS) / 2 + (gameSquareS / 3) * posX + gameSquareS / 6;
	int Y = (windowH - gameSquareS) / 2 + (gameSquareS / 3) * posY + gameSquareS / 6;
	oCircle->setPosition(sf::Vector2f(X, Y));
	oWindow->draw(*oCircle);
}

void GameWindow::DrawCross(int posX, int posY) {
	int X = (windowW - gameSquareS) / 2 + (gameSquareS / 3) * posX;
	int Y = (windowH - gameSquareS) / 2 + (gameSquareS / 3) * posY;
	oCrossBit1->setPosition(sf::Vector2f(X, Y));
	oCrossBit2->setPosition(sf::Vector2f(X, Y));
	oCrossBit1->rotate(45);
	oCrossBit2->rotate(-45);
	oWindow->draw(*oCrossBit1);
	oWindow->draw(*oCrossBit2);
	oCrossBit1->setRotation(0);
	oCrossBit2->setRotation(0);
}

void GameWindow::Display(Grid* grid) {

	for (int line = 0; line < 3; line++) {
		for (int column = 0; column < 3; column++) {
			if (grid->boxList[line * 3 + column]->GetValue() == 'O') {
				DrawCircle(column, line);
			}
			else if(grid->boxList[line * 3 + column]->GetValue() == 'X') {
				DrawCross(column, line);
			}
		}
		cout << endl;
	}

    //Updates the window.
    oWindow->display();
}
