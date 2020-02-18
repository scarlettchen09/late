#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
class Obstacle
{
	int counter;
	sf::Vector2f dim;
	sf::Vector2i screenDim;
	sf::RectangleShape** rect;
	sf::Texture obstacleTexture;

	
public:
	
	Obstacle(sf::Vector2i screen, sf::Vector2f obstacleDim, const sf::Texture obstacle, int numberOfObstacle);
	sf::Vector2f getDim();
	sf::RectangleShape** getObstacle();
	int getCounter();
	void generateObstacle(double pos, int seed);
	bool collision(sf::RectangleShape player, sf::RectangleShape obstacle);
	



};
#endif
