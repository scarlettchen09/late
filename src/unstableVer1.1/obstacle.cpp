#include "obstacle.h"

Obstacle::Obstacle(sf::Vector2i screen, sf::Vector2f obstacleDim, const sf::Texture obstacle, int numberOfObstacle)
	:screenDim(screen), dim(obstacleDim), obstacleTexture(obstacle), counter(0)
{ 
	rect = new sf::RectangleShape* [numberOfObstacle];
}

sf::Vector2f Obstacle::getDim()
{
	return dim;
}

int Obstacle::getCounter()
{
	return counter;
}

bool Obstacle::generateObstacle(double pos, int seed, int obstacleGenSpeed)
{
	srand(seed * time(0));
	if (rand() % obstacleGenSpeed == 0 && counter < 100 && ((int)pos % (obstacleGenSpeed * 40)) == 0)
	{  
		rect[counter] = new sf::RectangleShape(dim);
		rect[counter]->setPosition(pos + screenDim.x, screenDim.y - dim.y);
		rect[counter]->setTexture(&obstacleTexture);
		counter++;
		std::cout << "OBSTACLE CREATED #" << counter << std::endl;
		return true;
	}
	return false;
}

bool Obstacle::collision(sf::Sprite & player, int i, bool autoPlayFlag)
{
	double playerX1 = player.getPosition().x;
	double playerX2 = player.getPosition().x + 10;
	double playerY = player.getPosition().y + 130;
	double obstacleX = (rect)[i]->getPosition().x;
	double obstacleY = (rect)[i]->getPosition().y;
	int autoDis = 190;
	if ((playerX1 < obstacleX && obstacleX < playerX2) && (playerY > obstacleY) && !autoPlayFlag)
	{
		return true;
	}
	else if ((playerX1 + autoDis < obstacleX && obstacleX < playerX2 + autoDis) && playerY > obstacleY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

sf::RectangleShape** Obstacle::getObstacle()
{
	return rect;
}
