#include "Player.h"
#include "TextureManager.h"

Player::Player()
{
	
	TextureManager::Instance()->load("../Assets/Textures/Detonator.png", "detonator");

	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	angleDegrees = 75; //Angle of initial ascent, in degrees
	initVelocity = 95; //Initial speed of projectile, in m/s

	getTransform()->position = glm::vec2(100.0f, 675.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("detonator", x, y);
}

void Player::update()
{

	frameCount++;

	if (frameCount == 4)
	{
		frameCount = 1;

		if (getTransform()->position.y + getRigidBody()->velocity.y <= 675.0f)
		{
			getTransform()->position = getTransform()->position + getRigidBody()->velocity;

			getRigidBody()->velocity = getRigidBody()->velocity + getRigidBody()->acceleration;

			std::cout << getTransform()->position.y << std::endl;
		}
		else
		{
			getTransform()->position.y = 700;
		}
	}


}

void Player::clean()
{
}

void Player::setIsMoving(bool moving)
{
	isMoving = moving;
}

void Player::setAngleDegrees(int val)
{
	if(0 <= val <= 90)
	{
		angleDegrees = val;
	}
}

void Player::setInitVelocity(float val)
{
	if(val >= 0)
	{
		initVelocity = val;
	}
}

void Player::setPosition(glm::vec2 pos)
{
	getTransform()->position = pos;
}

glm::vec2 Player::getPosition()
{
	return getTransform()->position;
}

int Player::getAngleDegrees()
{
	return angleDegrees;
}

int Player::getInitVelocity()
{
	return initVelocity;
}

void Player::reset()
{
	getTransform()->position = glm::vec2(100, 675);
	getRigidBody()->velocity = glm::vec2(initVelocity * cos(angleDegrees * (3.14 / 180)), -initVelocity * sin(angleDegrees * (3.14 / 180)));
	getRigidBody()->acceleration = glm::vec2(0, 9.8);
}
