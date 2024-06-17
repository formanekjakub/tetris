# Tetris Game

This is a simple Tetris game built using C++ and SFML.

## Table of Contents
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Building the Project](#building-the-project)
- [Running the Game](#running-the-game)
- [Game Controls](#game-controls)
- [Project Structure](#project-structure)
- [Acknowledgements](#acknowledgements)

## Getting Started

This project is a Tetris game implemented in C++ using the SFML library. Follow the instructions below to get started with building and running the game.

## Prerequisites

- [SFML](https://www.sfml-dev.org/download.php) (Simple and Fast Multimedia Library) installed on your system.
- A C++ compiler that supports C++11 or later.
- CMake (optional, but recommended for building the project).

## Building the Project

1. Clone the repository:

    ```sh
    git clone https://github.com/yourusername/tetris-game.git
    cd tetris-game
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

    If you are not using CMake, you can compile the project directly using your preferred C++ compiler. Ensure that you link against the SFML libraries.

## Running the Game

After building the project, you can run the game executable:

```sh
./TetrisGame
