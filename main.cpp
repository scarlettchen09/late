#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
//Sprite movement and jump
int main()
{
	sf::Vector2u mainWindowSize = { 800u, 600u };
	sf::RenderWindow window(sf::VideoMode(mainWindowSize.x, mainWindowSize.y), "SFML Sprite Sheet Demonstration", sf::Style::Close);
	sf::Event evnt;
	sf::View view;
	sf::Vector2f spriteSize = { 54.0f,70.0 };
	sf::Vector2f spritePosition = { 0.0f,mainWindowSize.y / 2.0f };
	bool pauseFlag = false;
	auto loopCounter = 0u;
	float xOffset;
	float yVel, xAcl, yAcl;
	yVel = xAcl = yAcl = 0.0f;

	// Set movement direction
	enum Direction { Right, Left };
	Direction direction = Right;

	// Create sprite
	sf::Texture spriteTexture;
	spriteTexture.loadFromFile("C:\\Users\\delli7desktop\\Documents\\henry\\c++29\\running-sprite_half_size.png");
	sf::IntRect locationInTexture;
	locationInTexture.height = static_cast<int>(spriteSize.y);
	locationInTexture.width = static_cast<int>(spriteSize.x);

	unsigned horizontalTextureOffset = 0;
	unsigned verticalTextureOffset = 0;
	++verticalTextureOffset %= 2;
	locationInTexture.left = horizontalTextureOffset * spriteSize.x;
	locationInTexture.top = 0;

	sf::Sprite sprite(spriteTexture);
	sprite.setPosition(spritePosition);
	sprite.setTextureRect(locationInTexture);
	sprite.setTexture(spriteTexture);

	// Music
	sf::Music music;
	music.openFromFile("C:\\Users\\delli7desktop\\Documents\\henry\\c++29\\GreenOnions.ogg");
	music.setVolume(0);
	music.play();

	view.reset(sf::FloatRect(0, 0, mainWindowSize.x, mainWindowSize.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
					window.close();
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					pauseFlag = !pauseFlag;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					direction = Left;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					direction = Right;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					spritePosition.y -= 20.0f;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					spritePosition.y += 20.0f;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (sprite.getPosition().y == mainWindowSize.y - 20)
					{
						yAcl = 1.00f;
					}
				}
				break;
			default:
				;
			}
			if (evnt.type == evnt.Closed)
			{
				window.close();
			}
		}
		if (!pauseFlag)
		{
			if (sprite.getPosition().y < mainWindowSize.y - 20)
			{
				yAcl = -0.0003f;
			}

			yVel += yAcl;
			sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - yVel);

			if (sprite.getPosition().y > mainWindowSize.y - 20)
			{
				sprite.setPosition(sprite.getPosition().x, mainWindowSize.y - 20);
			}
			loopCounter++;
			if (loopCounter % 500 == 0)
			{
				if (direction == Right)
				{
					if (spritePosition.x > mainWindowSize.x)
					{
						direction = Left;
					}
				}
				else
				{
					if (spritePosition.x < 0.0f)
					{
						direction = Right;
					}
				}
				// Set the texture offset in the sprite sheet
				if (loopCounter % 800 == 0)
				{
					horizontalTextureOffset = 0;
				}
				else
				{
					horizontalTextureOffset++;
				}
				locationInTexture.top = direction * spriteSize.y;
				locationInTexture.left = horizontalTextureOffset * spriteSize.x;
				sprite.setTextureRect(locationInTexture);
				sprite.setTexture(spriteTexture);
			}
		}
		spritePosition.x += 0.0001;
		sprite.setPosition(spritePosition.x, sprite.getPosition().y);
		view.setCenter(spritePosition);
		window.setView(view);
		window.draw(sprite);
		window.display();
		window.clear();
	}
}