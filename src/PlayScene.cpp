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

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	static float initialVelocity = m_pPlayer->getInitVelocity();
	static int angleDegrees = m_pPlayer->getAngleDegrees();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Thermal Detonator Simulation", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	
	if(ImGui::SliderFloat("Initial Velocity", &initialVelocity, 0.0f, 199.0f))
	{
		std::cout << initialVelocity << std::endl;
		m_pPlayer->setInitVelocity(initialVelocity);
	}

	ImGui::Separator();
	
	if (ImGui::SliderInt("Initial Angle (Degrees)", &angleDegrees, 0, 90))
	{
		std::cout << angleDegrees << std::endl;
		m_pPlayer->setAngleDegrees(angleDegrees);
	}

	ImGui::Separator();

	if (ImGui::Button("Reset"))
	{
		std::cout << "Scenario Reset" << std::endl;
		m_pPlayer->setInitVelocity(95.0f);
		m_pPlayer->setAngleDegrees(75);
		m_pPlayer->setPosition(glm::vec2(100.0f, 675.0f));

		initialVelocity = m_pPlayer->getInitVelocity();
		angleDegrees = m_pPlayer->getAngleDegrees();
	}

	ImGui::Separator();

	ImGui::Text("X position = %f", (m_pPlayer->getPosition().x - 100.0f));
	ImGui::Text("y position = %f", (675 - m_pPlayer->getPosition().y));

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}