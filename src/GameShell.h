#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "obstacle.h"
#include "Menu.h"
#include "Score.h"
#include "player.h"
#include "airObstacle.h"
#include <iostream>
#include <string>
#include <vector>//C++ 11 Feature: range based for loop and auto
#include <chrono>
#include <random>
class GameShell
{
public:
	GameShell();

	void startGame(sf::RenderWindow& Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage, Menu menu);
	void assignObstacleType(std::vector<Obstacle*>& obstacleCollection, int numObstacle, sf::Vector2i screenDimensions);
};