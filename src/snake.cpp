#include "headers/snake.hpp"

#include <iostream>

using namespace std;

Snake::Snake(int gridSize) {
    body.push_back({gridSize / 2, gridSize / 2});
}

void Snake::move(sf::Vector2f dir) {
    for (int i = body.size() - 1; i > 0; --i) {
        body[i].x = body[i - 1].x;
        body[i].y = body[i - 1].y;
    }

    body[0].x += dir.x;
    body[0].y += dir.y;
}

void Snake::draw(sf::RenderWindow& window, int gridSize) {
    for (const auto& segment : body) {
        sf::RectangleShape segmentRect(sf::Vector2f(gridSize, gridSize));
        segmentRect.setPosition(segment.x * gridSize, segment.y * gridSize);
        segmentRect.setFillColor(sf::Color::Green);
        window.draw(segmentRect);
    }
}

void Snake::grow() {
    body.push_back({body[body.size() - 1].x, body[body.size() - 1].y});
}

void Snake::shrink() {
    body.pop_back();
}

int Snake::size() {
    return body.size();
}

bool Snake::isColiding() {
    if (body.size() <= 1) return false;

    SnakeSegment head = body[0];
    for (uint i = 1; i < body.size(); ++i) {
        if (head.x == body[i].x && head.y == body[i].y) return true;
    }

    return false;
}

SnakeSegment Snake::getHead() {
    return body[0];
}

std::vector<SnakeSegment> Snake::getBody() {
    return body;
}


// Path: src/headers/snake.h