#pragma once
#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class EndScreen : public cScreen {
    private:
        sf::Font font;
        sf::Text gameOverText;
        sf::Text againText;

        sf::Texture endBackground;
        sf::Sprite endBack;
    public:
        EndScreen(sf::Vector2i& screenDimensions);
        int Run(sf::RenderWindow &Window, sf::Vector2i& screenDimensions);
};
