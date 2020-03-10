#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Score
{
    private:
        sf::Clock timeElapsed;
        sf::Font font;
        sf::Text ScoreText;
		sf::Text labelText;
        double curScore;
        int printAlertInterval;
        int curAlertScore;

    public:
        Score();
        void startScore();
		void setScoreText();
        void update();
		sf::Text getLabel();
        sf::Text getText();
        friend std::ostream& operator<<(std::ostream& os, const Score& score);
};