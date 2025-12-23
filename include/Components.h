#pragma once

#include <memory>
#include "Vec2.h"
#include "Texture.h"
#include "Text.h"

struct Component
{
    bool m_exists = false; 
    bool m_alive = false;

    virtual ~Component() = default;
};

struct CTransform : public Component
{
    Vec2f m_position;
    float m_rotation;
    Vec2f m_scale;

    CTransform()
        : m_position(0.f, 0.f),
        m_rotation(0.f),
        m_scale(1.f, 1.f)
    {
    }

    explicit CTransform(const Vec2f& pos, float rot = 0.f, const Vec2f& scale = { 1.f, 1.f })
        : m_position(pos),
        m_rotation(rot),
        m_scale(scale)
    {
        m_exists = true;
        m_alive = true;
    }
};

struct CSprite : public Component
{
    std::shared_ptr<Texture> m_texture;

    CSprite() = default;

    explicit CSprite(const std::shared_ptr<Texture>& texture)
        : m_texture(texture)
    {
        m_exists = true;
        m_alive = true;
    }
};

struct CBoundingBox : public Component
{
    Vec2f m_min;
    Vec2f m_max;

    CBoundingBox()
        : m_min(0.f, 0.f), m_max(0.f, 0.f)
    {
    }

    explicit CBoundingBox(const Vec2f& min, const Vec2f& max)
        : m_min(min), m_max(max)
    {
        m_exists = true;
        m_alive = true;
    }
};

struct CVelocity : public Component
{
    Vec2f m_velocity;

    CVelocity()
        : m_velocity(0.f, 0.f)
    {
    }

    explicit CVelocity(const Vec2f& vel)
        : m_velocity(vel)
    {
        m_exists = true;
        m_alive = true;
    }
};

struct CPlayerTag : public Component
{
    CPlayerTag() = default;
};

struct CBackgroundTag : public Component
{
    CBackgroundTag() = default;
};

struct CBulletTag : public Component
{
    CBulletTag() = default;
};

struct CLifetime : public Component
{
    float m_time = 0.f;

    CLifetime() = default;

    CLifetime(float time)
        : m_time(time)
    {
        m_exists = true;
        m_alive = true;
    }
};

struct CEnemyTag : public Component
{
    CEnemyTag() = default;
};

struct CTimer : public Component
{
    float time;
    float interval;

    explicit CTimer(float t = 0.f, float i = 0.f)
        : time(t), interval(i) {
    }
};


struct CEnemySpawnerTag : public Component
{
    CEnemySpawnerTag() = default;
};

struct CLive : public Component
{
    int m_lives = 3;

    CLive() = default;

    CLive(int l)
        : m_lives(l)
    {
        m_exists = true;
        m_alive = true;
    }
};

struct CText : public Component
{
    std::string m_text;
    SDL_Color   m_color;
    TTF_Font* m_font = nullptr;

    CText() = default;

    explicit CText(const std::string& text,
        TTF_Font* font,
        SDL_Color color = { 255,255,255,255 })
        : m_text(text), m_color(color), m_font(font)
    {
        m_exists = true;
        m_alive = true;
    }
};

struct CScore : public Component
{
    int m_score = 0;

    CScore() = default;

    explicit CScore(int score) : m_score(score)
    {
        m_alive = true;
        m_exists = true;
    }
};

struct CColor : public Component
{
    SDL_Color m_color = {};
    CColor() = default;

    explicit CColor(const SDL_Color& color) : m_color(color)
    {
        m_alive = true;
        m_exists = true;
    }
};

struct CButtonTag : public Component
{
    CButtonTag() = default;
};

struct CStartButtonTag : public Component
{
    CStartButtonTag() = default;
};

struct CExitButtonTag : public Component
{
    CExitButtonTag() = default;
};
