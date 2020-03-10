#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "obstacle.h"
#include "Score.h"
#include "player.h"
#include "airObstacle.h"
#include <iostream>
#include <string>
#include <vector>//C++ 11 Feature: range based for loop and auto
#include <chrono>
#include <random>
class Menu
{
private:
	const int numberOfMenuOptions;
	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text> menuOptions; //STL Container: vector
	sf::Text option;
	sf::Texture menuBackground;
	sf::Sprite menuBack;
public:
	Menu();
	Menu(float width, float height);
	void mainMenu(sf::RenderWindow & Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage);
	void displayBackground(sf::RenderWindow& Window);
	void drawAllOptions(sf::RenderWindow& window);
	void drawOption(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void displayGameOver(sf::RenderWindow & window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, sf::Sprite bImage);
	int GetPressedItem() { return selectedItemIndex; }
};