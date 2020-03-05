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
#include <vector>

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

	if (!bTexture.loadFromFile(filePrefixLinux + "deanzabackground.jpg"))
		std::cout << "Could not load background image" << std::endl;
	if (!playerTexture.loadFromFile(filePrefixLinux + "player_spritesheet.png"))
		std::cout << "Could not load player image" << std::endl;
	if (!music.openFromFile(filePrefixLinux + "background.wav"))
		std::cout << "Could not load background music" << std::endl;
	if (!jump.loadFromFile(filePrefixLinux + "jump.wav"))
		std::cout << "Could not load jump sound effect" << std::endl;

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

void mainMenu(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage)
{
	Menu menu(Window.getSize().x, Window.getSize().y);
	sf::Event event;
	while (Window.isOpen())
	{
		Window.clear();
		menu.dispBackground(Window);
		menu.draw(Window);
		Window.display();

		while (Window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
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
							menu.dispBackground(Window);
							menu.optionDraw(Window);
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
	const int numObstacle = 100;
	//Obstacle* arr[numObstacle];
	std::vector<Obstacle*> obstacleCollection;
	Score Score(30);
	Player player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);

	player.setXvelocity(11.0f);
	player.setJumpHeight(22.0f);
	player.speedUp(2.0f);
	assignObstacleType(obstacleCollection, numObstacle, screenDimensions);
	//assignObstacleType(arr, numObstacle, screenDimensions);
	time = clock.restart();
	Score.startScore();

	while (Window.isOpen())
	{
		if (loopCounter % 150 == 0 && !autoPlay && levelIndex <= 20)//testing for a more dynamic and challenging game.
		{
			assignObstacleType(obstacleCollection, numObstacle, screenDimensions);
			//assignObstacleType(arr, numObstacle, screenDimensions);
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
			default://to aovid program crash when unknown inputs are encountered
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

		for (int i = 0; i < numObstacle; i++)
		{
			Window.draw(obstacleCollection[i]->getObstacle());

			if (player.getHitbox().intersects(obstacleCollection[i]->getHitbox()))
			{
				player.resetWindowView(position, screenDimensions, view, Window);
				//mainMenu(Window, screenDimensions, sound, view, playerTexture, bImage);
				menu.dispGameover(Window);
			}
			if (autoPlay && player.getCushion().intersects(obstacleCollection[i]->getHitbox()))
			{
				player.jump();
				sound.play();
			}
		}
		Score.update();
		Window.setView(hudView);
		Window.draw(Score.getText());
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
	if (!squirrel.loadFromFile(filePrefixLinux + "squirrel.png"))
		std::cout << "Could not load squirrel effect" << std::endl;
	if (!bird.loadFromFile(filePrefixLinux + "bird.png"))
		std::cout << "Could not load bird effect" << std::endl;
	srand(time(0) * rand());
	for (int i = 0; i < numObstacle; i++)
	{
		switch (rand() % 2)
		{
			case 0:
			{
				obstacleCollection.push_back(new Obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(squirrelDimX, squirrelDimY), squirrel, sf::IntRect(30, 0, squirrelDimX, squirrelDimY)));
				//obstacleCollection[i] = new Obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(squirrelDimX, squirrelDimY), squirrel, sf::IntRect(30, 0, squirrelDimX, squirrelDimY));
				break;
			}
			case 1:
			{
				obstacleCollection.push_back(new AirObstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(birdDimX, birdDimY), bird, sf::IntRect(20, 0, birdDimX, birdDimY)));
				//obstacleCollection[i] = new AirObstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(birdDimX, birdDimY), bird, sf::IntRect(20, 0, birdDimX, birdDimY));
				break;
			}
		}
	}
	for (int i = 0; i < numObstacle; i++)
	{
		obstacleCollection[i]->generateObstacle(screenDimensions.x * (i + 1));
	}
}