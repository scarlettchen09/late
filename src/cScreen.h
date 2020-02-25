#pragma once
#include "SFML/Graphics.hpp"

class cScreen
{
public :
    virtual int Run (sf::RenderWindow &Window, sf::Vector2i& screenDimensions) = 0;
};
