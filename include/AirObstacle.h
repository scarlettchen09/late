#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Obstacle.h"

class AirObstacle : public Obstacle
{
public:
	AirObstacle(sf::Vector2i screen, sf::Vector2f obstacleDim, const sf::Texture obstacle, sf::IntRect box);
	void generateObstacle(double pos);
};