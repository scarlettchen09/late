#pragma once
#include "cScreen.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "player.h"
#include "obstacle.h"
#include "Timer.h"

class GameScreen : public cScreen {
    private:
    	bool running;
	
        int levelIndex; //For adjusting the rate in which obstacles are generated.
        float frametime; //Updates 60 times per second
        float xVel;
        float takeOffSpeed;
        bool autoPlay;
        bool autoJmped;

        sf::Texture bTexture;
        sf::Texture playerTexture;
        sf::Texture squirrel;
        sf::Sprite playerSprite;
        sf::Sprite bImage;
        sf::SoundBuffer jump;
        sf::Music music;
        sf::Clock clock;
        sf::Time time;
        sf::View view;
        sf::View hudView;
        sf::Sound sound;
        sf::Event Event;
        sf::RectangleShape** obstacleArr;
        sf::Vector2f position;
        Timer timer;

        //Player player(screenDimensions, sf::Vector2i(108, 140), playerTexture, 7);
    public:
        GameScreen(sf::Vector2i& screenDimensions);
        int Run(sf::RenderWindow &Window, sf::Vector2i& screenDimensions);
};