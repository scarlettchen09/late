#include "EndScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

EndScreen::EndScreen(sf::Vector2i& screenDimensions){
	
}

int EndScreen::Run(sf::RenderWindow &Window, sf::Vector2i& screenDimensions){
    sf::Font font;
    sf::Text gameOverText;
    sf::Text againText;

    sf::Texture endBackground;
    sf::Sprite endBack;

    float width = screenDimensions.x;
	float height = screenDimensions.y;

    char file[] = "C:\\Users\\delli7desktop\\Documents\\GitHub\\late\\late\\resources\\resources\\font.ttf";
	if (!font.loadFromFile(file))
	{
		std::cout << "Error opening \"" << file << "\"\n";
		exit(EXIT_FAILURE);
	}

    gameOverText.setFont(font);
    gameOverText.setFillColor(sf::Color::White);
	gameOverText.setString("You were\nLATE!");
	gameOverText.setPosition(sf::Vector2f(width / 2 + width / 15, height / 5 * 2));

    againText.setFont(font);
    againText.setFillColor(sf::Color::Red);
	againText.setString("Restart");
	againText.setPosition(sf::Vector2f(width / 2 + width / 15, height / 5 * 2));


    if (!endBackground.loadFromFile("C:\\Users\\delli7desktop\\Documents\\GitHub\\late\\late\\resources\\resources\\wakeup.png"))
		std::cout << "Could not load background image" << std::endl;
	endBack.setTexture(endBackground);
	endBack.setScale(width / endBack.getLocalBounds().width, height / endBack.getLocalBounds().height);
  
    sf::Event event;

    bool running = true;

    while(running){
        while (Window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {

                case sf::Keyboard::Return:
                    std::cout <<"Going from EndScreen to MenuScreen" << std::endl;
                    return 0;
                    break;

                break;
                }
                break;
            case sf::Event::Closed:
                Window.close();
                return -1;
                break;

            }
        }
        Window.clear();
        Window.draw(gameOverText);
        Window.draw(againText);

        Window.display();
    }
   
    return -1;
}