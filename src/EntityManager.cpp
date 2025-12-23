#include "EntityManager.h"
#include <algorithm>

std::shared_ptr<Entity> EntityManager::addEntity(std::string_view tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(tag, m_entityID++));
    m_toAdd.push_back(entity);
    return entity;
}

void EntityManager::removeEntity(std::shared_ptr<Entity> entity)
{
    entity->destroy();
}

const EntityVec& EntityManager::getEntities() const
{
    return m_entities;
}

const EntityVec& EntityManager::getEntities(std::string_view tag) const
{
    static EntityVec empty;

    auto it = m_entityTags.find(std::string(tag));
    if (it != m_entityTags.end())
    {
        return it->second;
    }
    return empty;
}

void EntityManager::update()
{
    for (auto& entity : m_toAdd)
    {
        m_entities.push_back(entity);
        m_entityTags[std::string(entity->getTag())].push_back(entity);
    }
    m_toAdd.clear();

    m_entities.erase(
        std::remove_if(
            m_entities.begin(),
            m_entities.end(),
            [&](const std::shared_ptr<Entity>& entity)
            {
                if (!entity->isAlive())
                {
                    auto& vec = m_entityTags[std::string(entity->getTag())];
                    vec.erase(std::remove(vec.begin(), vec.end(), entity), vec.end());
                    return true;
                }
                return false;
            }
        ),
        m_entities.end()
    );
}

