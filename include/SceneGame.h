#pragma once

#include "Scene.h"
#include "Window.h"
#include "EntityManager.h"
#include "ActionManager.h"
#include "SystemManager.h"
#include "PhysicsSystem.h"
#include "AudioSystem.h"
#include "LivesSystem.h"
#include "ScoreSystem.h"
#include "Gui.h"
#include "GameState.h"

class SceneGame : public Scene
{
private:
    Window& m_window;
    EntityManager m_entities;
    ActionManager m_actions;
    SystemManager m_systems;
    std::shared_ptr<Gui> m_gui;
    
    bool m_running = true;
    GameState m_state = GameState::Playing;
    bool m_paused = false;

    friend class Gui;

    void spawnBullet();
    void spawnEnemy(bool canSpawnNotSpawnEnabled = false);
    
    void createEntities();
    void bindActions();

public:
    SceneGame(Window& window);

    void init() override;
    void handleEvents() override;
    void update() override;
    void render() override;

    const EntityManager& getEntityManager() const { return m_entities; }
    Window& getWindow() const { return m_window; }

    bool isRunning() const { return m_running; }
    GameState getGameState() const { return m_state; }
};
