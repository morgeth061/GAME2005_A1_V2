#include "Ramp.h"
#include "TextureManager.h"

Ramp::Ramp()
{
	TextureManager::Instance()->load("../Assets/Textures/ramp.png", "ramp");
	getTransform()->position = glm::vec2(100.0f, 675.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(RAMP);
}

Ramp::~Ramp()
{
}

void Ramp::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("ramp", x, y);
}

void Ramp::update()
{
}

void Ramp::clean()
{
}

void Ramp::setHeight(float height)
{
	m_height = height;
}

float Ramp::getHeight()
{
	return m_height;
}

void Ramp::setLength(float length)
{
	m_length = length;
}

float Ramp::getLength()
{
	return m_length;
}
