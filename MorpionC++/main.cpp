#include "Game.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

int main() {
    Game thisGame;
    while (thisGame.playing) {
        thisGame.Play();
        thisGame.Reset();
    }

    return 0;
}
