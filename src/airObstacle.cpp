#include "airObstacle.h"

AirObstacle::AirObstacle(sf::Vector2i screen, sf::Vector2f obstacleDim, const sf::Texture obstacle, sf::IntRect box)
	: Obstacle(screen, obstacleDim, obstacle, box)
{ 
}

void AirObstacle::generateObstacle(double pos)
{
	rect.setPosition(pos, screenDim.y - dim.y - 180);
	rect.setTexture(&obstacleTexture);
	hitbox.left += pos;
	hitbox.top += screenDim.y - dim.y - 180;
}