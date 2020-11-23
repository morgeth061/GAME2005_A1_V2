#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Ramp.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	Ramp* m_pRamp;
	bool m_playerFacingRight;

	//Ramp
	glm::vec2 m_pRampHeight = glm::vec2(90, 665);
	glm::vec2 m_pRampLength = glm::vec2(210, 725);
	glm::vec2 m_pRampOrigin = glm::vec2(90, 725);

	float m_pRampAngle = 36.0f;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Button* m_pPlayButton;
	Label* m_pInstructionsLabel;
};

#endif /* defined (__PLAY_SCENE__) */