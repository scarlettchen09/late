#include "GameShell.h"
#include "Menu.h"
void GameShell::startGame(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>& bImage, Menu menu)
{
	sf::Event Event;
	sf::View hudView; //hudView (for Score) initialized with default pos values: top left corner of window screen
	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	sf::Clock clock;
	sf::Time time;
	std::vector<sf::Sprite*> generatedBackground;
	auto loopCounter = 0u;
	int levelIndex = 20; //For adjusting the rate in which obstacles are generated. range should be 50 to 10 (low to high difficulty).
	float frametime = 1.0f / 60.0f; //Updates 60 times per second
	bool autoPlay = true;
	const int numObstacle = 100;
	double currentSpeed = 1;
	double speedLim = 2.8;

	std::string lose = "------Game Over.------\n\n\n\nYou failed to get \nto class on time.\n\n\nPress Escape to exit.\n\nOr backspace \nto return to main menu.";
	std::string win = "-------You Win.-------\n\n\n\nYou got into class\n... just on time.\n\n\nPress Escape to exit.\n\nOr backspace \nto return to main menu.";
	std::vector<Obstacle*> obstacleCollection; //STL Container: vector
	Score score;
	Player player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);

	player.setXvelocity(11.0f);
	player.setJumpHeight(22.0f);
	player.speedUp(currentSpeed);
	assignObstacleType(obstacleCollection, numObstacle, screenDimensions, bImage, generatedBackground);

	time = clock.restart();
	score.startScore();

	while (Window.isOpen())
	{
		
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
					menu.mainMenu(Window, screenDimensions, sound, view, playerTexture, bImage);
				}
				break;
			default://to avoid program crash when unknown inputs are encountered
				break;
			}
		}
		/*if (loopCounter % 400 == 0)
		{
			obstacleCollection.clear();
			assignObstacleType(obstacleCollection, numObstacle, screenDimensions);
		}*/
		position.x += player.getXvelocity();
		/*if (loopCounter % 400 == 0)
		{
			position.x = screenDimensions.x / 2;
			player.resetPlayerPos();
			player.getSprite().setPosition(player.getPosition());
		}*/
		if (currentSpeed < speedLim)
		{
			currentSpeed = 1 + score.getScore() / 100;
			player.setYacceleration(1.0f);
			player.setXvelocity(11.0f);
			player.setJumpHeight(22.0f);
			player.speedUp(currentSpeed);
		}
		view.setCenter(position);
		Window.setView(view);
		player.update();
		for (auto background : generatedBackground)
		{
			Window.draw(*background);
		}
		Window.draw(player.getSprite());
		time -= sf::seconds(frametime);

		for (auto obs : obstacleCollection) //C++ 11 Feature: range based for loop and auto
		{
			Window.draw(obs->getObstacle());

			if (player.getHitbox().intersects(obs->getHitbox()))
			{
				player.resetWindowView(position, screenDimensions, view, Window);
				menu.displayGameOver(Window, screenDimensions, sound, view, playerTexture, bImage, lose);
			}
			if (autoPlay && player.getCushion().intersects(obs->getHitbox()))
			{
				player.jump();
				sound.play();
			}
		}


		if (obstacleCollection[obstacleCollection.size() - 1]->getObstacle().getPosition().x +
			obstacleCollection[obstacleCollection.size() - 1]->getDim().x <= position.x - 2 * screenDimensions.x)
		{
			player.resetWindowView(position, screenDimensions, view, Window);
			menu.displayGameOver(Window, screenDimensions, sound, view, playerTexture, bImage, win);
		}

		score.update();
		Window.setView(hudView);
		Window.draw(score.getText());
		Window.draw(score.getLabel());
		Window.display();
		Window.clear();
	}



	for (auto obs : obstacleCollection)
	{
		delete obs;
	}
	for (auto background : generatedBackground)
	{
		delete background;
	}
}

void GameShell::assignObstacleType(std::vector<Obstacle*>& obstacleCollection, int numObstacle, sf::Vector2i screenDimensions, std::vector<sf::Sprite*>& bImage, std::vector<sf::Sprite*>& generatedBackground)
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

	try
	{
		if (!squirrel.loadFromFile(filePrefixLinux + "squirrel.png"))
			throw(std::string("Could not load squirrel image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

	try
	{
		if (!bird.loadFromFile(filePrefixLinux + "bird.png"))
			throw(std::string("Could not load bird image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

	auto seed = std::chrono::system_clock::now().time_since_epoch().count(); //C++ 11 feature: use of chrono library, better than ctime. auto is also C++ 11 feature

	std::default_random_engine generator(seed); //C++ 11 feature: using generator and distribution using <random> header for random numbers
	std::uniform_int_distribution<int> distribution(0, 1);
	//makeRandomObstacles(obstacleCollection, numObstacle ,screenDimensions, squirrelDimX, squirrelDimY, birdDimX, birdDimY, squirrel, bird, generator, distribution);
	int randObstacleType;

	for (int i = 0; i < numObstacle; i++)
	{
		//int randObstacleType = distribution(generator);
		switch (randObstacleType = distribution(generator); randObstacleType) //C++ 17 feature: initializing expression inside a switch statement
		{
		case 0:
		{
			obstacleCollection.push_back(new Obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(squirrelDimX, squirrelDimY), squirrel, sf::IntRect(30, 0, squirrelDimX, squirrelDimY)));
			break;
		}
		case 1:
		{
			obstacleCollection.push_back(new AirObstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(birdDimX, birdDimY), bird, sf::IntRect(20, 0, birdDimX, birdDimY)));
			break;
		}
		}
	}
	for (int i = 0; i < numObstacle; i++)
	{
		obstacleCollection[i]->generateObstacle(screenDimensions.x * (i + 1));
	}

	int screenLim = obstacleCollection[obstacleCollection.size() - 1]->getObstacle().getPosition().x + obstacleCollection[obstacleCollection.size() - 1]->getDim().x;
	int currentBackgroundSize = 0;
	auto it = bImage.cbegin();
	while (currentBackgroundSize < screenLim)
	{
		it++;
		if (it == bImage.cend())
		{
			it = bImage.cbegin();
		}	

		sf::Sprite* temp = new sf::Sprite(**it);
		temp->setPosition(currentBackgroundSize, 0);
		
		generatedBackground.push_back(temp);
		currentBackgroundSize += temp->getTexture()->getSize().x;
	}
}