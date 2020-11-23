#pragma once
#include "PlayerAnimationState.h"
#include "Sprite.h"

#ifndef __RAMP__
#define __RAMP__


class Ramp final : public Sprite
{
public:
	Ramp();
	~Ramp();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setHeight(float height);

	float getHeight();

	void setLength(float length);

	float getLength();

private:
	float m_length;
	float m_height;
};

#endif /* defined (__RAMP__) */
