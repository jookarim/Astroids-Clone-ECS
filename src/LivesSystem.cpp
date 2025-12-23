#include "LivesSystem.h"

LivesSystem::LivesSystem(PhysicsSystem& physicsSystem, EntityManager& entityManager)
    : m_physicsSystem(physicsSystem)
    , m_entityManager(entityManager)
{
}

void LivesSystem::update(float dt)
{
    (void)dt;

    if (!m_physicsSystem.getState().playerHit)
        return;

    for (auto& entity : m_entityManager.getEntities("Lives"))
    {
        if (!entity->hasComponent<CLive>())
            continue;

        auto& live = entity->getComponent<CLive>();

        if (live.m_lives > 0)
            live.m_lives -= 1;

        break;
    }

    m_physicsSystem.consumePlayerHit();
}
