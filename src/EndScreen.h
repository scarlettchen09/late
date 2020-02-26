#pragma once
#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class EndScreen : public cScreen {
    private:

    public:
        EndScreen(sf::Vector2i& screenDimensions);
        int Run(sf::RenderWindow &Window, sf::Vector2i& screenDimensions);
};
