#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
int main()
{
	long long int counter = 0;
	float yVel, yAcl, levelUpSpeedUp, blockLoc = 30;
	sf::RenderWindow Window;
	sf::Texture bTexture;
	sf::Sprite bImage;
	sf::Vector2i screenDimensions(800, 600);
	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	sf::RectangleShape rect(sf::Vector2f(20, 20));
	sf::Texture spriteTexture;
	sf::View view;
	sf::Event Event;

	yVel = yAcl = levelUpSpeedUp = 0.0f;

	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "My First SFML Game");
	Window.setKeyRepeatEnabled(false);

	if (!bTexture.loadFromFile("C:\\Users\\delli7desktop\\Documents\\GitHub\\late\\resources\\Background.jpg"))
	{
		std::cout << "Could not load background image" << std::endl;
	}

	bImage.setTexture(bTexture);
	bImage.setScale(9.0f, (float)screenDimensions.y / bTexture.getSize().y);
	spriteTexture.loadFromFile("C:\\Users\\delli7desktop\\Documents\\henry\\c++29\\running-sprite_half_size.png");
	rect.setTexture(&spriteTexture);
	rect.setPosition(screenDimensions.x, screenDimensions.y);
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	while (Window.isOpen())
	{
		if (counter >= 9000)
		{
			//TODO: reset the view to beginning (wrapping the image).
		}
		while (Window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:  Window.close();
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
					if (rect.getPosition().y == screenDimensions.y - blockLoc)
						yAcl = 0.9f;
				}
				break;
			}
		}

		if (rect.getPosition().y < screenDimensions.y - blockLoc)
		{
			yAcl = -0.0003f;
		}

		yVel += yAcl;
		rect.setPosition(rect.getPosition().x, rect.getPosition().y - yVel);

		if (rect.getPosition().y > screenDimensions.y - blockLoc)
		{
			rect.setPosition(rect.getPosition().x, screenDimensions.y - blockLoc);
		}

		levelUpSpeedUp += 0.000001;//testing: to speed up as level progresses.
		position.x += levelUpSpeedUp;
		rect.setPosition(position.x, rect.getPosition().y);
		view.setCenter(position);
		Window.setView(view);
		Window.draw(bImage);
		Window.draw(rect);
		Window.display();
		Window.clear();
		counter++;
	}
	return 0;
}
/*********************************
//Sprite movement test code below (comment top main() to test this)
int main()
{
	const sf::Vector2u mainWindowSize= {1024u,768u};
	sf::RenderWindow window(sf::VideoMode(mainWindowSize.x,mainWindowSize.y), "SFML Sprite Sheet Demonstration", sf::Style::Close);
	sf::Event evnt;
	bool pauseFlag = false;
	auto loopCounter = 0u;
	sf::Vector2f spriteSize= {54.0f,70.0};
	sf::Vector2f spritePosition = {0.0f,mainWindowSize.y/2.0f};
	float xOffset;

	// Set movement direction
	enum Direction {Right, Left};
	Direction direction = Right;

	// Create sprite
	sf::Texture spriteTexture;
	spriteTexture.loadFromFile("C:\\Users\\delli7desktop\\Documents\\henry\\c++29\\running-sprite_half_size.png");
	sf::IntRect locationInTexture;
	locationInTexture.height = static_cast<int>(spriteSize.y);
	locationInTexture.width = static_cast<int>(spriteSize.x);

	unsigned horizontalTextureOffset = 0;
	unsigned verticalTextureOffset = 0 ;
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
	music.setVolume(40);
	music.play();

	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				spritePosition.x = evnt.mouseButton.x;
				spritePosition.y = evnt.mouseButton.y;
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
					window.close();
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))  // pause
					pauseFlag = !pauseFlag;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					direction = Left;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					direction = Right;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					spritePosition.y -= 20.0f;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					spritePosition.y += 20.0f;
				else
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
		   loopCounter++;

			if (loopCounter%500 == 0)
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

				// Set the sprite position in the window
				//xOffset = direction == Right ? 20.0f : -20.0f;
				//spritePosition.x += xOffset;
				sprite.setPosition(spritePosition);

				// Set the texture offset in the sprite sheet
				if (loopCounter%800 == 0)
					horizontalTextureOffset = 0;
				else
					horizontalTextureOffset++;
				locationInTexture.top = direction * spriteSize.y;
				locationInTexture.left = horizontalTextureOffset * spriteSize.x;
				sprite.setTextureRect(locationInTexture);
				sprite.setTexture(spriteTexture);
			}
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
}
*******************************/
