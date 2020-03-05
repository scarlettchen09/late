#include "Score.h"
#include <iostream>
Score::Score(int timeSeconds) : curScore(0.0f)
{
	timeElapsed.restart();
	setScoreText();
}

void Score::startScore()
{
    timeElapsed.restart();
}

void Score::setScoreText()
{
	std::string filePrefixH = "C://Users//delli7desktop//Documents//GitHub//late//late//resources//";
	std::string filePrefixLinux = "../resources/";

	std::string file = filePrefixLinux + "font.ttf";
	if (!font.loadFromFile(file))
	{
		std::cout << "Error opening \"" << file << "\"\n";
	}

	ScoreText.setFont(font);
	ScoreText.setCharacterSize(50);
	ScoreText.setFillColor(sf::Color::White);

	ScoreText.setString(std::to_string(static_cast<int>(curScore)));
	ScoreText.setPosition(0, 0);
}

void Score::update()
{
	curScore += timeElapsed.getElapsedTime().asSeconds() * 2;
	timeElapsed.restart();
	ScoreText.setString(std::to_string(static_cast<int>(curScore)));

}

sf::Text Score::getText()
{
    return ScoreText;
}