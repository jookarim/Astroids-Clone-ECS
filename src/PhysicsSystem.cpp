#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(EntityManager& entityManager, Window& window)
    : m_entityManager(entityManager)
    , m_window(window)
    , m_startPressed(false)
    , m_exitPressed(false)
    , m_physicsEnabled(true)
{
}


void PhysicsSystem::update(float dt)
{
    m_startPressed = false;
    m_exitPressed = false;

    if (!m_physicsEnabled) return;

    m_state.playerHit = false;
    m_state.enemyHit = false;

    for (auto& bullet : m_entityManager.getEntities("Bullet"))
    {
        if (!bullet->isAlive()) continue;

        auto& bulletBB = bullet->getComponent<CBoundingBox>();

        for (auto& enemy : m_entityManager.getEntities("Enemy"))
        {
            if (!enemy->isAlive()) continue;

            auto& enemyBB = enemy->getComponent<CBoundingBox>();

            if (Collision::checkCollisionRecs(
                bulletBB.m_min, bulletBB.m_max,
                enemyBB.m_min, enemyBB.m_max))
            {
                bullet->destroy();
                enemy->destroy();
                m_state.enemyHit = true;
                break;
            }
        }
    }

    /* ---------------------------------
       Player vs Enemy + Window Bounds
    --------------------------------- */
    for (auto& player : m_entityManager.getEntities("Player"))
    {
        if (!player->isAlive()) continue;

        auto& playerBB = player->getComponent<CBoundingBox>();
        auto& transform = player->getComponent<CTransform>();
        auto& velocity = player->getComponent<CVelocity>();
        auto& sprite = player->getComponent<CSprite>();

        /* ---- Player vs Enemy ---- */
        for (auto& enemy : m_entityManager.getEntities("Enemy"))
        {
            if (!enemy->isAlive()) continue;

            auto& enemyBB = enemy->getComponent<CBoundingBox>();

            if (Collision::checkCollisionRecs(
                playerBB.m_min, playerBB.m_max,
                enemyBB.m_min, enemyBB.m_max))
            {
                enemy->destroy();

                transform.m_position = {
                    m_window.getWidth() * 0.5f,
                    m_window.getHeight() * 0.5f
                };
                transform.m_rotation = 0.f;

                m_state.playerHit = true;
            }
        }

        float w = sprite.m_texture->getSize().x * transform.m_scale.x;
        float h = sprite.m_texture->getSize().y * transform.m_scale.y;

        int windowWidth = m_window.getWidth();
        int windowHeight = m_window.getHeight();

        if (transform.m_position.x < 0.f)
        {
            transform.m_position.x = 0.f;
            velocity.m_velocity.x = 0.f;
        }

        if (transform.m_position.x + w > windowWidth)
        {
            transform.m_position.x = windowWidth - w;
            velocity.m_velocity.x = 0.f;
        }

        if (transform.m_position.y < 0.f)
        {
            transform.m_position.y = 0.f;
            velocity.m_velocity.y = 0.f;
        }

        if (transform.m_position.y + h > windowHeight)
        {
            transform.m_position.y = windowHeight - h;
            velocity.m_velocity.y = 0.f;
        }
    }
    
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (!(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)))
        return;

    Vec2f mousePos{
        static_cast<float>(mouseX),
        static_cast<float>(mouseY)
    };

    for (auto& e : m_entityManager.getEntities())
    {
        if (!e->hasComponent<CButtonTag>() ||
            !e->hasComponent<CBoundingBox>())
            continue;

        auto& bb = e->getComponent<CBoundingBox>();

        if (Collision::checkCollisionPointRect(
            mousePos,
            bb.m_min,
            bb.m_max))
        {
            if (e->hasComponent<CStartButtonTag>())
            {
                m_startPressed = true;
                return;
            }

            if (e->hasComponent<CExitButtonTag>())
            {
                m_exitPressed = true;
                return;
            }
        }
    }
}
