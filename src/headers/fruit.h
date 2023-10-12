#include <SFML/Graphics.hpp>

#ifndef FRUIT_H
#define FRUIT_H

class Fruit {
public:
    enum Type {
        MALUS,
        BONUS
    };

    struct Position {
        int x, y;
    };

    Fruit(Type type, int gridSize);
    sf::RectangleShape spawn(int gridSize);
    Position getPosition();

private:
    Type mType;
    Position mPosition;
    sf::Color mColor;
};

#endif // FRUIT_H
