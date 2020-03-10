#include "GameShell.h"
#include "Menu.h"
#include <iostream>
#pragma warning(disable : 4996)

Menu::Menu(): numberOfMenuOptions(3)
{
}

Menu::Menu(float width, float height) : numberOfMenuOptions(3)
{
	for(int i = 0; i < numberOfMenuOptions; i++){
		sf::Text text;
		menuOptions.push_back(text);
	}
	std::string filePrefixH = "C://Users//delli7desktop//Documents//GitHub//late//late//resources//";
	std::string filePrefixLinux = "../resources/";

	std::string file = filePrefixH + "font.ttf";

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

void Menu::mainMenu(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>&bImage)
{
	Menu menu(Window.getSize().x, Window.getSize().y);
	sf::Event event;
	GameShell startGameObject;
	while (Window.isOpen())
	{
		Window.clear();
		menu.displayBackground(Window);
		menu.drawAllOptions(Window);
		Window.display();

		while (Window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.moveUp();
					break;

				case sf::Keyboard::Down:
					menu.moveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Play button has been pressed" << std::endl;
						startGameObject.startGame(Window, screenDimensions, sound, view, playerTexture, bImage, menu);
						break;

					case 1:
						std::cout << "Help button has been pressed" << std::endl;
						while (Window.isOpen())
						{
							menu.displayBackground(Window);
							menu.drawOption(Window);
							Window.display();

							while (Window.pollEvent(event))
							{
								switch (event.type)
								{
								case sf::Event::KeyReleased:
									switch (event.key.code)
									{
									case sf::Keyboard::Backspace:
										mainMenu(Window, screenDimensions, sound, view, playerTexture, bImage);
										break;
									}
								}
							}
						}
					case 2:
						Window.close();
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				Window.close();
				break;
			}
		}
	}
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

void Menu::displayGameOver(sf::RenderWindow& window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>& bImage, std::string msg)
{
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		option.setFont(font);
		option.setColor(sf::Color::Red);
		option.setString(msg);
		option.setPosition(sf::Vector2f(window.getSize().x / 4, window.getSize().y / 5));
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
				case sf::Keyboard::BackSpace:
					mainMenu(window, screenDimensions, sound, view, playerTexture, bImage);
					break;
				case sf::Event::Closed:
					window.close();
					break;
				}
			}
		}
	}
}