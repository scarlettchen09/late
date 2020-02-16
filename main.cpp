#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
//Sprite movements and jumps
int main()
{
	sf::Vector2u mainWindowSize = { 1024, 768 };
	sf::RenderWindow window(sf::VideoMode(mainWindowSize.x, mainWindowSize.y), "Late!", sf::Style::Close);
	sf::Event evnt;
	sf::View view;
	sf::Vector2f spriteSize = { 54.0f, 70.0f };
	sf::Vector2f spritePosition = { 0, 480 };
	sf::Texture spriteTexture, bTexture;
	unsigned horizontalTextureOffset = 0;
	bool pauseFlag = false;
	int loopCounter = 0;
	float yVel, xAcl, yAcl;

	yVel = xAcl = yAcl = 0.0f;

	window.setKeyRepeatEnabled(false);

	if (!spriteTexture.loadFromFile("C:\\Users\\delli7desktop\\Documents\\henry\\c++29\\running-sprite\\half_size.png"))
	{
		std::cout << "Could not load sprite image" << std::endl;
	}

	if (!bTexture.loadFromFile("C:\\Users\\delli7desktop\\Documents\\GitHub\\late\\resources\\Background.jpg"))
	{
		std::cout << "Could not load background image" << std::endl;
	}

	sf::IntRect locationInTexture;
	locationInTexture.height = static_cast<int>(spriteSize.y);
	locationInTexture.width = static_cast<int>(spriteSize.x);

	sf::Sprite sprite(spriteTexture), bImage;
	sprite.setPosition(spritePosition);
	sprite.setTextureRect(locationInTexture);

	bImage.setTexture(bTexture);
	bImage.setScale(5.0f, (float)mainWindowSize.y / bTexture.getSize().y);
	bImage.setPosition(0, 80);
	// Music
	sf::Music music;
	music.openFromFile("C:\\Users\\delli7desktop\\Documents\\henry\\c++29\\GreenOnions.ogg");
	music.play();

	view.reset(sf::FloatRect(0, 0, mainWindowSize.x, mainWindowSize.y));
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
				if (loopCounter % 800 == 0)
				{
					horizontalTextureOffset = 0;
				}
				else
				{
					horizontalTextureOffset++;
				}
				locationInTexture.left = horizontalTextureOffset * spriteSize.x;
				sprite.setTextureRect(locationInTexture);
				sprite.setTexture(spriteTexture);
			}
		}
		spritePosition.x += 0.1;
		sprite.setPosition(spritePosition.x, sprite.getPosition().y);
		view.setCenter(spritePosition);
		window.setView(view);
		window.draw(bImage);
		window.draw(sprite);
		window.display();
		window.clear();
	}
}