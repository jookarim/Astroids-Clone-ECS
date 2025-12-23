#pragma once

#include <vector>
#include <map>
#include <memory>
#include <string>
#include <string_view>

#include "System.h"
#include "Gui.h"

class SystemManager
{
private:
    std::vector<std::shared_ptr<System>> m_systems;
    std::map<std::string, System*> m_systemsByName;

public:
    template<typename T, typename... Args>
    T* addSystem(std::string_view name, Args&&... args)
    {
        auto system = std::make_shared<T>(std::forward<Args>(args)...);
        T* ptr = system.get();

        m_systems.push_back(system);
        m_systemsByName.emplace(name, ptr);

        return ptr;
    }

    void update(float dt)
    {
        for (auto& s : m_systems)
        {
            s->update(dt);
        }
    }

    void render()
    {
        for (auto& s : m_systems)
        {
            s->render();
        }
    }

    System* getSystemByName(std::string_view name)
    {
        auto it = m_systemsByName.find(std::string(name));
        if (it != m_systemsByName.end())
            return it->second;

        return nullptr;
    }

    const std::vector<std::shared_ptr<System>>& getSystems() const
    {
        return m_systems;
    }

    void clear()
    {
        m_systemsByName.clear();
        m_systems.clear();
    }
};
