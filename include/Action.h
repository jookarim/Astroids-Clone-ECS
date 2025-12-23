#pragma once

#include <string>
#include <string_view>

enum class ActionType
{
    Pressed,
    Released,
    Held
};

class Action
{
private:
    std::string m_name;
    ActionType  m_type;

public:
    Action(const std::string& name, ActionType type);

    std::string_view getName() const;
    ActionType getType() const;

    bool isPressed() const;
    bool isReleased() const;

    bool isDown() const;   
};
