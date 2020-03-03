#pragma once
#include "SFML/Graphics.hpp"

const int MAX_NUMBER_OF_ITEMS = 3;
class Menu
{
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text option;
	sf::Texture menuBackground;
	sf::Sprite menuBack;
public:
	Menu(float width, float height);
	void dispBackground(sf::RenderWindow& Window);
	void draw(sf::RenderWindow& window);
	void optionDraw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void dispGameover(sf::RenderWindow & window);
	int GetPressedItem() { return selectedItemIndex; }
};

