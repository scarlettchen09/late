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

void loadMainFiles(sf::Texture& bTexture, sf::Texture& playerTexture, sf::Music& music, sf::SoundBuffer& jump, std::string prefix);
int main()
{
	sf::Vector2i screenDimensions(800, 600);
	sf::RenderWindow Window;
	sf::Texture bTexture, playerTexture;
	sf::Sprite bImage;
	sf::SoundBuffer jump;
	sf::Music music;
	sf::View view;
	sf::Sound sound;
	Menu menu;
	std::string filePrefixH = "C://Users//delli7desktop//Documents//GitHub//late//late//resources//";
	std::string filePrefixLinux = "../resources/";
	
	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Late!");
	Window.setKeyRepeatEnabled(false);
	Window.setFramerateLimit(60);

	loadMainFiles(bTexture, playerTexture, music, jump, filePrefixH);

	sound.setBuffer(jump);
	bTexture.setSmooth(true);
	bImage.setTexture(bTexture);
	bImage.setScale(1.0f, 1.0f * screenDimensions.y / bTexture.getSize().y);
	view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	music.setLoop(true);
	music.play();

	menu.mainMenu(Window, screenDimensions, sound, view, playerTexture, bImage);
	return 0;
}

void loadMainFiles(sf::Texture& bTexture, sf::Texture& playerTexture, sf::Music& music, sf::SoundBuffer& jump, std::string prefix)
{
	try 
	{
		if (!bTexture.loadFromFile(prefix + "deanzabackground.jpg"))
			throw(std::string("Could not load background image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}
	try
	{
		if (!playerTexture.loadFromFile(prefix + "player_spritesheet.png"))
			throw(std::string("Could not load player image"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}
	try
	{
		if (!music.openFromFile(prefix + "background.wav"))
			throw(std::string("Could not load background music"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}
	try 
	{
		if (!jump.loadFromFile(prefix + "jump.wav"))
			throw(std::string("Could not load jump sound effect"));
	}
	catch (const std::string& errorMessage)
	{
		std::cout << errorMessage << std::endl << std::endl;
	}

}

