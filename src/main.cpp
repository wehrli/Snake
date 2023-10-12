#include <iostream>

#include "headers/snake.h"
#include "headers/game.h"

#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    Game game(20, 800, 600);
    game.run();

    return 1;
}
