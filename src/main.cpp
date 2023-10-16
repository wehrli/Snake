#include <iostream>

#include "headers/snake.hpp"
#include "headers/game.hpp"

#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    Game game(20, 800, 600);
    game.init();
    game.run();

    return 1;
}
