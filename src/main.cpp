#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "obstacle.h"
#include "Menu.h"
#include "Score.h"
#include "player.h"
#include "airObstacle.h"
#include <iostream>
#include <string>
#include <vector>//C++ 11 Feature: range based for loop and auto
#include <chrono>
#include <random>

void loadMainFiles(sf::Texture& bTexture, sf::Texture& playerTexture, sf::Music& music, sf::SoundBuffer& jump, std::string prefix);
void mainMenu(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage);
void assignObstacleType(std::vector<Obstacle*>& obstacleCollection, int numObstacle, sf::Vector2i screenDimensions);
void startGame(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage, Menu menu);
int main()
{
	sf::Vector2i screenDimensions(800, 600);
	sf::RenderWindow Window;
	sf::Texture bTexture, playerTexture;
	sf::Sprite bImage;
	sf::SoundBuffer jump;
	sf::Music music;
	sf::View view;
	sf::Sound sound;

	std::string filePrefixH = "C://Users//delli7desktop//Documents//GitHub//late//late//resources//";
	std::string filePrefixLinux = "../resources/";
	
	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Late!");
	Window.setKeyRepeatEnabled(false);
	Window.setFramerateLimit(60);

	loadMainFiles(bTexture, playerTexture, music, jump, filePrefixLinux);

	sound.setBuffer(jump);
	bTexture.setSmooth(true);
	bImage.setTexture(bTexture);
	bImage.setScale(1.0f, 1.0f * screenDimensions.y / bTexture.getSize().y);
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	music.setLoop(true);
	music.play();

	mainMenu(Window, screenDimensions, sound, view, playerTexture, bImage);
	return 0;
}

void loadMainFiles(sf::Texture& bTexture, sf::Texture& playerTexture, sf::Music& music, sf::SoundBuffer& jump, std::string prefix)
{
	try 
	{
		if (!bTexture.loadFromFile(prefix + "deanzabackground.jpg"))
			throw(std::string("Could not load background image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}
	try
	{
		if (!playerTexture.loadFromFile(prefix + "player_spritesheet.png"))
			throw(std::string("Could not load player image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}
	try
	{
		if (!music.openFromFile(prefix + "background.wav"))
			throw(std::string("Could not load background music"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}
	try 
	{
		if (!jump.loadFromFile(prefix + "jump.wav"))
			throw(std::string("Could not load jump sound effect"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

}
void mainMenu(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage)
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

void startGame(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage, Menu menu)
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
	bool gameOver = false;
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

		if(loopCounter % 400 == 0){
			obstacleCollection.clear();
			assignObstacleType(obstacleCollection, numObstacle, screenDimensions);
		}

/*
		if (loopCounter % 400 == 0 && !autoPlay && levelIndex <= 20)//testing for a more dynamic and challenging game.
		{
			obstacleCollection.clear();
			assignObstacleType(obstacleCollection, numObstacle, screenDimensions);
		}
*/
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
				menu.displayGameOver(Window);
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
		Window.display();
		Window.clear();
	}
}

void assignObstacleType(std::vector<Obstacle*>& obstacleCollection, int numObstacle, sf::Vector2i screenDimensions)
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
		if (!squirrel.loadFromFile(filePrefixLinux + "squirrel.png"))
			throw(std::string("Could not load squirrel image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

	try 
	{
		if (!bird.loadFromFile(filePrefixLinux + "bird.png"))
			throw(std::string("Could not load bird image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}
	
	auto seed = std::chrono::system_clock::now().time_since_epoch().count(); //C++ 11 feature: use of chrono library, better than ctime. auto is also C++ 11 feature

	std::default_random_engine generator(seed); //C++ 11 feature: using generator and distribution using <random> header for random numbers
	std::uniform_int_distribution<int> distribution(0,1);
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

