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
		if (!font.loadFromFile(filePrefixH + "font.ttf"))
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
		if (!menuBackground.loadFromFile(filePrefixH + "wakeup.png"))
			throw(std::string("Could not background image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

	menuBack.setTexture(menuBackground);
	menuBack.setScale(width / menuBack.getLocalBounds().width, height / menuBack.getLocalBounds().height);
}

void Menu::mainMenu(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage)
{
	Menu menu(Window.getSize().x, Window.getSize().y);
	sf::Event event;
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
						startGame(Window, screenDimensions, sound, view, playerTexture, bImage, menu);
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

void Menu::startGame(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage, Menu menu)
{
	sf::Event Event;
	sf::View hudView; //hudView (for Score) initialized with default pos values: top left corner of window screen
	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	sf::Clock clock;
	sf::Time time;
	auto loopCounter = 0u;
	int levelIndex = 20; //For adjusting the rate in which obstacles are generated. range should be 50 to 10 (low to high difficulty).
	float frametime = 1.0f / 60.0f; //Updates 60 times per second
	bool autoPlay = true;
	const int numObstacle = 100;

	std::vector<Obstacle*> obstacleCollection; //STL Container: vector
	Score score;
	Player player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);

	player.setXvelocity(11.0f);
	player.setJumpHeight(22.0f);
	player.speedUp(2.0f);
	assignObstacleType(obstacleCollection, numObstacle, screenDimensions);

	time = clock.restart();
	score.startScore();

	while (Window.isOpen())
	{
		if (loopCounter % 400 == 0) 
		{
			obstacleCollection.clear();
			assignObstacleType(obstacleCollection, numObstacle, screenDimensions);
		}
		time += clock.restart();
		loopCounter++;
		while (Window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Space)
				{
					if (player.jump())
					{
						sound.play();
					}
				}
				if (Event.key.code == sf::Keyboard::Escape)
				{
					player.resetWindowView(position, screenDimensions, view, Window);
					mainMenu(Window, screenDimensions, sound, view, playerTexture, bImage);
				}
				break;
			default://to avoid program crash when unknown inputs are encountered
				break;
			}
		}
		position.x += player.getXvelocity();
		if (loopCounter % 400 == 0)
		{
			position.x = screenDimensions.x / 2;
			player.resetPlayerPos();
			player.getSprite().setPosition(player.getPosition());
		}
		view.setCenter(position);
		Window.setView(view);
		player.update();
		Window.draw(bImage);
		Window.draw(player.getSprite());
		time -= sf::seconds(frametime);

		for (auto obs : obstacleCollection) //C++ 11 Feature: range based for loop and auto
		{
			Window.draw(obs->getObstacle());

			if (player.getHitbox().intersects(obs->getHitbox()))
			{
				player.resetWindowView(position, screenDimensions, view, Window);
				//mainMenu(Window, screenDimensions, sound, view, playerTexture, bImage);
				menu.displayGameOver(Window, screenDimensions, sound, view, playerTexture, bImage);
			}
			if (autoPlay && player.getCushion().intersects(obs->getHitbox()))
			{
				player.jump();
				sound.play();
			}
		}

		score.update();
		Window.setView(hudView);
		Window.draw(score.getText());
		Window.draw(score.getLabel());
		Window.display();
		Window.clear();
	}
}

void Menu::assignObstacleType(std::vector<Obstacle*>& obstacleCollection, int numObstacle, sf::Vector2i screenDimensions)
{
	int squirrelDimX, squirrelDimY, birdDimX, birdDimY;
	sf::Texture squirrel;
	sf::Texture bird;
	std::string filePrefixH = "C://Users//delli7desktop//Documents//GitHub//late//late//resources//";
	std::string filePrefixLinux = "../resources/";

	squirrelDimX = 67;
	squirrelDimY = 50;
	birdDimX = 51;
	birdDimY = 40;

	try
	{
		if (!squirrel.loadFromFile(filePrefixH + "squirrel.png"))
			throw(std::string("Could not load squirrel image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

	try
	{
		if (!bird.loadFromFile(filePrefixH + "bird.png"))
			throw(std::string("Could not load bird image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

	auto seed = std::chrono::system_clock::now().time_since_epoch().count(); //C++ 11 feature: use of chrono library, better than ctime. auto is also C++ 11 feature

	std::default_random_engine generator(seed); //C++ 11 feature: using generator and distribution using <random> header for random numbers
	std::uniform_int_distribution<int> distribution(0, 1);
	//makeRandomObstacles(obstacleCollection, numObstacle ,screenDimensions, squirrelDimX, squirrelDimY, birdDimX, birdDimY, squirrel, bird, generator, distribution);
	int randObstacleType;

	for (int i = 0; i < numObstacle; i++)
	{
		//int randObstacleType = distribution(generator);
		switch (randObstacleType = distribution(generator); randObstacleType) //C++ 17 feature: initializing expression inside a switch statement
		{
		case 0:
		{
			obstacleCollection.push_back(new Obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(squirrelDimX, squirrelDimY), squirrel, sf::IntRect(30, 0, squirrelDimX, squirrelDimY)));
			break;
		}
		case 1:
		{
			obstacleCollection.push_back(new AirObstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(birdDimX, birdDimY), bird, sf::IntRect(20, 0, birdDimX, birdDimY)));
			break;
		}
		}
	}
	for (int i = 0; i < numObstacle; i++)
	{
		obstacleCollection[i]->generateObstacle(screenDimensions.x * (i + 1));
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

void Menu::displayGameOver(sf::RenderWindow& window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage)
{
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		option.setFont(font);
		option.setColor(sf::Color::Red);
		option.setString("------Game Over.------\n\n\n\nYou failed to get \nto class on time.\n\n\nPress Escape to exit.\n\nOr backspace \nto return to main menu.");
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