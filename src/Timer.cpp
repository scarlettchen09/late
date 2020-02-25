#include "Timer.h"

#include <iostream>
Timer::Timer() {
    remainingTime = sf::seconds(20);
    timeElapsed.restart();

    char file[] = "../resources/font.ttf";
	if (!font.loadFromFile(file))
	{
		std::cout << "Error opening \"" << file << "\"\n";
		//exit(EXIT_FAILURE);
	}

    timerText.setFont(font);
    timerText.setCharacterSize(50);
    timerText.setFillColor(sf::Color::White);
    timerText.setString(std::to_string(remainingTime.asSeconds()));
    timerText.setPosition(0,0);
}

void Timer::startTimer(){
    timeElapsed.restart();
}

void Timer::update(){
    remainingTime -= timeElapsed.getElapsedTime();
    timeElapsed.restart();
    timerText.setString(std::to_string(static_cast<int>(remainingTime.asSeconds())));

}


sf::Text Timer::getText(){
    return timerText;
}