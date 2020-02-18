#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "obstacle.h"
#include <iostream>
#include <string>

bool collision(sf::Sprite player, sf::RectangleShape obstacle);


int main()
{
	sf::Vector2i screenDimensions(800, 600);

	sf::RenderWindow Window;
	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Late!");
	Window.setKeyRepeatEnabled(false);
	Window.setFramerateLimit(60);
	
	sf::Texture bTexture;
	sf::Texture playerTexture;
	sf::Texture squirrel;
	sf::Sprite playerSprite;
	sf::Sprite bImage;
	sf::SoundBuffer jump;
	sf::Music music;
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
	sf::Sound sound;
	sound.setBuffer(jump);

	bTexture.setSmooth(true);
	bTexture.setRepeated(true);
	bImage.setTexture(bTexture);
	bImage.setScale(1.0f, 1.0f * screenDimensions.y / bTexture.getSize().y);

	playerSprite.setTexture(playerTexture);
	int playerWidth = 108;
	int playerHeight = 140;
	sf::IntRect playerRect(0, 0, playerWidth, playerHeight);
	playerSprite.setTextureRect(playerRect);

	playerSprite.setPosition(80, screenDimensions.y - playerHeight);
	sf::Clock clock;
	sf::Time time;
	float frametime = 1.0f / 60.0f; //Updates 60 times per second
	int animationRate = 5; //Animates once every 5 updates
	int animationCtr = 0;

	float xVel = 5.0f;
	float yVel = 0.0f;

	float xAcl = 0.0f;
	float yAcl = 0.0f;

	sf::View view;

	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	music.setLoop(true);
	music.play();

	Obstacle obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y - 30), sf::Vector2f(67, 50), squirrel, 20);
	sf::RectangleShape** obstacleArr;
	while (Window.isOpen())
	{
		time += clock.restart();
		sf::Event Event;
		if (time.asSeconds() >= frametime) //Sets a fixed time step so game can run at a constant update time
		{
			animationCtr++;
			if(animationCtr == animationRate){
				if(playerRect.left == playerWidth * 7)
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
							yAcl = 15.0f;
							sound.play();
						}
					}

					break;
				}
			}

			if (playerSprite.getPosition().y < screenDimensions.y - playerHeight)
			{
				yAcl = -0.4f;
			}

			yVel += yAcl;

			playerSprite.move(xVel, -yVel);
			if (playerSprite.getPosition().y > screenDimensions.y - playerHeight)
			{
				playerSprite.setPosition(playerSprite.getPosition().x, screenDimensions.y - playerHeight);
			}
			if (playerSprite.getPosition().y == screenDimensions.y - playerHeight && (yAcl != 0.0f && yVel != 0.0f))
			{
				yAcl = 0.0f;
				yVel = 0.0f;
			}

			position.x += xVel;
			
			time -= sf::seconds(frametime);
		}
		

		view.setCenter(position);
		Window.setView(view);

		Window.draw(bImage);
		Window.draw(playerSprite);

		obstacle.generateObstacle(position.x, time.asMicroseconds());
		obstacleArr = obstacle.getObstacle();
		for (int i = 0; i < obstacle.getCounter(); i++)
		{
			Window.draw(*(obstacleArr[i]));
			if (collision(playerSprite, *(obstacleArr[i])))
			{
				std::cout << "GAME OVER" << std::endl;
				Window.close(); // replace this for game over or whatever
			}
				
			
		}
		Window.display();
		Window.clear();
	}

	return 0;
}

bool collision(sf::Sprite player, sf::RectangleShape obstacle)
{
	double playerX1 = player.getPosition().x;
	double playerX2 = player.getPosition().x + 108;
	double playerY2 = player.getPosition().y + 140;
	double obstacleX1 = obstacle.getPosition().x;
	double obstacleY1 = obstacle.getPosition().y;
	double obstacleX2 = obstacle.getPosition().x + 67;
	if ( ( (playerX1 <= obstacleX1 && obstacleX1 <= playerX2) || (playerX1 <= obstacleX2 && obstacleX2 <= playerX2) ) && playerY2 >= obstacleY1)
	{
		return true;
	}
		
	return false;
}