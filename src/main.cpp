#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "obstacle.h"
#include "Menu.h"
#include "Timer.h"
#include "player.h"
#include "airObstacle.h"
#include <iostream>
#include <string>"
void mainMenu(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound,
	sf::View view, sf::Texture playerTexture, sf::Sprite bImage);
void assignObstacleType(Obstacle* arr[], int numObstacle, sf::Vector2i screenDimensions);
void startGame(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound,
	sf::View view, sf::Texture playerTexture, sf::Sprite bImage);

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

	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Late!");
	Window.setKeyRepeatEnabled(false);
	Window.setFramerateLimit(60);

	if (!bTexture.loadFromFile("C://Users//delli7desktop//Documents//GitHub//late//late//resources//deanzabackground.jpg"))
		//if (!bTexture.loadFromFile("../resources/deanzabackground.jpg"))
		std::cout << "Could not load background image" << std::endl;
	if (!playerTexture.loadFromFile("C://Users//delli7desktop//Documents//GitHub//late//late//resources//player_spritesheet.png"))
		//if (!playerTexture.loadFromFile("../resources/player_spritesheet.png"))
		std::cout << "Could not load player image" << std::endl;
	if (!music.openFromFile("C://Users//delli7desktop//Documents//GitHub//late//late//resources//background.wav"))
		//if (!music.openFromFile("../resources/background.wav"))
		std::cout << "Could not load background music" << std::endl;
	if (!jump.loadFromFile("C://Users//delli7desktop//Documents//GitHub//late//late//resources//jump.wav"))
		//if (!jump.loadFromFile("../resources/jump.wav"))
		std::cout << "Could not load jump sound effect" << std::endl;

	sound.setBuffer(jump);
	bTexture.setSmooth(true);
	bTexture.setRepeated(true);
	bImage.setTexture(bTexture);
	bImage.setScale(1.0f, 1.0f * screenDimensions.y / bTexture.getSize().y);
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	music.setLoop(true);
	music.play();

	////////////////////////////
	mainMenu(Window, screenDimensions, sound, view, playerTexture, bImage);
	////////////////////////////
	return 0;
}

void mainMenu(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage)
{
	sf::Texture menuBackground;
	sf::Sprite menuBack;
	if (!menuBackground.loadFromFile("C://Users//delli7desktop//Documents//GitHub//late//late//resources//wakeup.png"))
		std::cout << "Could not load background image" << std::endl;
	menuBack.setTexture(menuBackground);
	menuBack.setScale(screenDimensions.x / menuBack.getLocalBounds().width, screenDimensions.y / menuBack.getLocalBounds().height);
	Menu menu(Window.getSize().x, Window.getSize().y);
	while (Window.isOpen())
	{
		sf::Event event;
		Window.clear();
		Window.draw(menuBack);
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
						startGame(Window, screenDimensions, sound, view, playerTexture, bImage);
						break;

					case 1:
						std::cout << "Help button has been pressed" << std::endl;
						while (Window.isOpen())
						{
							Window.clear();
							Window.draw(menuBack);
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

void startGame(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage)
{
	sf::Event Event;
	sf::View hudView; //hudView (for timer) initialized with default pos values: top left corner of window screen
	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	sf::Clock clock;
	sf::Time time;

	Timer timer(30);
	auto loopCounter = 0u;
	int levelIndex = 20; //For adjusting the rate in which obstacles are generated. range should be 50 to 10 (low to high difficulty).
	float frametime = 1.0f / 60.0f; //Updates 60 times per second
	bool autoPlay = true;

	Player player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);
	player.setXvelocity(11.0f);
	player.setJumpHeight(22.0f);
	player.speedUp(2.0f);

	const int numObstacle = 100;
	Obstacle* arr[numObstacle];
	assignObstacleType(arr, numObstacle, screenDimensions);

	time = clock.restart();
	timer.startTimer();
	while (Window.isOpen())
	{
		if (loopCounter % 150 == 0 && !autoPlay && levelIndex <= 20)//testing for a more dynamic and challenging game.
		{
			assignObstacleType(arr, numObstacle, screenDimensions);
		}
		time += clock.restart();
		loopCounter++;
		if (time.asSeconds() >= frametime) //Sets a fixed time step so game can run at a constant update time
		{
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
						Window.clear();
						position.x = screenDimensions.x / 2;
						position.y = screenDimensions.y / 2;
						view.setCenter(position);
						Window.setView(view);
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
				player.getSprite().setPosition(player.getPosition());
			}
			view.setCenter(position);
			Window.setView(view);
			player.update();
			time -= sf::seconds(frametime);
		}

		Window.draw(bImage);
		Window.draw(player.getSprite());
		for (int i = 0; i < numObstacle; i++)
		{
			Window.draw(arr[i]->getObstacle());

			if (player.getHitbox().intersects(arr[i]->getHitbox()))
			{
				Window.clear();
				position.x = screenDimensions.x / 2;
				position.y = screenDimensions.y / 2;
				view.setCenter(position);
				Window.setView(view);
				mainMenu(Window, screenDimensions, sound, view, playerTexture, bImage);
				//Window.close();
			}

			if (autoPlay && player.getCushion().intersects(arr[i]->getHitbox()))
			{
				player.jump();
				sound.play();
			}
		}
		timer.update();
		Window.setView(hudView);
		Window.draw(timer.getText());
		Window.display();
		Window.clear();
	}
}

void assignObstacleType(Obstacle* arr[], int numObstacle, sf::Vector2i screenDimensions)
{
	int squirrelDimX, squirrelDimY, birdDimX, birdDimY;
	sf::Texture squirrel;
	sf::Texture bird;

	squirrelDimX = 67;
	squirrelDimY = 50;
	birdDimX = 51;
	birdDimY = 40;
	if (!squirrel.loadFromFile("C://Users//delli7desktop//Documents//GitHub//late//late//resources//squirrel.png"))
		std::cout << "Could not load squirrel effect" << std::endl;
	if (!bird.loadFromFile("C://Users//delli7desktop//Documents//GitHub//late//late//resources//bird.png"))
		std::cout << "Could not load bird effect" << std::endl;
	srand(time(0) * rand());
	for (int i = 0; i < numObstacle; i++)
	{
		switch (rand() % 2)
		{
			case 0:
			{
				arr[i] = new Obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(squirrelDimX, squirrelDimY), squirrel, sf::IntRect(30, 0, squirrelDimX, squirrelDimY));
				break;
			}
			case 1:
			{
				arr[i] = new AirObstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(birdDimX, birdDimY), bird, sf::IntRect(20, 0, birdDimX, birdDimY));
				break;
			}
		}
	}
	for (int i = 0; i < numObstacle; i++)
	{
		arr[i]->generateObstacle(screenDimensions.x * (i + 1));
	}
}