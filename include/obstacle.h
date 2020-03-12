#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
class Obstacle
{
protected:

	sf::Vector2f dim;
	sf::Vector2i screenDim;
	sf::RectangleShape rect;
	sf::Texture obstacleTexture;
	sf::IntRect hitbox;

public:
	Obstacle(sf::Vector2i screen, sf::Vector2f obstacleDim, const sf::Texture obstacle, sf::IntRect box);
	~Obstacle();

	sf::Vector2f getDim();
	sf::RectangleShape getObstacle();
	sf::IntRect getHitbox();

	virtual void generateObstacle(double pos);
};
#endif
