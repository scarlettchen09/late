#include "player.h"

/*
Constructor: constructs the player object with an optional hit box paramater.
Initializes every member variable and defaulted the player attributes. 
*/
Player::Player(sf::Vector2i screen, sf::Vector2i pDim, sf::Texture& playerText, int noImg, sf::Vector2i box)
	:screenDim(screen), playerDim(pDim), noOfImg(noImg)
{
	int xLocCharacter = 10; // default
	playerSprite.setTexture(playerText);
	currentTextureRect = sf::IntRect(0, 0, playerDim.x, playerDim.y);
	playerSprite.setTextureRect(currentTextureRect);
	playerPos = sf::Vector2f(xLocCharacter, screenDim.y - playerDim.y);
	playerSprite.setPosition(playerPos);
	if (box.x == 0) // default
	{
		hitbox = sf::IntRect(xLocCharacter, screenDim.y - playerDim.y, pDim.x, pDim.y);
		cushion = sf::IntRect(xLocCharacter, screenDim.y - playerDim.y, pDim.x + 200, pDim.y);
	}
	else // given hitbox
	{
		hitbox = sf::IntRect(sf::Vector2i(xLocCharacter, screenDim.y - playerDim.y), box);
		cushion = sf::IntRect(sf::Vector2i(xLocCharacter, screenDim.y - playerDim.y), sf::Vector2i(box.x + 200, box.y));
	}
	noOfImg = noImg;

	// default values
	animation[0] = 0;
	animation[1] = 5;
	playerXacceleration = 0;
	playerXvelocity = 0;
	playerYacceleration = 1.0f; // gravity
	playerYvelocity = 0;
	jumpHeight = 0;
	maxNoOfJump = 2;
	noOfJump = maxNoOfJump;
}


/*~*~*~*~*~*~*~*~*
ACESSOR FUNCTIONS
*~*~*~*~*~*~*~*~*/

sf::Vector2i Player::getDim()
{
	return playerDim;
}


sf::Sprite Player::getSprite()
{
	return playerSprite;
}

double Player::getXvelocity()
{
	return playerXvelocity;
}

double Player::getAcceleration()
{
	return playerXacceleration;
}

sf::Vector2f Player::getPosition()
{
	return playerPos;
}


sf::IntRect Player::getHitbox()
{
	return hitbox;
}

sf::IntRect Player::getCushion()
{
	return cushion;
}

/*~*~*~*~*~*~*~*~*
MUTATOR FUNCTIONS
*~*~*~*~*~*~*~*~*/

void Player::setAnimationRate(int rate)
{
	animation[1] = rate;
}

void Player::setXvelocity(double xVel)
{
	playerXvelocity = xVel;
}

void Player::setAcceleration(double acceleration)
{
	playerXacceleration = acceleration;
}

void Player::setJumpHeight(double height)
{
	jumpHeight = height;
}

void Player::setMaxNoOfJump(unsigned short no)
{
	maxNoOfJump = no;
}

/*~*~*~*~*~*~*~*
MEMBER FUNCTIONS
*~*~*~*~*~*~*~*/

void Player::speedUp(double rate)
{
	playerXvelocity *= rate;
	playerYacceleration *= rate;
	jumpHeight += rate;
}

bool Player::jump()
{
	if (noOfJump)
	{
		playerYvelocity = jumpHeight;
		noOfJump--;
		return true;
	}
	return false;
}

void Player::update()
{
	animation[0]++;
	if (animation[0] == animation[1])
	{
		if (currentTextureRect.left == playerDim.x * noOfImg)
		{
			currentTextureRect.left = 0;
		}
		else
		{
			currentTextureRect.left += playerDim.x;
		}

		playerSprite.setTextureRect(currentTextureRect);
		animation[0] = 0;
	}
	
	if (playerSprite.getPosition().y < screenDim.y - playerDim.y)
	{
		playerYvelocity -= playerYacceleration;
	}
	else if (playerSprite.getPosition().y > screenDim.y - playerDim.y)
	{
		playerSprite.setPosition(playerSprite.getPosition().x, screenDim.y - playerDim.y);
	}

		

	playerSprite.move(playerXvelocity, -playerYvelocity);
	hitbox.left = playerSprite.getPosition().x;
	hitbox.top = playerSprite.getPosition().y;
	cushion.left = playerSprite.getPosition().x;
	cushion.top = playerSprite.getPosition().y;
	if (playerSprite.getPosition().y >= screenDim.y - playerDim.y)
	{
		playerYvelocity = 0.0f;
		noOfJump = maxNoOfJump;
	}
	
}