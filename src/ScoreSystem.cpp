#include "ScoreSystem.h"

ScoreSystem::ScoreSystem(EntityManager& entityManager, PhysicsSystem& physicsSystem) : m_entityManager(entityManager), m_physicsSystem(physicsSystem)
{

}

void ScoreSystem::update(float dt)
{
	for (auto& entity : m_entityManager.getEntities())
	{
		if (entity->hasComponent<CScore>())
		{
			if (m_physicsSystem.getState().enemyHit)
			{
				entity->getComponent<CScore>().m_score += 10;
				score = entity->getComponent<CScore>().m_score;
			}
		}
	}
}

int ScoreSystem::getScore() const
{
	return score;
}
