#include "GameShell.h"
#include "Menu.h"
void GameShell::startGame(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound[], sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>& bImage, Menu menu)
{
	sf::Event Event;
	sf::View hudView; //hudView (for Score) initialized with default pos values: top left corner of window screen
	sf::Vector2f position(static_cast<float>(screenDimensions.x) / 2, static_cast<float>(screenDimensions.y) / 2);
	sf::Clock clock;
	sf::Time time;
	std::vector<sf::Sprite*> generatedBackground;
	auto loopCounter = 0u;
	float frametime = 1.0f / 60.0f; //Updates 60 times per second
	bool autoPlay = true;
	const int numObstacle = 100;
	double currentSpeed = 1;
	double speedLim = 3;
	double velHoldFromMax = 0;
	bool initializeMaxFlag = true;

	std::string lose = "------Game Over.------\n\n\nYou failed to get \nto class on time.\n\n\nPress Escape to exit.\n\nOr backspace \nto return to main menu.\nYour final score:";
	std::string win = "-------You Win.-------\n\n\nYou got into class\n... just on time.\n\n\nPress Escape to exit.\n\nOr backspace \nto return to main menu.\nYour final score:";
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
			case sf::Event::MouseButtonPressed:
			case sf::Event::KeyPressed:
				if (Event.key.code == sf::Keyboard::Space || sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					if (player.jump())
					{
						sound[0].play();
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
		position.x += static_cast<float>(player.getXvelocity());

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
				sound[1].play();
				menu.displayGameOver(Window, screenDimensions, sound, view, playerTexture, bImage, lose, score);
			}
			if (autoPlay && player.getCushion().intersects(obs->getHitbox()))
			{
				player.jump();
				sound[0].play();
			}
		}
		if (obstacleCollection[obstacleCollection.size() - 1]->getObstacle().getPosition().x +
			obstacleCollection[obstacleCollection.size() - 1]->getDim().x <= position.x - 2 * screenDimensions.x)
		{
			player.speedDown(0.1);
			view.setCenter(position);
			Window.setView(view);
			player.update();
			if (initializeMaxFlag)
			{
				velHoldFromMax = player.getXvelocity() * 1.05;
				initializeMaxFlag = false;
			}
			if (player.getXvelocity() >= velHoldFromMax)
			{
				player.resetWindowView(position, screenDimensions, view, Window);
				menu.displayGameOver(Window, screenDimensions, sound, view, playerTexture, bImage, win, score);
			}
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
	float squirrelDimX, squirrelDimY, birdDimX, birdDimY;
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

	std::default_random_engine generator(static_cast<unsigned int>(seed)); //C++ 11 feature: using generator and distribution using <random> header for random numbers
	std::uniform_int_distribution<int> distribution(0, 1);
	int randObstacleType;

	for (int i = 0; i < numObstacle; i++)
	{
		switch (randObstacleType = distribution(generator); randObstacleType) //C++ 17 feature: initializing expression inside a switch statement
		{
		case 0:
		{
			obstacleCollection.push_back(new Obstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(squirrelDimX, squirrelDimY), squirrel, sf::IntRect(30, 0, static_cast<int>(squirrelDimX), static_cast<int>(squirrelDimY))));
			break;
		}
		case 1:
		{
			obstacleCollection.push_back(new AirObstacle(sf::Vector2i(screenDimensions.x, screenDimensions.y), sf::Vector2f(birdDimX, birdDimY), bird, sf::IntRect(20, 0, static_cast<int>(birdDimX - 20), static_cast<int>(birdDimY))));
			break;
		}
		}
	}
	for (int i = 0; i < numObstacle; i++)
	{
		obstacleCollection[i]->generateObstacle(static_cast<double>(screenDimensions.x) * (static_cast<double>(i) + 1));
	}

	float screenLim = obstacleCollection[obstacleCollection.size() - 1]->getObstacle().getPosition().x + obstacleCollection[obstacleCollection.size() - 1]->getDim().x;
	int currentBackgroundSize = 0;
	std::shuffle(bImage.begin(), bImage.end(),  std::default_random_engine(static_cast<unsigned int>(seed))); //C++ 11 features: shuffle and default_random_engine 
	
	auto it = bImage.cbegin();

	while (currentBackgroundSize < screenLim)
	{
		it++;
		if (it == bImage.cend())
		{
			std::shuffle(bImage.begin(), bImage.end(),  std::default_random_engine(static_cast<unsigned int>(seed))); //C++ 11 features: shuffle and default_random_engine 
	
			it = bImage.cbegin();
		}	

		sf::Sprite* temp = new sf::Sprite(**it);
		temp->setPosition(static_cast<float>(currentBackgroundSize), 0);
		
		generatedBackground.push_back(temp);
		currentBackgroundSize += temp->getTexture()->getSize().x;
	}
}