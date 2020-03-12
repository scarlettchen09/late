#include "GameShell.h"
#include "Menu.h"
#include <iostream>
#pragma warning(disable : 4996)

Menu::Menu(): numberOfMenuOptions(3), selectedItemIndex(-1)
{
}

Menu::Menu(float width, float height) : numberOfMenuOptions(3)
{
	for(int i = 0; i < numberOfMenuOptions; i++){
		sf::Text text;
		menuOptions.push_back(text);
	}
	std::string filePrefixH = "C://Users//delli7desktop//Documents//GitHub//late//late//resources//";
	std::string filePrefixLinux = "./resources/";

	std::string file = filePrefixH + "font.ttf";

	try 
	{
		if (!font.loadFromFile(filePrefixH + "font.ttf"))
			throw(std::string("Could not load font"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}
	menuOptions[0].setFont(font);
	menuOptions[0].setFillColor(sf::Color::Red);
	menuOptions[0].setString("Play");
	menuOptions[0].setPosition(sf::Vector2f(width / 15, height / (MAX_NUMBER_OF_ITEMS + 1) * 0.6));

	menuOptions[1].setFont(font);
	menuOptions[1].setFillColor(sf::Color::Black);
	menuOptions[1].setString("How to \nPlay");
	menuOptions[1].setPosition(sf::Vector2f(width / 15, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.2));

	menuOptions[2].setFont(font);
	menuOptions[2].setFillColor(sf::Color::Black);
	menuOptions[2].setString("Exit");
	menuOptions[2].setPosition(sf::Vector2f(width / 15, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.1));

	option.setFont(font);
	option.setFillColor(sf::Color::Green);
	option.setString("Jump over obstacles as \na student rushing \nto get to class\non time by pressing \nthe space key. \n\nPress backspace to \ngo back");
	option.setPosition(sf::Vector2f(static_cast<float>(width) / 5, height / 5 * 2));

	selectedItemIndex = 0;

	try 
	{
<<<<<<< Updated upstream
		if (!menuBackground.loadFromFile(filePrefixLinux + "wakeup.jpg"))
=======
		if (!menuBackground.loadFromFile(filePrefixH + "wakeup.png"))
>>>>>>> Stashed changes
			throw(std::string("Could not background image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}
	menuBackground.setSmooth(true);
	menuBack.setTexture(menuBackground);
	menuBack.setScale(width / menuBack.getLocalBounds().width, height / menuBack.getLocalBounds().height);
}

sf::IntRect* Menu::createIntRect(sf::Vector2i position, std::string item, int characterSize)
{
	int width = 0;
	int maxWidth = 0;
	int height = 0;
	height += characterSize;
	for (int i = 0; i < item.length(); i++)
	{
		width += characterSize;
		if (maxWidth < width)
			maxWidth = width;
		if (item[i] == '\n')
		{
			height += characterSize;
			width = 0;
		}
	}
	sf::IntRect* temp = new sf::IntRect(position, sf::Vector2i(maxWidth, height));
	return temp;
}


void Menu::mainMenu(sf::RenderWindow& window, sf::Vector2i screenDimensions, sf::Sound sound[], sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>&bImage)
{
	Menu menu(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	sf::Event event;
	GameShell startGameObject;

	std::vector<sf::IntRect*> option;
	menuOptions = menu.getMenuOptions();
	for (auto item : menuOptions)
	{
		option.push_back(createIntRect(sf::Vector2i(item.getPosition().x, item.getPosition().y), item.getString(), item.getCharacterSize()));
	}


	while (window.isOpen())
	{
		window.clear();
		menu.displayBackground(window);
		menu.drawAllOptions(window);
		window.display();
		
		sf::IntRect mouse(sf::Mouse::getPosition(window), sf::Vector2i(1, 1));
		if (option[0]->intersects(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << "Play button has been pressed" << std::endl;
			startGameObject.startGame(window, screenDimensions, sound, view, playerTexture, bImage, menu);
		}
		if (option[1]->intersects(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << "Help button has been pressed" << std::endl;
			helpScreen(window, screenDimensions, sound, view, playerTexture, bImage, menu, event);
		}
		if (option[2]->intersects(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			window.close();
		}
		while (window.pollEvent(event))
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
						startGameObject.startGame(window, screenDimensions, sound, view, playerTexture, bImage, menu);
						break;

					case 1:
						std::cout << "Help button has been pressed" << std::endl;
						helpScreen(window, screenDimensions, sound, view, playerTexture, bImage, menu, event);
					case 2:
						window.close();
						break;
					}
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}
	for (auto item : option)
	{
		delete item;
	}
}

void Menu::helpScreen(sf::RenderWindow& window, sf::Vector2i screenDimensions, sf::Sound sound[], sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>& bImage, Menu menu, sf::Event event)
{
	while (window.isOpen())
	{
		menu.displayBackground(window);
		menu.drawOption(window);
		window.display();

		sf::IntRect mouse(sf::Mouse::getPosition(window), sf::Vector2i(1, 1));
		sf::IntRect* option = createIntRect(sf::Vector2i(160, 480), "Press backspace to \ngo back", menuOptions[0].getCharacterSize());

		if (option->intersects(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mainMenu(window, screenDimensions, sound, view, playerTexture, bImage);
		}

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
			case sf::Event::KeyReleased:	
				if(event.key.code == sf::Keyboard::Backspace|| sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					mainMenu(window, screenDimensions, sound, view, playerTexture, bImage);
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
			
			
		}
	}
}

std::vector<sf::Text> Menu::getMenuOptions()
{
	return menuOptions;
}

void Menu::displayBackground(sf::RenderWindow& window)
{
	window.clear();
	window.draw(menuBack);
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
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < numberOfMenuOptions)
	{
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::displayGameOver(sf::RenderWindow& window, sf::Vector2i screenDimensions, sf::Sound sound[], sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>& bImage, std::string msg, Score score)
{
	std::string msgWithScore;
	msgWithScore = msg + " " + std::to_string(static_cast<int>(score.getScore())); //another C++11 feature
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		option.setFont(font);
		option.setFillColor(sf::Color::Red);
		option.setString(msg);
		option.setFillColor(sf::Color::Red);
		option.setString(msgWithScore);
		option.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) / 4, static_cast<float>(window.getSize().y) / 5));
		displayBackground(window);
		drawOption(window);
		window.display();

		sf::IntRect mouse(sf::Mouse::getPosition(window), sf::Vector2i(1, 1));
		sf::IntRect* option = createIntRect(sf::Vector2i(160, 480), msg, menuOptions[0].getCharacterSize());
		if (option->intersects(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mainMenu(window, screenDimensions, sound, view, playerTexture, bImage);
		}
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonPressed:
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Event::Closed:
					window.close();
					break;
				}
				if(event.key.code == sf::Keyboard::Backspace|| sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					mainMenu(window, screenDimensions, sound, view, playerTexture, bImage);
				}				
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}
}
<<<<<<< Updated upstream
=======

int Menu::GetPressedItem()
{
	return selectedItemIndex;
}
>>>>>>> Stashed changes
