#include <vector>
#include <SFML/Graphics.hpp>

#ifndef SNAKE_H
#define SNAKE_H

struct SnakeSegment {
    int x, y;
};

class Snake {
public:
    Snake(int gridSize);
    void move(sf::Vector2f dir);
    void grow();
    void shrink();
    int size();
    bool isColiding();
    void draw(sf::RenderWindow& window, int gridSize);
    SnakeSegment getHead();
    std::vector<SnakeSegment> getBody();
private:
    std::vector<SnakeSegment> body;
};

#endif // SNAKE_H