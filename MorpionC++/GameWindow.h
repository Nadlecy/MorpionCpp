#pragma once
#include "Grid.h"

#include <SFML/Graphics.hpp>

class GameWindow
{
public:
    sf::RenderWindow* oWindow;
    sf::VideoMode oVideoMode;
    sf::Vector2i localPosition;
    int windowW;
    int windowH;
    int gameSquareS;

    sf::CircleShape* oCircle; 
    sf::RectangleShape* oCrossBit;


    GameWindow();

    void DrawCircle(int posX, int posY);
    void DrawCross(int posX, int posY);
    void Display(Grid* grid);
};

