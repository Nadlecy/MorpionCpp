#include "Game.h"

#include <iostream>
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
