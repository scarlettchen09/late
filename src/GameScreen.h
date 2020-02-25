#include "cScreen.h"
#include <SFML/Graphics.hpp>

class GameScreen : public cScreen {
    private:

    public:
        GameScreen();
        int Run(sf::RenderWindow &Window, sf::Vector2i& screenDimensions);
};