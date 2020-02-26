#pragma once
#include "cScreen.h"
#include <SFML/Graphics.hpp>


const int MAX_NUMBER_OF_ITEMS = 3;

class MenuScreen : public cScreen {
    private:
    	int selectedItemIndex;
        sf::Font font;
        sf::Text menu[MAX_NUMBER_OF_ITEMS];
        sf::Text instructions;
        sf::Text option;
        enum class screenState {Menu, Instructions}; //C++ 11 feature
        screenState curState;

        sf::Texture menuBackground;
    	sf::Sprite menuBack;

        void draw(sf::RenderWindow& window);
	    void optionDraw(sf::RenderWindow& window);
	    void MoveUp();
	    void MoveDown();
    public:
        MenuScreen(sf::Vector2i& screenDimensions);
        int Run(sf::RenderWindow &Window, sf::Vector2i& screenDimensions);
};