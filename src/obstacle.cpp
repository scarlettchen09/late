#include "obstacle.h"

Obstacle::Obstacle(sf::Vector2i screen, sf::Vector2f obstacleDim, const sf::Texture obstacle, sf::IntRect box)
	:screenDim(screen), dim(obstacleDim), obstacleTexture(obstacle), hitbox(box)
{ 
	sf::RectangleShape temp(dim);
	rect = temp;
}

sf::Vector2f Obstacle::getDim()
{
	return dim;
}

sf::IntRect Obstacle::getHitbox()
{
	return hitbox;
}

sf::RectangleShape Obstacle::getObstacle()
{
	return rect;
}

void Obstacle::generateObstacle(double pos)
{
	rect.setPosition(static_cast<float>(pos), screenDim.y - dim.y);
	rect.setTexture(&obstacleTexture);
	hitbox.left += static_cast<int>(pos);
	hitbox.top += static_cast<int>(screenDim.y) - static_cast<int>(dim.y);
}

Obstacle::~Obstacle()
{
}


