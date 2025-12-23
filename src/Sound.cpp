#include "Sound.h"

Sound::Sound(std::string_view path)
    : m_sound(nullptr)
{
    loadSound(path);
}

void Sound::loadSound(std::string_view path)
{
    m_sound = Mix_LoadWAV(path.data());

    if (!m_sound)
    {
        std::cout << "Failed to load sound: "
            << path
            << " | Error: "
            << Mix_GetError()
            << std::endl;
    }
}

Mix_Chunk* Sound::getSound() const
{
    return m_sound;
}

Sound::~Sound()
{
    if (m_sound)
    {
        Mix_FreeChunk(m_sound);
        m_sound = nullptr;
    }
}
