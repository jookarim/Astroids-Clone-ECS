#pragma once

#include <iostream>
#include "Components.h"
#include "System.h"
#include "EntityManager.h"
#include "PhysicsSystem.h"

class LivesSystem : public System
{
private:
	EntityManager& m_entityManager;
	PhysicsSystem& m_physicsSystem;
public:
	LivesSystem(PhysicsSystem& physicsSystem, EntityManager& entityManager);
	void update(float dt) override;
};

