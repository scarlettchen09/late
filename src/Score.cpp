#include "Score.h"
#include <iostream>
#include <array>
#include <random>
#include <chrono>

Score::Score() : curScore(0.0f), printAlertInterval(15), curAlertScore(15)
{
	timeElapsed.restart();
	setScoreText();
}

void Score::startScore()
{
    timeElapsed.restart();
}

double Score::getScore()
{
	return curScore;
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


	labelText.setFont(font);
	labelText.setCharacterSize(50);
	labelText.setFillColor(sf::Color::White);
	labelText.setPosition(0, 0);
	labelText.setString("Score: ");

	ScoreText.setFont(font);
	ScoreText.setCharacterSize(50);
	ScoreText.setFillColor(sf::Color::White);
	ScoreText.setString(std::to_string(static_cast<int>(curScore)));
	ScoreText.setPosition(300, 0);
}

void Score::update()
{
	curScore += timeElapsed.getElapsedTime().asSeconds() * 2;
	timeElapsed.restart();
	ScoreText.setString(std::to_string(static_cast<int>(curScore)));

	if(static_cast<int>(curScore) >= curAlertScore){
		curAlertScore += printAlertInterval;
		std::cout << *this; 
	}

}

sf::Text Score::getLabel()
{
	return labelText;
}

sf::Text Score::getText()
{
    return ScoreText;
}

std::ostream& operator<<(std::ostream& os, const Score& score)
{
	//STL Container: array
	std::array<std::string, 5> possibleMessages = {"Good job!", "Keep running!", "Make it on time!", "Don't hurt the animals!", "You're almost late!"};
	
	auto seed = std::chrono::system_clock::now().time_since_epoch().count(); //C++ 11 feature: use of chrono library, better than ctime. auto is also C++ 11 feature
	std::shuffle(possibleMessages.begin(), possibleMessages.end(),  std::default_random_engine(seed)); //C++ 11 features: shuffle and default_random_engine 
	os << possibleMessages[0] << " (Current score: " << static_cast<int>(score.curScore) << ")" << std::endl << std::endl;
	return os;
}