#include "Input.h"

std::map<int, KeyState> Input::m_keys;

void Input::beginFrame()
{
    for (auto& [key, state] : m_keys)
    {
        if (state == KeyState::Pressed)
            state = KeyState::Held;
        else if (state == KeyState::Released)
            state = KeyState::None;
    }
}

void Input::onKeyDown(int key)
{
    auto& state = m_keys[key];

    if (state == KeyState::None)
        state = KeyState::Pressed;
}

void Input::onKeyUp(int key)
{
    m_keys[key] = KeyState::Released;
}

bool Input::isPressed(int key)
{
    auto it = m_keys.find(key);
    return it != m_keys.end() &&
        it->second == KeyState::Pressed;
}

bool Input::isDown(int key)
{
    auto it = m_keys.find(key);
    return it != m_keys.end() &&
        (it->second == KeyState::Pressed ||
            it->second == KeyState::Held);
}

bool Input::isReleased(int key)
{
    auto it = m_keys.find(key);
    return it != m_keys.end() &&
        it->second == KeyState::Released;
}

void Input::reset()
{
    m_keys.clear();
}