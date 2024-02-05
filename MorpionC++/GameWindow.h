#pragma once
#include "Grid.h"

#include <SFML/Graphics.hpp>

class GameWindow
{
public:
    sf::RenderWindow* oWindow;
    sf::VideoMode oVideoMode;
    sf::Vector2i localPosition;
    int screenW;
    int screenH;

    GameWindow();

    void Display();
};

