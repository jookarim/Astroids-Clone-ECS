#include "Action.h"

Action::Action(const std::string& name, ActionType type)
    : m_name(name), m_type(type)
{
}

std::string_view Action::getName() const
{
    return m_name;
}

ActionType Action::getType() const
{
    return m_type;
}

bool Action::isPressed() const
{
    return m_type == ActionType::Pressed;
}

bool Action::isReleased() const
{
    return m_type == ActionType::Released;
}

bool Action::isDown() const
{
    return m_type == ActionType::Pressed ||
        m_type == ActionType::Held;
}
