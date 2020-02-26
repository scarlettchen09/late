#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "obstacle.h"
#include "Menu.h"
#include "player.h"
#include "Timer.h"
#include "cScreen.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "EndScreen.h"
#include <iostream>
#include <string>


void mainMenu(sf::RenderWindow& Window, sf::Vector2i &screenDimensions);

int main()
{
	sf::Vector2i screenDimensions(800, 600);
	sf::RenderWindow Window;
	Window.setFramerateLimit(60);
	std::vector<cScreen*> Screens;
	int screen = 0;
	//Window creation
	Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Late!");

	//Screens preparations
    MenuScreen s0(screenDimensions);
  	Screens.push_back(&s0);
  	GameScreen s1(screenDimensions);
 	Screens.push_back(&s1);
	EndScreen s2(screenDimensions);
	Screens.push_back(&s2);

	//Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(Window, screenDimensions);
	}

	return 0;
}
