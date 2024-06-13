#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class Block : public sf::Drawable {
public:
    Block();
    void setPosition(int x, int y);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape block;
};

#endif // BLOCK_HPP
