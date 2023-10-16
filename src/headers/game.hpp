#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "snake.hpp"
#include "fruit.hpp"

struct berryPosition {
    int x, y;
};

class Game {
public:
    Game(int gridSize, int sWidth, int sHeight);
    void run();
    void init();
private:
    int mGridSize;
    int mScreenWidth;
    int mScreenHeight;
    Snake mSnake;
    sf::RenderWindow mWindow;
    Fruit mBerry;
    Fruit mAckee;
    enum Status { PLAYING, GAME_OVER };
    Status mStatus;
    sf::RectangleShape mBerryShape;
    sf::RectangleShape mAckeeShape;
    sf::Font mFont;
    sf::Text mGameOverText;
    sf::Text mScoreText;
    sf::Clock mClock;
    sf::Vector2f mDirection;
    sf::Event mEvent;
    void handleEvents();
    void display();
};


