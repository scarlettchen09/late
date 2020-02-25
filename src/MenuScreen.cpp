#include "MenuScreen.h"
#include <iostream>

MenuScreen::MenuScreen(float width, float height){
    char file[] = "../resources/font.ttf";
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
	menu[1].setString("Instructions");
	menu[1].setPosition(sf::Vector2f(width / 1.4 - width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::Black);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 1.4, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	curState = screenState::Menu;

	instructions.setFont(font);
    instructions.setColor(sf::Color::Black);
	instructions.setString("Get to\nclass in time!\nAvoid obstacles\nand don't be\nLATE!");
	instructions.setPosition(sf::Vector2f(width / 2 + width / 20, height / 5 * 2));

	selectedItemIndex = 0;
}

void MenuScreen::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void MenuScreen::optionDraw(sf::RenderWindow& window)
{
	window.draw(option);
	window.draw(instructions);
}

void MenuScreen::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void MenuScreen::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

int MenuScreen::Run(sf::RenderWindow &Window, sf::Vector2i& screenDimensions){
    sf::Texture menuBackground;
	sf::Sprite menuBack;
	if (!menuBackground.loadFromFile("../resources/wakeup.png"))
		std::cout << "Could not load background image" << std::endl;
	menuBack.setTexture(menuBackground);
	menuBack.setScale(screenDimensions.x / menuBack.getLocalBounds().width, screenDimensions.y / menuBack.getLocalBounds().height);

	sf::Event event;
	switch(curState)
	{
	case screenState::Menu:
		while (Window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					MoveUp();
					break;

				case sf::Keyboard::Down:
					MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (selectedItemIndex)
					{
					case 0:
						std::cout << "Play button has been pressed" << std::endl;
						return 1; //Go to GameScreen
						//return;
						break;
					case 1:
						std::cout << "Instruction button has been pressed" << std::endl;
						curState = screenState::Instructions;
						//return 2; //Go to OptionScreen
						break;
					case 2:
						Window.close();
						return -1;
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				Window.close();
				return -1;
				break;

			}
		}
		Window.clear();
		Window.draw(menuBack);
		draw(Window);
		break;
	case screenState::Instructions:
		while (Window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::BackSpace:
					curState = screenState::Menu;
					break;
				case sf::Keyboard::Escape:
					curState = screenState::Menu;
					break;
				break;
				}
				break;
			case sf::Event::Closed:
				Window.close();
				return -1;
				break;

			break;
			}
		}
		Window.clear();
		Window.draw(menuBack);
		Window.draw(instructions);
	}

	Window.display();

	
}