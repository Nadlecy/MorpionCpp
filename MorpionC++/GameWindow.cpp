#include "GameWindow.h"

GameWindow::GameWindow() {
    oWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Morpion", sf::Style::Default);
    screenW = sf::VideoMode::getDesktopMode().width;
    screenH = sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow owindow(sf::VideoMode(800, 600), "Morpion");

}

void GameWindow::Display() {

}