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
	std::vector<sf::Text> getMenuOptions();
	sf::IntRect* createIntRect(sf::Vector2i position, std::string item, int characterSize);
	void mainMenu(sf::RenderWindow & Window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>&bImage);
	void helpScreen(sf::RenderWindow & window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>& bImage, Menu menu, sf::Event event);
	void displayBackground(sf::RenderWindow& Window);
	void drawAllOptions(sf::RenderWindow& window);
	void drawOption(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void displayGameOver(sf::RenderWindow & window, sf::Vector2i screenDimensions, sf::Sound sound, sf::View view, sf::Texture playerTexture, std::vector<sf::Sprite*>& bImage, std::string msg, Score score);
	int GetPressedItem() { return selectedItemIndex; }
};