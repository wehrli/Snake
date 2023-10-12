#include <vector>
#include <SFML/Graphics.hpp>

#include "snake.h"
#include "fruit.h"

struct berryPosition {
    int x, y;
};

class Game {
public:
    Game(int gridSize, int sWidth, int sHeight);
    sf::Text gameOver();
    void run();
private:
    int mGridSize;
    int mScreenWidth;
    int mScreenHeight;
    Fruit mBerry;
    Fruit mAckee;
    sf::RectangleShape mBerryShape;
    sf::RectangleShape mAckeeShape;
    sf::RenderWindow mWindow;
    sf::Clock mClock;
    Snake mSnake;
    sf::Vector2f mDirection;
    sf::Event mEvent;
    void handleEvents();
};


