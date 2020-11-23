#include "Player.h"
#include "TextureManager.h"

Player::Player()
{

	TextureManager::Instance()->load("../Assets/Textures/Detonator.png", "detonator");

	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	//angleDegrees = 75; //Angle of initial ascent, in degrees		// Should be equal to ramp angle
	initVelocity = 0; //Initial speed of projectile, in m/s		// Should be 0, and increase as it descends the ramp, then decrease against the floor

	getTransform()->position = glm::vec2(90.0f, 620.0f);
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

	if(isMoving == true)
	{
		frameCount++;
		if (frameCount == 4)
		{
			frameCount = 1;

			//getTransform()->position = getTransform()->position + getRigidBody()->velocity;

			//getRigidBody()->velocity = glm::vec2(sqrt(2 * 9.81 * ((getTransform()->position.y - 90) / 30)) * cos(angleDegrees * (3.14 / 180)), sqrt(2 * 9.81 * ((getTransform()->position.y - 90) / 30)) * sin(angleDegrees * (3.14 / 180)));

			if (((getTransform()->position.y - 725) / 30) < -2)
			{
				getTransform()->position = getTransform()->position + getRigidBody()->velocity;
				getRigidBody()->velocity = glm::vec2(sqrt(2 * 9.81 * ((getTransform()->position.y - 90) / 30)) * cos(angleDegrees * (3.14 / 180)), sqrt(2 * 9.81 * ((getTransform()->position.y - 90) / 30)) * sin(angleDegrees * (3.14 / 180)));
			}
			else
			{
				getRigidBody()->acceleration = glm::vec2(-0.548, 0);
				getRigidBody()->velocity = glm::vec2(getRigidBody()->velocity.x + getRigidBody()->acceleration.x, 0);
				if(getRigidBody()->velocity.x > 0)
				{
					getTransform()->position = getTransform()->position + getRigidBody()->velocity;
				}
				else
				{
					getRigidBody()->velocity = glm::vec2(0, 0);
				}
			}

			std::cout << ((getTransform()->position.y - 725) / 30) << rampHeight << std::endl;

			

			//getRigidBody()->velocity = getRigidBody()->velocity + getRigidBody()->acceleration;

			// Guessing this is the math? if so should be changed so the ball moves down the ramp with acceleration.
			// Once it reaches the same displacement as the length of the ramps hyp it should change
			// Should travel straight against the ground and decelerate according to friction with the floor
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

void Player::setAngleDegrees(float val)
{
	// Should be used to set angle to angle of ramp then when reaches floor
	if (0 <= val <= 90)
	{
		angleDegrees = val;
	}
}

void Player::setInitVelocity(float val)
{
	if (val >= 0)
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

void Player::setRampLength(float length)
{
	rampLength = length;
}

void Player::setRampHeight(float height)
{
	rampHeight = height;
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
	getTransform()->position = glm::vec2(glm::vec2(100.0f, ((rampHeight * -30) + 700)));
	getRigidBody()->velocity = glm::vec2(0,0);
	//getRigidBody()->acceleration = glm::vec2(0, 9.8);
}
