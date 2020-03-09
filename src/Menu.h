#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Menu
{
private:
	const int numberOfMenuOptions;
	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text> menuOptions; //STL Container: vector
	sf::Text option;
	sf::Texture menuBackground;
	sf::Sprite menuBack;
public:
	Menu(float width, float height);
	void displayBackground(sf::RenderWindow& Window);
	void drawAllOptions(sf::RenderWindow& window);
	void drawOption(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void displayGameOver(sf::RenderWindow & window);
	int GetPressedItem() { return selectedItemIndex; }
};

