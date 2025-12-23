#include "RenderSystem.h"
#include "Renderer.h"
#include <SDL2/SDL_ttf.h>

RenderSystem::RenderSystem(EntityManager& entityManager, Window& window)
    : m_entityManager(entityManager)
    , m_window(window)
{
}

void RenderSystem::render()
{
    m_enemyVA.clear();
    m_bulletVA.clear();
    m_enemyRectVA.clear();

    SDL_Texture* enemyTexture = nullptr;
    SDL_Texture* bulletTexture = nullptr;
    
    for (auto& entity : m_entityManager.getEntities())
    {
        if (!entity->hasComponent<CTransform>())
            continue;

        const auto& transform = entity->getComponent<CTransform>();

        if (entity->hasComponent<CText>())
        {
            const auto& text = entity->getComponent<CText>();
            if (!text.m_font || !text.m_alive)
                continue;

            SDL_Surface* surface =
                TTF_RenderText_Blended(
                    text.m_font,
                    text.m_text.c_str(),
                    text.m_color
                );

            SDL_Texture* texture =
                SDL_CreateTextureFromSurface(
                    m_window.getRenderer(),
                    surface
                );

            SDL_FreeSurface(surface);
            if (!texture)
                continue;

            int w, h;
            SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

            SDL_Rect dst{
                (int)transform.m_position.x,
                (int)transform.m_position.y,
                (int)(w * transform.m_scale.x),
                (int)(h * transform.m_scale.y)
            };

            SDL_RenderCopy(
                m_window.getRenderer(),
                texture,
                nullptr,
                &dst
            );

            SDL_DestroyTexture(texture);

            if (entity->hasComponent<CScore>())
            {
                entity->getComponent<CText>().m_text =
                    "Score: " + std::to_string(
                        entity->getComponent<CScore>().m_score
                    );
            }
            continue;
        }

        if (!entity->hasComponent<CSprite>())
            continue;

        const auto& sprite = entity->getComponent<CSprite>();

        if (entity->getTag() == "Bullet")
        {
            if (!bulletTexture)
                bulletTexture = sprite.m_texture->getTexture();

            m_bulletVA.pushQuad(
                transform.m_position.x,
                transform.m_position.y,
                sprite.m_texture->getSize().x * transform.m_scale.x,
                sprite.m_texture->getSize().y * transform.m_scale.y,
                transform.m_rotation * 3.14159265f / 180.f,
                { 255, 255, 255, 255 }
            );

            continue;
        }

        if (entity->getTag() == "Enemy")
        {
            if (!enemyTexture)
                enemyTexture = sprite.m_texture->getTexture();

            m_enemyVA.pushQuad(
                transform.m_position.x,
                transform.m_position.y,
                sprite.m_texture->getSize().x * transform.m_scale.x,
                sprite.m_texture->getSize().y * transform.m_scale.y,
                0.f,
                { 255, 255, 255, 255 }
            );

            Vec2i enemyScale = { 10, 10 };

            SDL_Color enemyColor = { 255, 255, 255, 255 };
            if (entity->hasComponent<CColor>())
            {
                enemyColor = entity->getComponent<CColor>().m_color;
            }

            m_enemyRectVA.pushQuad(
                transform.m_position.x - (enemyScale.x / 2),
                transform.m_position.y - 5.f,
                (float)enemyScale.x,
                (float)enemyScale.y,
                0.f,
                enemyColor
            );

            continue;
        }

        if (entity->hasComponent<CLive>())
        {
            const auto& lives = entity->getComponent<CLive>();
            Vec2f pos = transform.m_position;

            for (int i = 0; i < lives.m_lives; ++i)
            {
                Renderer::drawTexture(
                    m_window,
                    *sprite.m_texture,
                    pos,
                    transform.m_scale,
                    0.f
                );
                pos.x += 20.f;
            }
            continue;
        }

        Renderer::drawTexture(
            m_window,
            *sprite.m_texture,
            transform.m_position,
            transform.m_scale,
            transform.m_rotation
        );
    }

    m_bulletVA.draw(m_window.getRenderer(), bulletTexture);
    m_enemyVA.draw(m_window.getRenderer(), enemyTexture);
    m_enemyRectVA.draw(m_window.getRenderer(), nullptr);
}