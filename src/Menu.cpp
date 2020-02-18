#include "Menu.h"
#include <iostream>
#pragma warning(disable : 4996)

Menu::Menu(float width, float height)
{
	char file[] = "C:\\Users\\dbiso\\Downloads\\font.ttf";
	if (!font.loadFromFile(file))
	{
		std::cout << "Error opening \"" << file << "\"\n";
		exit(EXIT_FAILURE);
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 1.4, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::Black);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 1.4, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::Black);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 1.4, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

	menu[3].setFont(font);
	menu[3].setColor(sf::Color::Black);
	menu[3].setString("There are no options available right now");
	menu[3].setPosition(sf::Vector2f(width / 1.4, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	selectedItemIndex = 0;
}


void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::optionDraw(sf::RenderWindow& window)
{
	window.draw(menu[3]);
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}