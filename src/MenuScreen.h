#include "cScreen.h"
#include <SFML/Graphics.hpp>


const int MAX_NUMBER_OF_ITEMS = 3;

class MenuScreen : public cScreen {
    private:
    	int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        sf::Text option;
        void draw(sf::RenderWindow& window);
	    void optionDraw(sf::RenderWindow& window);
	    void MoveUp();
	    void MoveDown();
    public:
        MenuScreen(float width, float height);
        int Run(sf::RenderWindow &Window, sf::Vector2i& screenDimensions);
};