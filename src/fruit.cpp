#include "headers/fruit.hpp"

Fruit::Fruit(Type type, int gridSize) {
    mType = type;
    mPosition.x = rand() % gridSize;
    mPosition.y = rand() % gridSize;

    if (mType == Fruit::Type::MALUS) mColor = sf::Color::Red;
    else if (mType == Fruit::Type::BONUS) mColor = sf::Color::Blue;
    else mColor = sf::Color::White;
}

sf::RectangleShape Fruit::spawn(int gridSize) {
    mPosition.x = rand() % gridSize;
    mPosition.y = rand() % gridSize;

    sf::RectangleShape segmentRect(sf::Vector2f(gridSize, gridSize));
    segmentRect.setPosition(mPosition.x * gridSize, mPosition.y * gridSize);
    if (mType == Fruit::Type::MALUS) segmentRect.setFillColor(sf::Color::Blue);
    else if (mType == Fruit::Type::BONUS) segmentRect.setFillColor(sf::Color::Red);

    return segmentRect;
}

Fruit::Position Fruit::getPosition() {
    return mPosition;
}
