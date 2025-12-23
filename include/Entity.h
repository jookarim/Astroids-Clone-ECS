#pragma once

#include <string>
#include <string_view>
#include <tuple>
#include <cstdint>
#include <type_traits>

#include "Components.h"

using ComponentTuple = std::tuple<
    CTransform,
    CVelocity,
    CSprite,
    CBoundingBox,
    CPlayerTag,
    CBackgroundTag,
    CBulletTag,
    CLifetime,
    CTimer,
    CEnemySpawnerTag,
    CEnemyTag,
    CLive,
    CText,
    CScore,
    CColor,
    CButtonTag,
    CStartButtonTag,
    CExitButtonTag
>;


class EntityManager;

class Entity
{
private:
    std::string     m_tag;
    uint32_t        m_id = 0;
    bool            m_alive = true;
    ComponentTuple  m_components;

    Entity(std::string_view tag, uint32_t id)
        : m_tag(tag), m_id(id)
    {
    }

    friend class EntityManager;

public:
    ~Entity() = default;

    std::string_view getTag() const { return m_tag; }
    uint32_t getID() const { return m_id; }
    bool isAlive() const { return m_alive; }

    void destroy()
    {
        m_alive = false;
    }

    template<typename T>
    bool hasComponent() const
    {
       
        return std::get<T>(m_components).m_exists;
    }

    template<typename T>
    T& getComponent()
    {
        auto& comp = std::get<T>(m_components);
        return comp;
    }

    template<typename T, typename... Args>
    void addComponent(Args&&... args)
    {
        auto& comp = std::get<T>(m_components);
        comp = T(std::forward<Args>(args)...);
        comp.m_exists = true;

        if constexpr (std::is_same_v<T, CBoundingBox>)
        {
            auto& t = std::get<CTransform>(m_components);
            auto& s = std::get<CSprite>(m_components);

            const float w = s.m_texture->getSize().x * t.m_scale.x;
            const float h = s.m_texture->getSize().y * t.m_scale.y;

            comp.m_min = t.m_position;
            comp.m_max = {
                t.m_position.x + w,
                t.m_position.y + h
            };
        }
    }

    template<typename T>
    void removeComponent()
    {
        auto& comp = std::get<T>(m_components);
        comp = T{};
        comp.m_exists = false;
    }
};
