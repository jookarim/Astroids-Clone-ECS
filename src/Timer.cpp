#include "Timer.h"

Uint32 Timer::m_startTicks = 0;
Uint32 Timer::m_lastTicks = 0;
float  Timer::m_deltaTime = 0.0f;

void Timer::start()
{
    m_startTicks = SDL_GetTicks();
    m_lastTicks = m_startTicks;
    m_deltaTime = 0.0f;
}

void Timer::update()
{
    Uint32 currentTicks = SDL_GetTicks();

    m_deltaTime = (currentTicks - m_lastTicks) / 1000.0f;
    m_lastTicks = currentTicks;
}

float Timer::getDeltaTime()
{
    return m_deltaTime;
}

float Timer::getElapsedTime()
{
    return (SDL_GetTicks() - m_startTicks) / 1000.0f;
}

void Timer::reset()
{
    m_lastTicks = SDL_GetTicks();
    m_deltaTime = 0.0f;
}
