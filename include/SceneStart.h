#pragma once

#include <iostream>
#include "Scene.h"
#include "EntityManager.h"
#include "AssetManager.h"
#include "SystemManager.h"
#include "RenderSystem.h"
#include "Window.h"
#include "GameState.h"
#include "PhysicsSystem.h"
#include "Timer.h"
#include "Music.h"

class SceneStart : public Scene
{
private:
	EntityManager m_entities;
	SystemManager m_systems;
	Window& m_window;
	GameState m_state;	

	PhysicsSystem* m_physicsSystem = nullptr;

	void createEntities();
	void createSystems();
public:
	SceneStart(Window& window);
	void init() override;
	void render() override;
	void update() override;
	void handleEvents() override;
	GameState getState() const { return m_state; }
	bool isRunning() const { return m_state != GameState::GameOver; }
};

