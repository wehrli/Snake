#include <iostream>

#include <SFML/Graphics.hpp>

#include <ncurses.h>

// #define KEY_UP 72
// #define KEY_DOWN 80
// #define KEY_LEFT 75
// #define KEY_RIGHT 77

#include "headers/game.h"

using namespace std;

Game::Game(int gridSize, int sWidth, int sHeight) : 
    mGridSize(gridSize),
    mScreenWidth(sWidth),
    mScreenHeight(sHeight),
    mSnake(gridSize),
    mWindow(sf::VideoMode(sWidth, sHeight), "SFML Snake Game"),
    mBerry(Fruit::Type::BONUS, gridSize),
    mAckee(Fruit::Type::MALUS, gridSize) {
        mDirection = sf::Vector2f(1, 0);
        mBerryShape = mBerry.spawn(gridSize);
        mAckeeShape = mAckee.spawn(gridSize);
}

void Game::handleEvents() {
    if (mWindow.pollEvent(mEvent)) {
         if (mEvent.type == sf::Event::Closed) {
            mWindow.close();
        }
        else if (mEvent.type == sf::Event::KeyPressed) {
            if (mEvent.key.code == sf::Keyboard::Left) mDirection = sf::Vector2f(-1, 0);
            else if (mEvent.key.code == sf::Keyboard::Right) mDirection = sf::Vector2f(1, 0);
            else if (mEvent.key.code == sf::Keyboard::Up) mDirection = sf::Vector2f(0, -1);
            else if (mEvent.key.code == sf::Keyboard::Down) mDirection = sf::Vector2f(0, 1);
        }
    }
}

sf::Text Game::gameOver() {
    sf::Font font;
    if (!font.loadFromFile("src/arial.ttf")) {
        // handle font loading error
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(mScreenWidth / 2 - gameOverText.getGlobalBounds().width / 2, mScreenHeight / 2 - gameOverText.getGlobalBounds().height / 2);

    return gameOverText;
    // sf::Text restartText("Press R to restart", font, 30);
    // restartText.setFillColor(sf::Color::White);
    // restartText.setPosition(mScreenWidth / 2 - restartText.getGlobalBounds().width / 2, mScreenHeight / 2 + restartText.getGlobalBounds().height);



        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        //     mSnake.reset();
        //     mBerryShape = mBerry.spawn(mGridSize);
        //     mAckeeShape = mAckee.spawn(mGridSize);
        //     return;
        // }
}

void Game::run() {
    while (mWindow.isOpen()) {
        handleEvents();

        if (mWindow.isOpen() && mClock.getElapsedTime().asMilliseconds() > 100) {
            mClock.restart();

            mSnake.move(mDirection);


            SnakeSegment head = mSnake.getHead();

            if (head.x < 0 || head.x >= mScreenWidth / mGridSize || head.y < 0 || head.y >= mScreenHeight / mGridSize) {
                std::cout << "Game Over" << std::endl;
                mWindow.close();
                break;
            }

            // Berry management
            Fruit::Position berryPos = mBerry.getPosition();
            Fruit::Position ackeePos = mAckee.getPosition();
            if (head.x == berryPos.x && head.y == berryPos.y) {
                mSnake.grow();
                mBerryShape = mBerry.spawn(mGridSize);
            }

            if (head.x == ackeePos.x && head.y == ackeePos.y) {
                mSnake.shrink();
                mAckeeShape = mAckee.spawn(mGridSize);
            }

            // Clear the window
            mWindow.clear();

            mWindow.draw(mBerryShape);
            mWindow.draw(mAckeeShape);
            mSnake.draw(mWindow, mGridSize);

            // Display everything
            mWindow.display();
        }
    }
}
