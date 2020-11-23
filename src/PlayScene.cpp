#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 0, 0);
	TextureManager::Instance()->draw("floor", 0, 725);

	/*if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	} */

	GUI_Function();



	drawDisplayList();
	m_pPlayer->draw();

	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), m_pRampHeight.x, m_pRampHeight.y, m_pRampLength.x, m_pRampLength.y);
	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), m_pRampHeight.x, m_pRampHeight.y, m_pRampOrigin.x, m_pRampOrigin.y);
	SDL_RenderDrawLine(Renderer::Instance()->getRenderer(), m_pRampLength.x, m_pRampLength.y, m_pRampOrigin.x, m_pRampOrigin.y);

	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{

	// Set GUI Title
	m_guiTitle = "Play Scene";

	TextureManager::Instance()->load("../Assets/Textures/background.jpg", "background");
	TextureManager::Instance()->load("../Assets/Textures/Floor.png", "floor");

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	// Back Button
	m_pPlayButton = new Button("../Assets/textures/startButton.png", "playButton", PLAY_BUTTON);
	m_pPlayButton->getTransform()->position = glm::vec2(400.0f, 762.5f);

	m_pPlayButton->addEventListener(CLICK, [&]()->void
		{
			m_pPlayButton->setActive(false);
			m_pPlayer->reset();
			m_pPlayer->setIsMoving(true);
			//TheGame::Instance()->changeSceneState(START_SCENE);
		});

	m_pPlayButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pPlayButton->setAlpha(128);
		});

	m_pPlayButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pPlayButton->setAlpha(255);
		});

	addChild(m_pPlayButton);
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	static float initialVelocity = m_pPlayer->getInitVelocity();
	static float rampLength = (m_pRampLength.x - 90) / 30;
	static float rampHeight = -1 * (m_pRampHeight.y - 725) / 30;
	static int angleDegrees = m_pPlayer->getAngleDegrees();

	

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Loot Box Simulation", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::SliderFloat("Ramp Height", &rampHeight, 1.0f, 10.0f))
	{
		std::cout << rampHeight << std::endl;
		m_pRampHeight = glm::vec2(m_pRampHeight.x, ((rampHeight * -30) + 725));

		m_pRampAngle = atan((rampHeight / rampLength)) * (180/3.14);

		m_pPlayer->setAngleDegrees(m_pRampAngle);
		m_pPlayer->setRampHeight(rampHeight);
		
		// Should this not move the players position and angle?
		// Ramp angle = tan(theta) * (height/length) == theta = atan(h/l)
		//m_pPlayer->setAngleDegrees(75); // Should set the the angle of the hyp of the ramp
		m_pPlayer->setPosition(glm::vec2(100.0f, ((rampHeight * -30) + 700)));  // position should be just above the value of the top point on the ramp
	}

	ImGui::Separator();

	if (ImGui::SliderFloat("Ramp Length", &rampLength, 1.0f, 10.0f))
	{
		std::cout << rampLength << std::endl;
		m_pRampLength = glm::vec2(((rampLength * 30.0f) + 90.0f), m_pRampLength.y);

		m_pRampAngle = atan((rampHeight / rampLength)) * (180 / 3.14);

		m_pPlayer->setAngleDegrees(m_pRampAngle);
		m_pPlayer->setRampLength(rampLength);

		m_pPlayer->setPosition(glm::vec2(100.0f, ((rampHeight * -30) + 700)));
		
		// Should this not move the players  angle?
		// Ramp angle == tan(theta) = (height/length) == theta = atan(h/l)
		//m_pPlayer->setAngleDegrees(75); // Should set the the angle of the hyp of the ramp
	}

	ImGui::Separator();

	if (ImGui::Button("Reset"))
	{
		std::cout << "Scenario Reset" << std::endl;
		m_pPlayer->reset();
		//m_pPlayer->setInitVelocity(95.0f);	// Velocity should be 0 at the top of the ramp i believe
		//m_pPlayer->setAngleDegrees(75); // Should set the the angle of the hyp of the default ramp
		//m_pPlayer->setPosition(glm::vec2(100.0f, 675.0f));  // position should be just above the value of the default top point on the ramp

		initialVelocity = m_pPlayer->getInitVelocity();
		angleDegrees = m_pPlayer->getAngleDegrees();
		
	}

	m_pRampAngle = atan((rampHeight / rampLength)) * (180 / 3.14);

	ImGui::Separator();

	ImGui::Text("X position = %f", (m_pPlayer->getPosition().x - 100.0f));
	ImGui::Text("y position = %f", (675 - m_pPlayer->getPosition().y));

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}