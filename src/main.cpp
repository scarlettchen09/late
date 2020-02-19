#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "obstacle.h"
#include <iostream>
#include <string>
#include "Menu.h"

void mainMenu(sf::RenderWindow& Window, sf::Vector2i &screenDimensions);

int main()
{
Again:	int noOfImgs = 7;
	int xLocCharacter = 10;
	int animationRate = 5; //Animates once every 5 updates
	int levelIndex = 1; //For adjusting the rate in which obstacles are generated.
	int animationCtr = 0;
	int playerWidth = 108;
	int playerHeight = 140;
	float frametime = 1.0f / 60.0f; //Updates 60 times per second
	float xVel = 11.0f;
	float yVel = 0.0f;
	float yAcl = 0.0f;
	float takeOffSpeed = 22.0f;
	float landingSpeed = -1.0f;
	bool autoPlay = true;
	bool autoJmped = true;
	sf::Vector2i screenDimensions(800, 600);
	sf::RenderWindow Window;
	sf::Texture bTexture;
	sf::Texture playerTexture;
	sf::Texture squirrel;
	sf::Sprite playerSprite;
	sf::Sprite bImage;
	sf::SoundBuffer jump;
	sf::Music music;
	sf::Clock clock;
	sf::Time time;
	sf::View view;
	sf::Sound sound;
	sf::Event Event;
	sf::RectangleShape** obstacleArr;
	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	sf::IntRect playerRect(0, 0, playerWidth, playerHeight);

	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Late!");
	Window.setKeyRepeatEnabled(false);
	Window.setFramerateLimit(60);

	if (!bTexture.loadFromFile("../resources/deanzabackground.jpg"))
		std::cout << "Could not load background image" << std::endl;
	if (!playerTexture.loadFromFile("../resources/player_spritesheet.png"))
		std::cout << "Could not load player image" << std::endl;
	if (!music.openFromFile("../resources/background.wav"))
		std::cout << "Could not load background music" << std::endl;
	if (!jump.loadFromFile("../resources/jump.wav"))
		std::cout << "Could not load jump sound effect" << std::endl;
	if (!squirrel.loadFromFile("../resources/squirrel.png"))
		std::cout << "Could not load squirrel effect" << std::endl;

	Obstacle obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y - 30), sf::Vector2f(67, 50), squirrel, 20);

	sound.setBuffer(jump);
	bTexture.setSmooth(true);
	bTexture.setRepeated(true);
	bImage.setTexture(bTexture);
	bImage.setScale(1.0f, 1.0f * screenDimensions.y / bTexture.getSize().y);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(playerRect);
	playerSprite.setPosition(xLocCharacter, screenDimensions.y - playerHeight);
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	music.setLoop(true);
	music.play();
	////////////////////////////
	mainMenu(Window, screenDimensions);
	////////////////////////////
	time = clock.restart();

	while (Window.isOpen())
	{
		time += clock.restart();
		if (time.asSeconds() >= frametime) //Sets a fixed time step so game can run at a constant update time
		{
			animationCtr++;
			if (animationCtr == animationRate)
			{
				if (playerRect.left == playerWidth * noOfImgs)
					playerRect.left = 0;
				else
					playerRect.left += playerWidth;
				playerSprite.setTextureRect(playerRect);
				animationCtr = 0;
			}

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
						if (playerSprite.getPosition().y == screenDimensions.y - playerHeight)
						{
							yAcl = takeOffSpeed;
							sound.play();
						}
					}
					break;
				}
			}

			if (playerSprite.getPosition().y < screenDimensions.y - playerHeight)
			{
				yAcl = landingSpeed;
			}

			else if (playerSprite.getPosition().y > screenDimensions.y - playerHeight)
			{
				playerSprite.setPosition(playerSprite.getPosition().x, screenDimensions.y - playerHeight);
			}

			yVel += yAcl;
			playerSprite.move(xVel, -yVel);
			position.x += xVel;

			if (playerSprite.getPosition().y == screenDimensions.y - playerHeight)
			{
				yAcl = 0.0f;
				yVel = 0.0f;
			}
			time -= sf::seconds(frametime);
		}
		view.setCenter(position);
		Window.setView(view);
		Window.draw(bImage);
		Window.draw(playerSprite);
		if (autoJmped)
		{
			autoJmped = !obstacle.generateObstacle(position.x, time.asMicroseconds(), levelIndex);
		}
		for (int i = 0; i < obstacle.getCounter(); i++)
		{
			Window.draw(*(obstacle.getObstacle()[i]));
			if (obstacle.collision(playerSprite, i, autoPlay))
			{
				if ((playerSprite.getPosition().y == screenDimensions.y - playerHeight) && autoPlay)
				{
					yAcl = takeOffSpeed;
					sound.play();
					autoJmped = true;
				}
				else 
				{
					std::cout << "GAME OVER" << std::endl;
					goto Again; // replace this for game over or whatever
				}
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
	again:		Window.clear();
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
