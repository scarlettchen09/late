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

void Obstacle::generateObstacle(double pos, int seed)
{
	srand(seed * time(0));
	if (rand() % 6 == 0 && counter < 100 && (int)pos % 100 == 0)
	{
		rect[counter] = new sf::RectangleShape(dim);
		rect[counter]->setPosition(pos + screenDim.x / 2, screenDim.y - dim.y);
		rect[counter]->setTexture(&obstacleTexture);
		counter++;
		std::cout << "OBSTACLE CREATED #" << counter << std::endl;
	}
	
}


bool Obstacle::collision(sf::RectangleShape player, sf::RectangleShape obstacle)
{
	if (player.getPosition().x >= obstacle.getPosition().x && player.getPosition().y >= obstacle.getPosition().y)
		return true;
	return false;
}


sf::RectangleShape** Obstacle::getObstacle()
{
	return rect;
}
