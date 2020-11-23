#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	//void setAnimationState(PlayerAnimationState new_state);

	void setIsMoving(bool moving);

	void setAngleDegrees(float val);

	void setInitVelocity(float val);

	void setPosition(glm::vec2 pos);

	glm::vec2 getPosition();

	void setRampLength(float length);

	void setRampHeight(float height);

	// getters

	int getAngleDegrees();

	int getInitVelocity();

	void reset();

private:
	//void m_buildAnimations();

	//PlayerAnimationState m_currentAnimationState;

	int angleDegrees;
	float initVelocity;
	float rampLength;
	float rampHeight;

	int frameCount = 1;
	bool isMoving = false;
};

#endif /* defined (__PLAYER__) */