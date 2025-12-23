#pragma once

#include "System.h"
#include "EntityManager.h"
#include "ActionManager.h"
#include "Window.h"

class MovementSystem : public System
{
private:
	EntityManager& m_entityManager;
	ActionManager& m_actionManager;
	bool m_timeEnabled;
	bool m_movementEnabled = true;
	Window& m_window;
public:
	MovementSystem(EntityManager& entityManager, ActionManager& actionManager,Window& window,bool timeEnabled = true);
	~MovementSystem() = default;

	void setTimeEnabled(bool enabled);
	void setMovementEnabled(bool enabled);

	bool isMovementEnabled() const { return m_movementEnabled; }

	void update(float deltaTime) override;
};

