#include "Game.hpp"
#include <ctime>

Game::Game()
    : window(sf::VideoMode((N+5) * BLOCK_SIZE, M * BLOCK_SIZE), "Tetris"),
        //sets up window size
      timer(0), delay(0.3f), score(0), gameOver(false), spawning(false), figures({
          {{{1,3,5,7}, sf::Color::White},  // I
           {{2,4,5,7}, sf::Color::Cyan},  // Z
           {{3,5,4,6}, sf::Color::Red},  // S
           {{3,5,4,7}, sf::Color::Blue},  // T
           {{2,3,5,7}, sf::Color::Green}, // L
           {{3,5,7,6}, sf::Color::Magenta},  // J
           {{2,3,4,5}, sf::Color::Yellow},  // O
      }})
{
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned int>(std::time(0)));
    //std::fill(&field[0][0], &field[0][0] + sizeof(field) / sizeof(field[0][0]), 0);
    //std::fill(&fieldColors[0][0], &fieldColors[0][0] + sizeof(fieldColors) / sizeof(fieldColors[0][0]), sf::Color::Black);

    spawnTetromino();

    if (!font.loadFromFile("../fonts/Arial.ttf")) {
        // Handle the error (in case the font is not found)
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition((N + 1) * BLOCK_SIZE, (M * BLOCK_SIZE)/ 2); // Position for the score text
    updateScoreText(); // Initialize the score text
}


void Game::run() {
    Block tmpBlock;
    while (window.isOpen()) {
        processEvents(tmpBlock);
        if (!gameOver) update(tmpBlock);
        render(tmpBlock);
    }
}

void Game::spawnTetromino() {
    //generates random number between 0-6
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist7(0,6);
    this->actualFigure = dist7(rng);

    for (int i = 0; i < 4; ++i) {
        tetromino[i].x = figures[actualFigure].first[i] % 2 + N / 2 - 1;
        tetromino[i].y = figures[actualFigure].first[i] / 2 - 2 ;
    }
    //tetrominoColor = color;
    spawning = true;
}

void Game::check(Block& block) {
    for (int i = 0; i < 4; ++i) {
        if (tetromino[i].y >= M || field[tetromino[i].y][tetromino[i].x].blockExists){
            block.setMovement(false);
            break;
        }
    }
}

bool Game::checkSides() {
    for (int i = 0; i < 4; ++i) {
        if (tetromino[i].y >= M || tetromino[i].x < 0 || tetromino[i].x >= N) return false;
    }
    
    return true;
}
//function to chech in there is space where to move the block

void Game::checkLines() {
    int linesCleared = 0;
    for (int i = M - 1; i >= 0; i--) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (field[i][j].blockExists) count++;
            field[i + linesCleared][j].blockExists = field[i][j].blockExists;
        }
        if (count == N) {
            linesCleared++;
        }
    }
    switch (linesCleared){
        case 1: score += 40; break;
        case 2: score += 100; break;
        case 3: score += 300; break;
        case 4: score += 1200; break;
    }

    updateScoreText();

    for (int i = 0; i < linesCleared; i++) {
        for (int j = 0; j < N; j++) {
            field[i][j].blockExists = 0;
        }
    }
}

void Game::updateScoreText() {
    scoreText.setString("Score: \n" + std::to_string(score));
}


bool Game::checkGameOver(bool movement) {
    for (int i = 0; i < N; ++i) {
        if ((field[0][i].blockExists != 0) /*&& (movement == false)*/) return true;
    }
    return false;
}

void Game::resetGame() {
    //std::fill(&field[0][0], &field[0][0] + sizeof(field) / sizeof(field[0][0]), {0, sf::Color::Black});
    for (int i = 0; i < M; ++i){
        for (int j = 0; j < N; ++j){
            field[i][j] = {0, sf::Color::Black};
        }
    }
    gameOver = false;
    score = 0;
    updateScoreText();
    spawnTetromino();
    timer = 0;
}

bool Game::canMoveRight() {
    for (int i = 0; i < 4; ++i) {
        if (field[tetromino[i].y][tetromino[i].x].blockExists)
            return false;
    }
    return true;
}

bool Game::canMoveLeft() {
    for (int i = 0; i < 4; ++i) {
        if (field[tetromino[i].y][tetromino[i].x].blockExists)
            return false;
    }
    return true;
}

void Game::processEvents(Block& block) {
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
                if (!checkSides() || !block.moving()) tetromino = temp;
            } 
            else if (e.key.code == sf::Keyboard::Left) {
                for (int i = 0; i < 4; ++i) tetromino[i].x -= 1;
                if (!checkSides() || !canMoveLeft()) for (int i = 0; i < 4; ++i) tetromino[i].x += 1;
            } 
            else if (e.key.code == sf::Keyboard::Right) {
                for (int i = 0; i < 4; ++i) tetromino[i].x += 1;
                if (!checkSides() || !canMoveRight()) for (int i = 0; i < 4; ++i) tetromino[i].x -= 1;
            }
            //moving down faster
            //else if (e.key.code == sf::Keyboard::Down) {

            //}
            else if (e.key.code == sf::Keyboard::R) resetGame();
            else if (e.key.code == sf::Keyboard::Down) fasterMode = true;
            
        }
    }
}

//moving down an checking for colision, if spawnTetromino else moves down
void Game::update(Block& block) {
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    
    if(fasterMode == true) timer += (20 * time);
    else timer += time;
    fasterMode = false;

    if (timer > delay) {
        if (spawning) {
            for (int i = 0; i < 4; ++i) {
                tetromino[i].y += 1;
            }
            check(block);
            if (!block.moving()) {
                for (int i = 0; i < 4; ++i) {
                    tetromino[i].y -= 1;
                }
                spawning = false; // Tetromino has finished spawning
                if (checkGameOver(block.moving())) {
                    gameOver = true;
                    return;
                }
            }
        } 
        else {
            for (int i = 0; i < 4; ++i) {
                tetromino[i].y += 1;
            }
            check(block);
            if (!block.moving()) {
                for (int i = 0; i < 4; ++i) {
                    tetromino[i].y -= 1;
                    field[tetromino[i].y][tetromino[i].x].blockExists = 1;
                    field[tetromino[i].y][tetromino[i].x].color = figures[actualFigure].second;
                }
                block.setMovement(true);
                spawnTetromino();
                checkLines();  // Check for full lines after placing a tetromino
                if (checkGameOver(block.moving())) {
                    gameOver = true;
                }
            }
        }

        timer = 0;
    }
}

//add function to delete row and to add score

void Game::render(Block& block) {
    window.clear();

    // Draw the black rectangle for the game area
    sf::RectangleShape gameArea(sf::Vector2f(N * BLOCK_SIZE, M * BLOCK_SIZE));
    gameArea.setFillColor(sf::Color::Black);
    window.draw(gameArea);

    // Draw the white rectangle for the score area
    sf::RectangleShape scoreArea(sf::Vector2f(5 * BLOCK_SIZE, M * BLOCK_SIZE));
    scoreArea.setFillColor(sf::Color::White);
    scoreArea.setPosition(N * BLOCK_SIZE, 0);
    window.draw(scoreArea);

    for (int i = 0; i < (M); ++i)
        for (int j = 0; j < N; ++j) {
            if (field[i][j].blockExists == 0) continue;
            block.setPosition(j, i);
            block.setColor(field[i][j].color);
            window.draw(block);
        }

    for (int i = 0; i < 4; ++i) {
        block.setPosition(tetromino[i].x, tetromino[i].y);
        block.setColor(figures[actualFigure].second);
        window.draw(block);
    }

    window.draw(scoreText);

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
        if (!font.loadFromFile("Arial.ttf")) {
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
