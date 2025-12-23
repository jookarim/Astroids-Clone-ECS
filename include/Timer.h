#pragma once
#include <SDL2/SDL.h>

class Timer
{
private:
    static Uint32 m_startTicks;
    static Uint32 m_lastTicks;
    static float  m_deltaTime;

public:
    static void start();
    static void update();
    static void reset();

    static float getDeltaTime();
    static float getElapsedTime();
};
