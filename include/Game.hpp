#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <random>
#include "Block.hpp"
#include "Constants.hpp"


struct Point {
    int x, y;
};

class Game {
public:
    Game();
    void run();

private:
    std::random_device dev;
    void spawnTetromino();
    void check(Block& block);
    bool checkSides();
    void checkLines();
    bool checkGameOver(bool movement);
    void resetGame();
    void processEvents(Block& block);
    void update(Block& block);
    void render(Block& block);
    void updateScoreText();
    bool canMoveRight();
    bool canMoveLeft();
    
    sf::RenderWindow window;
    sf::Clock clock;
    bool fasterMode = false;
    bool spawning;
    bool gameOver;
    int score;
    int actualFigure;
    float timer;
    float delay;
    std::array<Point, 4> tetromino, temp;
    struct fieldBlock
    {
        bool blockExists = false;
        sf::Color color = sf::Color::Black;
    };

    std::array<std::array<fieldBlock, N>, M> field;
    std::array<std::pair<std::array<int, 4>,sf::Color>, 7> figures;
    sf::Font font;
    sf::Text scoreText;
    //sf::Color fieldColors[M][N];
    //sf::Color tetrominoColor;
};

#endif //GAME_HPP
