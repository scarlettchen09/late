#include "Menu.h"
#include <iostream>
#pragma warning(disable : 4996)

Menu::Menu(float width, float height)
{
	std::string filePrefixH = "C://Users//delli7desktop//Documents//GitHub//late//late//resources//";
	std::string filePrefixLinux = "../resources/";

	std::string file = filePrefixLinux + "font.ttf";

	try 
	{
		if (!font.loadFromFile(filePrefixLinux + "font.ttf"))
			throw(std::string("Could not load font"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
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

	try 
	{
		if (!menuBackground.loadFromFile(filePrefixLinux + "wakeup.png"))
			throw(std::string("Could not background image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

	menuBack.setTexture(menuBackground);
	menuBack.setScale(width / menuBack.getLocalBounds().width, height / menuBack.getLocalBounds().height);
}

void Menu::dispBackground(sf::RenderWindow& Window)
{
	Window.clear();
	Window.draw(menuBack);
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

void Menu::dispGameover(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		option.setFont(font);
		option.setColor(sf::Color::Red);
		option.setString("------Game Over.------\n\n\n\nYou failed to get \nto class on time.\n\n\nPress Escape to exit.");
		option.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4));
		dispBackground(window);
		optionDraw(window);
		window.display();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;
					break;
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
		}
	}
}