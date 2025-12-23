#include "MovementSystem.h"
#include <cmath>

MovementSystem::MovementSystem(EntityManager& entityManager, ActionManager& actionManager, Window& window, bool timeEnabled)
    : m_entityManager(entityManager), m_actionManager(actionManager), m_timeEnabled(timeEnabled), m_window(window)
{
}

void MovementSystem::update(float deltaTime)
{
    if (m_movementEnabled)
    {
        for (auto& entity : m_entityManager.getEntities())
        {
            if (!entity->hasComponent<CTransform>() ||
                !entity->hasComponent<CVelocity>())
                continue;

            auto& transform = entity->getComponent<CTransform>();
            auto& velocity = entity->getComponent<CVelocity>();

            if (entity->hasComponent<CPlayerTag>())
            {
                velocity.m_velocity = { 0.f, 0.f };

                const float speed = 200.f;
                const float ROT_SPEED = 180.f;

                for (const auto& action : m_actionManager.getActions())
                {
                    if (action.getName() == "RotateRight" && action.isDown())
                        transform.m_rotation += deltaTime * ROT_SPEED;

                    if (action.getName() == "RotateLeft" && action.isDown())
                        transform.m_rotation -= deltaTime * ROT_SPEED;
                }

                float rad = (transform.m_rotation - 90.f) * 3.14159265f / 180.f;

                Vec2f forward{
                    -std::cos(rad),
                    -std::sin(rad)
                };

                for (const auto& action : m_actionManager.getActions())
                {
                    if (action.getName() == "MoveUp" && action.isDown())
                        velocity.m_velocity -= forward * speed;

                    if (action.getName() == "MoveDown" && action.isDown())
                        velocity.m_velocity += forward * speed;
                }

                transform.m_position += velocity.m_velocity * deltaTime;

                auto& sprite = entity->getComponent<CSprite>();
                float w = sprite.m_texture->getSize().x * transform.m_scale.x;
                float h = sprite.m_texture->getSize().y * transform.m_scale.y;
                
                if (entity->hasComponent<CBoundingBox>())
                {
                    auto& bb = entity->getComponent<CBoundingBox>();
                    bb.m_min = transform.m_position;
                    bb.m_max = { transform.m_position.x + w,
                                 transform.m_position.y + h };
                }
            }


            if (entity->hasComponent<CBulletTag>())
            {
                transform.m_position += velocity.m_velocity * deltaTime;

                auto& life = entity->getComponent<CLifetime>();
                life.m_time -= deltaTime;

                if (entity->hasComponent<CBoundingBox>() &&
                    entity->hasComponent<CSprite>())
                {
                    auto& bb = entity->getComponent<CBoundingBox>();
                    auto& sprite = entity->getComponent<CSprite>();

                    float w = sprite.m_texture->getSize().x * transform.m_scale.x;
                    float h = sprite.m_texture->getSize().y * transform.m_scale.y;

                    bb.m_min = transform.m_position;
                    bb.m_max = { transform.m_position.x + w,
                                 transform.m_position.y + h };
                }

                if (life.m_time <= 0.f && m_timeEnabled)
                    entity->destroy();
            }

            if (entity->hasComponent<CEnemyTag>())
            {
                transform.m_position += velocity.m_velocity * deltaTime;

                auto& life = entity->getComponent<CLifetime>();
                life.m_time -= deltaTime;

                if (entity->hasComponent<CBoundingBox>() &&
                    entity->hasComponent<CSprite>())
                {
                    auto& bb = entity->getComponent<CBoundingBox>();
                    auto& sprite = entity->getComponent<CSprite>();

                    float w = sprite.m_texture->getSize().x * transform.m_scale.x;
                    float h = sprite.m_texture->getSize().y * transform.m_scale.y;

                    bb.m_min = transform.m_position;
                    bb.m_max = { transform.m_position.x + w,
                                 transform.m_position.y + h };
                }

                if (life.m_time <= 0.f && m_timeEnabled)
                    entity->destroy();
            }
        }
    }
}

void MovementSystem::setTimeEnabled(bool enabled)
{
    m_timeEnabled = enabled;
}

void MovementSystem::setMovementEnabled(bool enabled)
{
    m_movementEnabled = enabled;
}