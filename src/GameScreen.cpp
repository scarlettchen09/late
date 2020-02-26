#include "GameScreen.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "player.h"
#include "Timer.h"
#include "obstacle.h"

GameScreen::GameScreen(sf::Vector2i& screenDimensions){
	levelIndex = 11; //For adjusting the rate in which obstacles are generated.
	frametime = 1.0f / 60.0f; //Updates 60 times per second
	xVel = 3.0f;
	takeOffSpeed = 22.0f;
	autoPlay = true;
	autoJmped = true;

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

	position.x = screenDimensions.x / 2;
	position.y = screenDimensions.y / 2;
	//(player.getSprite()).setTexture(playerTexture);



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

	time = clock.restart();

	//player = new Player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);

	//player->setXvelocity(xVel);
	//player->setJumpHeight(takeOffSpeed);
	
	//Obstacle obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y - 30), sf::Vector2f(67, 50), squirrel, 20);
	
}

int GameScreen::Run(sf::RenderWindow &Window, sf::Vector2i& screenDimensions){

	Player player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);
	player.setXvelocity(xVel);
	player.setJumpHeight(takeOffSpeed);

	bool running = true;
	while(running){
		time += clock.restart();
		if (time.asSeconds() >= frametime) //Sets a fixed time step so game can run at a constant update time
		{
			while (Window.pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed:
					Window.close();
					return -1;
					break;
				case sf::Event::KeyPressed:
					if (Event.key.code == sf::Keyboard::Escape)
					{
                        return 0;
						//Window.close();
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
	
}