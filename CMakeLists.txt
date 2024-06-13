cmake_minimum_required(VERSION 3.10)

project(MyGameProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

set(SOURCES
    src/Block.cpp
    src/Game.cpp
    src/main.cpp
)

add_executable(MyGame ${SOURCES})

target_link_libraries(MyGame sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

set_target_properties(MyGame PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)