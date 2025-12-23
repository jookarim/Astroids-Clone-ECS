#include "ActionManager.h"

void ActionManager::bindKey(int key, const std::string& actionName)
{
    m_keyBindings[key] = actionName;
}

void ActionManager::update()
{
    m_actions.clear();

    for (const auto& [key, actionName] : m_keyBindings)
    {
        if (Input::isPressed(key))
        {
            m_actions.emplace_back(actionName, ActionType::Pressed);
        }
        else if (Input::isDown(key))
        {
            m_actions.emplace_back(actionName, ActionType::Held);
        }
        else if (Input::isReleased(key))
        {
            m_actions.emplace_back(actionName, ActionType::Released);
        }
    }
}


const std::vector<Action>& ActionManager::getActions() const
{
    return m_actions;
}

void ActionManager::clearActions()
{
    m_actions.clear();
}
