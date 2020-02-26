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

public:
	Menu(float width, float height);

	void draw(sf::RenderWindow& window);
	void optionDraw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
};

