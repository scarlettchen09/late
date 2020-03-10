#include "Timer.h"
#include <iostream>
Timer::Timer(int timeSeconds)
{
	remainingTime = sf::seconds(timeSeconds);
	timeElapsed.restart();
	setTimerText();
}

void Timer::startTimer()
{
    timeElapsed.restart();
}

void Timer::setTimerText()
{
	char file[] = "C:\\Users\\delli7desktop\\Documents\\GitHub\\late\\late\\resources\\font.ttf";
	if (!font.loadFromFile(file))
	{
		std::cout << "Error opening \"" << file << "\"\n";
	}

	timerText.setFont(font);
	timerText.setCharacterSize(50);
	timerText.setFillColor(sf::Color::White);
	timerText.setString(std::to_string(remainingTime.asSeconds()));
	timerText.setPosition(0, 0);
}

void Timer::update()
{
	if (remainingTime.asSeconds() > 0)
	{
		remainingTime -= timeElapsed.getElapsedTime();
		timeElapsed.restart();
		timerText.setString(std::to_string(static_cast<int>(remainingTime.asSeconds())));
	}
}

sf::Text Timer::getText()
{
    return timerText;
}