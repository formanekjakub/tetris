# Tetris Game

This is a simple Tetris game built using C++ and SFML.

## Table of Contents
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
- [Running the Game](#running-the-game)
- [Game Controls](#game-controls)
- [Project Structure](#project-structure)

## Getting Started

This project is a Tetris game implemented in C++ using the SFML library. Follow the instructions below to get started with building and running the game.

## Prerequisites

- [SFML](https://www.sfml-dev.org/download.php) (Simple and Fast Multimedia Library) installed on your system.
- A C++ compiler that supports C++11 or later.
- CMake.

## Building the Project

1. Clone the repository:

    ```sh
    git clone https://github.com/formanekjakub/tetris.git
    cd tetris
    ```

2. Create a build directory and navigate into it:

    ```sh
    mkdir build
    cd build
    ```

3. Build the project using CMake:

    ```sh
    cmake ..
    make
    ```

## Running the Game

After building the project, you can run the game executable:

```sh
cd bin
./tetris
```

## Game Controls

- Up Arrow: Rotate the tetromino.
- Left Arrow: Move the tetromino left.
- Right Arrow: Move the tetromino right.
- Down Arrow: Speed up the tetromino's descent.
- R: Reset the game.

## Project Structure

- main.cpp: The entry point of the application.
- Game.hpp and Game.cpp: Contains the Game class which manages the game loop, rendering, and game logic.
- Block.hpp and Block.cpp: Contains the Block class which represents each Tetris block.
- Constants.hpp: Defines game constants such as the size of the game field and block size.


