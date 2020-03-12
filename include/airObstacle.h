#ifndef AIR_OBSTACLE_H
#define AIR_OBSTACLE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "obstacle.h"

class AirObstacle : public Obstacle
{
public:
	AirObstacle(sf::Vector2i screen, sf::Vector2f obstacleDim, const sf::Texture obstacle, sf::IntRect box);
	void generateObstacle(double pos);
};
#endif