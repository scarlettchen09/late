#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Score
{
    private:
        sf::Clock timeElapsed;
        sf::Font font;
        sf::Text ScoreText;

        double curScore;

    public:
        Score() = default;
		Score(int timeSeconds);
        void startScore();
		void setScoreText();
        void update();
        sf::Text getText();
};