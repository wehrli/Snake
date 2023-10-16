#include "headers/game.hpp"

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
        mStatus = PLAYING;
}

void Game::handleEvents() {
    if (mWindow.pollEvent(mEvent)) {
        if (mEvent.type == sf::Event::Closed) {
            mWindow.close();
        }
        else if (mEvent.type == sf::Event::KeyPressed && mEvent.key.code == sf::Keyboard::Escape) {
            mWindow.close();
        }
        else if (mEvent.type == sf::Event::KeyPressed && mEvent.key.code == sf::Keyboard::R) {
            mStatus = PLAYING;
            mSnake = Snake(mGridSize);
            mDirection = sf::Vector2f(1, 0);
            mBerryShape = mBerry.spawn(mGridSize);
            mAckeeShape = mAckee.spawn(mGridSize);
        }
        else if (mEvent.type == sf::Event::KeyPressed) {
            if (mEvent.key.code == sf::Keyboard::Left) mDirection = sf::Vector2f(-1, 0);
            else if (mEvent.key.code == sf::Keyboard::Right) mDirection = sf::Vector2f(1, 0);
            else if (mEvent.key.code == sf::Keyboard::Up) mDirection = sf::Vector2f(0, -1);
            else if (mEvent.key.code == sf::Keyboard::Down) mDirection = sf::Vector2f(0, 1);
        }
    }
}

void Game::display() {
    mWindow.clear();
    mScoreText.setString("Score: " + to_string(mSnake.size() - 1));

    if (mStatus == GAME_OVER) {
        mWindow.draw(mGameOverText);
        mWindow.display();
        return;
    }

    mWindow.draw(mScoreText);
    mWindow.draw(mBerryShape);
    mWindow.draw(mAckeeShape);
    mSnake.draw(mWindow, mGridSize);

    mWindow.display();
}

void Game::init() {
    mGameOverText = sf::Text();
    mScoreText = sf::Text();
    if (!mFont.loadFromFile("src/arial.ttf")) {
        std::cout << "Failed to load arial ttf" << std::endl;

        return;
    }

    mGameOverText.setFont(mFont);
    mGameOverText.setString("Game Over\nPress R to restart\nESC to quit");
    mGameOverText.setCharacterSize(50);
    mGameOverText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    mGameOverText.setFillColor(sf::Color::Red);
    mGameOverText.setPosition(mScreenWidth / 2 - mGameOverText.getGlobalBounds().width / 2, mScreenHeight / 2 - mGameOverText.getGlobalBounds().height / 2);

    mScoreText.setFont(mFont);
    mScoreText.setString("Score: 0");
    mScoreText.setCharacterSize(25);
    mScoreText.setFillColor(sf::Color::White);
    mScoreText.setPosition(0 + mScoreText.getGlobalBounds().width / 2, 0 + mScoreText.getGlobalBounds().height / 2);
}

void Game::run() {
    while (mWindow.isOpen()) {
        handleEvents();

        if (mStatus == PLAYING && mClock.getElapsedTime().asMilliseconds() > 100) {
            mClock.restart();


            SnakeSegment head = mSnake.getHead();

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

            mSnake.move(mDirection);
            head = mSnake.getHead();

            if (head.x < 0 || head.x >= mScreenWidth / mGridSize
                || head.y < 0 || head.y >= mScreenHeight / mGridSize
                || mSnake.size() <= 0
                || mSnake.isColiding()) {
                
                mStatus = GAME_OVER;
            }

            display();
        }
    }
}
