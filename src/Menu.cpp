#include "Menu.h"
#include <iostream>
#pragma warning(disable : 4996)

Menu::Menu(float width, float height)
{
	char file[] = "C://Users//delli7desktop//Documents//GitHub//late//late//resources//font.ttf";
	if (!font.loadFromFile(file))
	{
		std::cout << "Error opening \"" << file << "\"\n";
		exit(EXIT_FAILURE);
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 1.4, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::Black);
	menu[1].setString("How to \nPlay");
	menu[1].setPosition(sf::Vector2f(width / 1.4, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::Black);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 1.4, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	option.setFont(font);
	option.setColor(sf::Color::Green);
	option.setString("Jump over obstacles as \na student rushing \nto get to class\non time by pressing \nthe space key. \n\n DONT'T BE LATE!");
	option.setPosition(sf::Vector2f(width / 5, height / 5 * 2));

	selectedItemIndex = 0;
}


void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::optionDraw(sf::RenderWindow& window)
{
	window.draw(option);
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