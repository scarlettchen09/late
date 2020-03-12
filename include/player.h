#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
// iostream is used for bebugging only :)
class Player
{
	sf::Vector2i screenDim;
	sf::Vector2i playerDim;
	sf::Sprite playerSprite;
	sf::IntRect currentTextureRect;
	sf::Vector2f playerPos;
	sf::IntRect hitbox;
	sf::IntRect cushion;
	int noOfImg;
	int animation[2]; // [0]->animationCtr  ,  [1]->animationRate

	double playerXacceleration;
	double playerXvelocity;
	double playerYacceleration;
	double playerYvelocity;
	double jumpHeight;
	unsigned short maxNoOfJump;
	unsigned short noOfJump;
	const int xLocCharacter = 10;

public:
	Player(sf::Vector2i screenDim, sf::Vector2i pDim, sf::Texture &playerText, int noImg, sf::Vector2i box = sf::Vector2i(0, 0));

	sf::Vector2i getDim();
	sf::Sprite getSprite();
	double getXvelocity();
	double getAcceleration();
	sf::Vector2f getPosition();
	sf::IntRect getHitbox();
	sf::IntRect getCushion();

	void setYacceleration(double yAcl);
	void setAnimationRate(int rate);
	void setXvelocity(double xVel);
	void setAcceleration(double acceleration);
	void setJumpHeight(double height);
	void setMaxNoOfJump(unsigned short no);
	
	void speedUp(double rate);
	void speedDown(double rate);
	bool jump();
	void update();
	void resetPlayerPos();
	void resetWindowView(sf::Vector2f position, sf::Vector2i screenDimensions, sf::View view, sf::RenderWindow& window);
};
#endif
