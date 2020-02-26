#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Timer{
    private:
        sf::Clock timeElapsed;
        sf::Time remainingTime;
        sf::Font font;
        sf::Text timerText;

    public:
        Timer();
        void startTimer();
        void update();
        sf::Text getText();
};