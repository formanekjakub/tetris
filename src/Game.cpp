#include "Game.hpp"
#include <ctime>

Game::Game()
    : window(sf::VideoMode(N * BLOCK_SIZE, M * BLOCK_SIZE), "Tetris"),
        //sets up window size
      timer(0), delay(0.3f), score(0), figures({
          {{1,3,5,7},  // I
           {2,4,5,7},  // Z
           {3,5,4,6},  // S
           {3,5,4,7},  // T
           {2,3,5,7},  // L
           {3,5,7,6},  // J
           {2,3,4,5}}  // O
      })
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    std::fill(&field[0][0], &field[0][0] + sizeof(field) / sizeof(field[0][0]), 0);

    spawnTetromino();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (!gameOver) update();
        render();
    }
}

void Game::spawnTetromino() {
    int figure = std::rand() % 7;
    //generates random number between 0-6
    //int xOffset = 4;

    for (int i = 0; i < 4; ++i) {
        tetromino[i].x = figures[figure][i] % 2 + N / 2 - 1/*+ xOffset*/;
        tetromino[i].y = figures[figure][i] / 2 - 2 ;
    }
    spawning = true;
}

bool Game::check() {
    for (int i = 0; i < 4; ++i) {
        if (tetromino[i].x < 0 || tetromino[i].x >= N) return false;
        else if (field[tetromino[i].y][tetromino[i].x]) return false;
        //checks if the field is already occupied
    }

    return true;
}
//function to chech in there is space where to move the block

void Game::checkLines() {
    int linesCleared = 0;
    for (int i = M - 1; i >= 0; i--) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (field[i][j]) count++;
            field[i + linesCleared][j] = field[i][j];
        }
        if (count == N) {
            linesCleared++;
        }
    }
    for (int i = 0; i < linesCleared; i++) {
        for (int j = 0; j < N; j++) {
            field[i][j] = 0;
        }
    }
}


bool Game::checkGameOver() {
    for (int i = 0; i < N; ++i) {
        if (field[0][i] != 0) return true;
    }
    return false;
}

void Game::resetGame() {
    std::fill(&field[0][0], &field[0][0] + sizeof(field) / sizeof(field[0][0]), 0);
    gameOver = false;
    spawnTetromino();
    timer = 0;
}

void Game::processEvents() {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            window.close();

        //block moving
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Up) {
                temp = tetromino;
                Point p = tetromino[1];
                for (int i = 0; i < 4; ++i) {
                    int x = tetromino[i].y - p.y;
                    int y = tetromino[i].x - p.x;
                    tetromino[i].x = p.x - x;
                    tetromino[i].y = p.y + y;
                }
                if (!check()) tetromino = temp;
            } 
            else if (e.key.code == sf::Keyboard::Left) {
                for (int i = 0; i < 4; ++i) tetromino[i].x -= 1;
                if (!check()) for (int i = 0; i < 4; ++i) tetromino[i].x += 1;
            } 
            else if (e.key.code == sf::Keyboard::Right) {
                for (int i = 0; i < 4; ++i) tetromino[i].x += 1;
                if (!check()) for (int i = 0; i < 4; ++i) tetromino[i].x -= 1;
            }
            //moving down faster
            //else if (e.key.code == sf::Keyboard::Down) {

            //}
            else if (e.key.code == sf::Keyboard::R) resetGame();
        }
    }
}

//moving down an checking for colision, if spawnTetromino else moves down
void Game::update() {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;

    if (timer > delay) {
        if (spawning) {
            for (int i = 0; i < 4; ++i) {
                tetromino[i].y += 1;
            }
            if (!check()) {
                for (int i = 0; i < 4; ++i) {
                    tetromino[i].y -= 1;
                }
                spawning = false; // Tetromino has finished spawning
                if (checkGameOver()) {
                    gameOver = true;
                    return;
                }
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                tetromino[i].y += 1;
            }

            if (!check()) {
                for (int i = 0; i < 4; ++i) {
                    tetromino[i].y -= 1;
                    field[tetromino[i].y][tetromino[i].x] = 1;
                }
                spawnTetromino();
                checkLines();  // Check for full lines after placing a tetromino
                if (checkGameOver()) {
                    gameOver = true;
                }
            }
        }

        timer = 0;
    }
}

//add function to delete row and to add score

void Game::render() {
    window.clear(sf::Color::Black);

    Block block;
    for (int i = 0; i < (M); ++i)
        for (int j = 0; j < N; ++j) {
            if (field[i][j] == 0) continue;
            block.setPosition(j, i);
            window.draw(block);
        }

    for (int i = 0; i < 4; ++i) {
        block.setPosition(tetromino[i].x, tetromino[i].y);
        window.draw(block);
    }

    if (gameOver) {
        // Create a rectangle for the game over background
        sf::RectangleShape gameOverBackground(sf::Vector2f(N * BLOCK_SIZE, 100));
        gameOverBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black
        gameOverBackground.setPosition(0, (M * BLOCK_SIZE) / 2 - 50);

        // Create the text for "Game Over"
        sf::Text gameOverText;
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);

        // Create a basic font for rendering
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            // Handle the error (in case the font is not found)
        }
        gameOverText.setFont(font);

        // Center the text
        sf::FloatRect textRect = gameOverText.getLocalBounds();
        gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        gameOverText.setPosition(N * BLOCK_SIZE / 2.0f, M * BLOCK_SIZE / 2.0f);

        window.draw(gameOverBackground);
        window.draw(gameOverText);
    }

    window.display();
}
