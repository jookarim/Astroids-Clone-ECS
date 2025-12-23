#pragma once

#include <iostream>
#include "Components.h"
#include "System.h"
#include "EntityManager.h"
#include "PhysicsSystem.h"
	
class ScoreSystem : public System
{
private:
	EntityManager& m_entityManager;
	PhysicsSystem& m_physicsSystem;
	int score = 0;
public:
	ScoreSystem(EntityManager& entityManager, PhysicsSystem& physicsSystem);
	void update(float dt) override;
	int getScore() const;
};

