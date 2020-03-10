#include "GameShell.h"
#include "Menu.h"
void GameShell::startGame(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage, Menu menu)
{
	sf::Event Event;
	sf::View hudView; //hudView (for Score) initialized with default pos values: top left corner of window screen
	sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);
	sf::Clock clock;
	sf::Time time;
	auto loopCounter = 0u;
	int levelIndex = 20; //For adjusting the rate in which obstacles are generated. range should be 50 to 10 (low to high difficulty).
	float frametime = 1.0f / 60.0f; //Updates 60 times per second
	bool autoPlay = true;
	const int numObstacle = 100;

	std::vector<Obstacle*> obstacleCollection; //STL Container: vector
	Score score;
	Player player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);

	player.setXvelocity(11.0f);
	player.setJumpHeight(22.0f);
	player.speedUp(2.0f);
	assignObstacleType(obstacleCollection, numObstacle, screenDimensions);

	time = clock.restart();
	score.startScore();

	while (Window.isOpen())
	{
		if (loopCounter % 400 == 0)
		{
			obstacleCollection.clear();
			assignObstacleType(obstacleCollection, numObstacle, screenDimensions);
		}
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
		position.x += player.getXvelocity();
		if (loopCounter % 400 == 0)
		{
			position.x = screenDimensions.x / 2;
			player.resetPlayerPos();
			player.getSprite().setPosition(player.getPosition());
		}
		view.setCenter(position);
		Window.setView(view);
		player.update();
		Window.draw(bImage);
		Window.draw(player.getSprite());
		time -= sf::seconds(frametime);

		for (auto obs : obstacleCollection) //C++ 11 Feature: range based for loop and auto
		{
			Window.draw(obs->getObstacle());

			if (player.getHitbox().intersects(obs->getHitbox()))
			{
				player.resetWindowView(position, screenDimensions, view, Window);
				menu.displayGameOver(Window, screenDimensions, sound, view, playerTexture, bImage);
			}
			if (autoPlay && player.getCushion().intersects(obs->getHitbox()))
			{
				player.jump();
				sound.play();
			}
		}

		score.update();
		Window.setView(hudView);
		Window.draw(score.getText());
		Window.draw(score.getLabel());
		Window.display();
		Window.clear();
	}
}

void GameShell::assignObstacleType(std::vector<Obstacle*>& obstacleCollection, int numObstacle, sf::Vector2i screenDimensions)
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
		if (!squirrel.loadFromFile(filePrefixH + "squirrel.png"))
			throw(std::string("Could not load squirrel image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

	try
	{
		if (!bird.loadFromFile(filePrefixH + "bird.png"))
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
}