#pragma once

#include "EntityManager.h"
#include "Window.h"
#include "Collision.h"
#include "System.h"

struct PhysicsState
{
    bool playerHit = false; 
    bool enemyHit = false; 
};

class PhysicsSystem : public System
{
private:
    EntityManager& m_entityManager;
    Window& m_window;
    PhysicsState   m_state;
    bool m_physicsEnabled = true;
    bool m_startPressed = false;
    bool m_exitPressed = false;
public:
    PhysicsSystem(EntityManager& entityManager, Window& window);

    void update(float dt) override;

    PhysicsState getState() { return m_state; }

    void setPhysicsEnabled(bool enabled) { m_physicsEnabled = enabled; }
    void consumePlayerHit()
    {
        m_state.playerHit = false;
    }

    bool getStartPressed() const { return m_startPressed; } 
    bool getExitPressed() const { return m_exitPressed; }

    void resetButtons()
    {
        m_startPressed = false;
        m_exitPressed = false;
    }
};
