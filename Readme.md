# Snake Game in C++

This is a simple implementation of the classic Snake game in C++. The game is played on a grid where the player controls a snake that moves around and eats food. As the snake eats berries, it grows longer and the player earns points, if the snake eat Ackee it become shorter and the player loose points. The game ends if the snake collides with a wall or with its own body.

## How to Play

To play the game, simply run the executable file. The snake will start moving automatically, and you can control its direction using the arrow keys. The game ends if the snake collides with a wall or with its own body.

## Dependencies

This game requires the following dependencies:

- C++11 or higher
- SFML library

## Installation

To install the game, simply clone the repository and compile the source code using a C++ compiler. For example:

`g++ -Wall -Wextra -pedantic -std=c++11 src/*.cpp -o bin/snake_bin -I/usr/include -lsfml-graphics -lsfml-window -lsfml-system`
