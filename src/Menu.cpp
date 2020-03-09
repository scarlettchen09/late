#include "Menu.h"
#include <iostream>
#pragma warning(disable : 4996)

Menu::Menu(float width, float height) : numberOfMenuOptions(3)
{
	for(int i = 0; i < numberOfMenuOptions; i++){
		sf::Text text;
		menuOptions.push_back(text);
	}
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
	menuOptions[0].setFont(font);
	menuOptions[0].setColor(sf::Color::Red);
	menuOptions[0].setString("Play");
	menuOptions[0].setPosition(sf::Vector2f(width / 1.4, height / (numberOfMenuOptions + 1) * 1));

	menuOptions[1].setFont(font);
	menuOptions[1].setColor(sf::Color::Black);
	menuOptions[1].setString("How to \nPlay");
	menuOptions[1].setPosition(sf::Vector2f(width / 1.4, height / (numberOfMenuOptions + 1) * 2));

	menuOptions[2].setFont(font);
	menuOptions[2].setColor(sf::Color::Black);
	menuOptions[2].setString("Exit");
	menuOptions[2].setPosition(sf::Vector2f(width / 1.4, height / (numberOfMenuOptions + 1) * 3));

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

void Menu::displayBackground(sf::RenderWindow& Window)
{
	Window.clear();
	Window.draw(menuBack);
}

void Menu::drawAllOptions(sf::RenderWindow& window)
{
	for(auto i : menuOptions) //C++ 11 Feature: range based for loop and auto
	{
		window.draw(i);
	}

}

void Menu::drawOption(sf::RenderWindow& window)
{
	window.draw(option);
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menuOptions[selectedItemIndex].setColor(sf::Color::Black);
		selectedItemIndex--;
		menuOptions[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < numberOfMenuOptions)
	{
		menuOptions[selectedItemIndex].setColor(sf::Color::Black);
		selectedItemIndex++;
		menuOptions[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::displayGameOver(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		option.setFont(font);
		option.setColor(sf::Color::Red);
		option.setString("------Game Over.------\n\n\n\nYou failed to get \nto class on time.\n\n\nPress Escape to exit.");
		option.setPosition(sf::Vector2f(window.getSize().x / 3, window.getSize().y / 4));
		displayBackground(window);
		drawOption(window);
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