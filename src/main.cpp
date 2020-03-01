#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "obstacle.h"
#include "Menu.h"
#include "player.h"
#include "airObstacle.h"
#include <iostream>
#include <string>"

void mainMenu(sf::RenderWindow& Window, sf::Vector2i &screenDimensions);
void generateObstacle(Obstacle* arr[], int numObstacle);


int main()
{
Again:
	int levelIndex = 1; //For adjusting the rate in which obstacles are generated. range should be 50 ~> 10 from low to high difficulty.
	float frametime = 1.0f / 60.0f; //Updates 60 times per second
	bool autoPlay = true;
	sf::Vector2i screenDimensions(800, 600);
	sf::Event Event;
	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	sf::RenderWindow Window;
	sf::Texture bTexture;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Sprite bImage;
	sf::SoundBuffer jump;
	sf::Music music;
	sf::Clock clock;
	sf::Time time;
	sf::View view;
	sf::Sound sound;

	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Late!");
	Window.setKeyRepeatEnabled(false);
	Window.setFramerateLimit(60);

	//if (!bTexture.loadFromFile("C://Users//delli7desktop//Documents//GitHub//late//resources//deanzabackground.jpg"))
		if (!bTexture.loadFromFile("../resources/deanzabackground.jpg"))
			std::cout << "Could not load background image" << std::endl;
	//if (!playerTexture.loadFromFile("C://Users//delli7desktop//Documents//GitHub//late//resources//player_spritesheet.png"))
		if (!playerTexture.loadFromFile("../resources/player_spritesheet.png"))
			std::cout << "Could not load player image" << std::endl;
	//if (!music.openFromFile("C://Users//delli7desktop//Documents//GitHub//late//resources//background.wav"))
		if (!music.openFromFile("../resources/background.wav"))
			std::cout << "Could not load background music" << std::endl;
	//if (!jump.loadFromFile("C://Users//delli7desktop//Documents//GitHub//late//resources//jump.wav"))
		if (!jump.loadFromFile("../resources/jump.wav"))
			std::cout << "Could not load jump sound effect" << std::endl;

	const int numObstacle = 30;
	Obstacle* arr[numObstacle];
	generateObstacle(arr, numObstacle);

	Player player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);
	player.setXvelocity(11.0f);
	player.setJumpHeight(22.0f);
	player.speedUp(2.0f);

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
mainMenu:
	mainMenu(Window, screenDimensions);
	////////////////////////////
	time = clock.restart();

	while (Window.isOpen())
	{
		time += clock.restart();
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
					if (Event.key.code == sf::Keyboard::Escape)
					{
						Window.close();
					}
					if (Event.key.code == sf::Keyboard::Space)
					{
						if (player.jump())
						{
							sound.play();
						}
					}
					break;
				default://to aovid program crash when unknown inputs are encountered
					break;
				}
			}
			position.x += player.getXvelocity();
			player.update();
			time -= sf::seconds(frametime);
		}
		view.setCenter(position);
		Window.setView(view);
		Window.draw(bImage);
		Window.draw(player.getSprite());

		for (int i = 0; i < numObstacle; i++)
		{
			Window.draw(arr[i]->getObstacle());

			if (player.getHitbox().intersects(arr[i]->getHitbox()))
			{
				Window.close();
			}

			if (autoPlay && player.getCushion().intersects(arr[i]->getHitbox()))
			{
				player.jump();
				sound.play();
			}
		}
		
		Window.display();
		Window.clear();
	}
	return 0;
}

void mainMenu(sf::RenderWindow& Window, sf::Vector2i& screenDimensions)
{
	sf::Texture menuBackground;
	sf::Sprite menuBack;
	if (!menuBackground.loadFromFile("../resources/wakeup.png"))
		std::cout << "Could not load background image" << std::endl;
	menuBack.setTexture(menuBackground);
	menuBack.setScale(screenDimensions.x / menuBack.getLocalBounds().width, screenDimensions.y / menuBack.getLocalBounds().height);

	Menu menu(Window.getSize().x, Window.getSize().y);

	while (Window.isOpen())
	{
		sf::Event event;
		again:		
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
						return;
						break;

					case 1:
						std::cout << "Option button has been pressed" << std::endl;
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
									case sf::Keyboard::Backspace: goto again;
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

void generateObstacle(Obstacle* arr[], int numObstacle)
{
	sf::Texture squirrel;
	sf::Texture bird;
	if (!squirrel.loadFromFile("../resources/squirrel.png"))
		std::cout << "Could not load squirrel effect" << std::endl;
	if (!bird.loadFromFile("../resources/bird.png"))
		std::cout << "Could not load bird effect" << std::endl;

	for (int i = 0; i < numObstacle; i++)
	{
		srand(time(0) * rand());
		switch (rand() % 2)
		{
		case 0:
		{
			arr[i] = new Obstacle(sf::Vector2i(800, 600 - 30), sf::Vector2f(67, 50), squirrel, sf::IntRect(30, 0, 67, 50));
			break;
		}
		case 1:
		{
			arr[i] = new AirObstacle(sf::Vector2i(800, 600 - 30), sf::Vector2f(51, 40), bird, sf::IntRect(30, 0, 41, 40));
			break;
		}
		}
	}
	for (int i = 0; i < numObstacle; i++)
	{
		arr[i]->generateObstacle(800 * (i + 1));
	}
}

