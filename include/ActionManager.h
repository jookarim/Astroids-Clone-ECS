#pragma once

#include <map>
#include <vector>
#include <string>

#include "Action.h"
#include "Input.h"

class ActionManager
{
private:
    std::map<int, std::string> m_keyBindings;
    std::vector<Action> m_actions;
public:
    ActionManager() = default;
    void bindKey(int key, const std::string& actionName);
    void update();
    const std::vector<Action>& getActions() const;
    void clearActions();
};
