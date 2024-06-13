#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
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
    void spawnTetromino();
    void check(Block& block);
    bool checkSides();
    void checkLines();
    bool checkGameOver(bool movement);
    void resetGame();
    void processEvents();
    void update(Block& block);
    void render(Block& block);
    
    sf::RenderWindow window;
    sf::Clock clock;
    bool spawning;
    bool gameOver;
    int score;
    float timer;
    float delay;
    std::array<Point, 4> tetromino, temp;
    int field[M][N];
    std::array<std::array<int, 4>, 7> figures;
};

#endif //GAME_HPP
