#include "Block.hpp"

Block::Block() {
    block.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    block.setFillColor(sf::Color::White);
    block.setOutlineThickness(1);
    block.setOutlineColor(sf::Color::Black);
}

void Block::setPosition(int x, int y) {
    block.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(block, states);
}
