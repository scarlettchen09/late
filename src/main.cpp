#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "obstacle.h"
#include "Menu.h"
#include "player.h"
#include "Timer.h"
#include <iostream>
#include <string>


void mainMenu(sf::RenderWindow& Window, sf::Vector2i &screenDimensions);

int main()
{
	int levelIndex = 11; //For adjusting the rate in which obstacles are generated.
	float frametime = 1.0f / 60.0f; //Updates 60 times per second
	float xVel = 3.0f;
	float takeOffSpeed = 22.0f;
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
	sf::View hudView;
	sf::Sound sound;
	sf::Event Event;
	sf::RectangleShape** obstacleArr;
	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	Timer timer;

	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Late!");
	Window.setKeyRepeatEnabled(false);
	Window.setFramerateLimit(60);

	if (!bTexture.loadFromFile("../resources/Backgrounds/bg2.jpg"))
		std::cout << "Could not load background image" << std::endl;
	if (!playerTexture.loadFromFile("../resources/player_spritesheet.png"))
		std::cout << "Could not load player image" << std::endl;
	if (!music.openFromFile("../resources/background.wav"))
		std::cout << "Could not load background music" << std::endl;
	if (!jump.loadFromFile("../resources/jump.wav"))
		std::cout << "Could not load jump sound effect" << std::endl;
	if (!squirrel.loadFromFile("../resources/squirrel.png"))
		std::cout << "Could not load squirrel effect" << std::endl;

	//Obstacle obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y - 30), sf::Vector2f(67, 50), squirrel, 20);

	Player player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);
	player.setXvelocity(xVel);
	player.setJumpHeight(takeOffSpeed);


	sound.setBuffer(jump);
	bTexture.setSmooth(true);
	bTexture.setRepeated(true);
	bImage.setTexture(bTexture);
	bImage.setScale(1.0f, 1.0f * screenDimensions.y / bTexture.getSize().y);
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	music.setLoop(true);
	music.play();
	timer.startTimer();
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
				}
			}
			position.x += xVel;
			player.update();
			time -= sf::seconds(frametime);
		}
		timer.update();
		view.setCenter(position);

		Window.setView(view);
		Window.draw(bImage);
		Window.draw(player.getSprite());

		Window.setView(hudView);
		Window.draw(timer.getText());
		//obstacle.generateObstacle(position.x, time.asMicroseconds(), levelIndex);
		/*for (int i = 0; i < obstacle.getCounter(); i++)
		{
			Window.draw(*(obstacle.getObstacle()[i]));
			if (obstacle.collision(player.getSprite(), i))
				Window.close();
		}*/
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
