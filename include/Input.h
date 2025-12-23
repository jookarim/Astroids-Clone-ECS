#pragma once
#include <map>

enum class KeyState
{
    None,
    Pressed,
    Held,
    Released
};

class Input
{
private:
    static std::map<int, KeyState> m_keys;

public:
    static void beginFrame();

    static void onKeyDown(int key);
    static void onKeyUp(int key);

    static void reset();
    static bool isPressed(int key);
    static bool isDown(int key);      
    static bool isReleased(int key);
};
