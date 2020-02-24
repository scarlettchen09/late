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
	int noOfImg;
	int animation[2]; // [0]->animationCtr  ,  [1]->animationRate

	double playerXacceleration;
	double playerXvelocity;
	double playerYacceleration;
	double playerYvelocity;
	double jumpHeight;
	unsigned short maxNoOfJump;
	unsigned short noOfJump;

public:
	Player(sf::Vector2i screenDim, sf::Vector2i pDim, sf::Texture &playerText, int noImg, sf::Vector2i box = sf::Vector2i(0, 0));

	// Accessors
	sf::Vector2i getDim();
	sf::Sprite getSprite();
	double getXvelocity();
	double getAcceleration();
	sf::Vector2f getPosition();
	sf::IntRect getHitBox();

	// Mutators
	void setAnimationRate(int rate);
	void setXvelocity(double xVel);
	void setAcceleration(double acceleration);
	void setJumpHeight(double height);
	void setMaxNoOfJump(unsigned short no);
	


	bool jump();
	void update();
	




};

#endif
