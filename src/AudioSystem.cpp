#include "AudioSystem.h"
#include "AssetManager.h"
#include <SDL2/SDL_mixer.h>
#include "ActionManager.h"

AudioSystem::AudioSystem(ActionManager& actions, PhysicsSystem& physics)
    : m_actions(actions), m_physics(physics)
{
}

void AudioSystem::update(float dt)
{
    if (!m_musicStarted)
    {
        auto music =
            AssetManager::getInstance().getMusic("assets/sounds/game_music.mp3");

        if (music)
        {
            Mix_VolumeMusic(128);

            if (!Mix_PlayingMusic())
            {
                Mix_PlayMusic(music->getMusic(), -1);
            }

            m_musicStarted = true;
        }
    }


    if (m_audioDisabled)
    {
        Mix_PauseMusic();
        Mix_Volume(-1, 0);
    }
    else
    {
        Mix_ResumeMusic();
        Mix_Volume(-1, 128);
    }

    for (const auto& action : m_actions.getActions())
    {
        if (action.getName() == "Mute" && action.isPressed())
        {
            m_audioDisabled = !m_audioDisabled;

            if (m_audioDisabled)
            {
                Mix_PauseMusic();       
                Mix_Volume(-1, 0);      
            }
            else
            {
                Mix_ResumeMusic();        
                Mix_Volume(-1, 128);      
            }
        }

        if (!m_audioDisabled &&
            action.getName() == "Shoot" &&
            action.isPressed())
        {
            auto sound =
                AssetManager::getInstance().getSound("assets/sounds/laser.mp3");

            if (sound)    
            {
                Mix_VolumeChunk(sound->getSound(), 32);
                Mix_PlayChannel(-1, sound->getSound(), 0);
            }
        }
    }

    if (!m_audioDisabled &&
        (m_physics.getState().enemyHit || m_physics.getState().playerHit))
    {
        auto sound =
            AssetManager::getInstance().getSound("assets/sounds/boom.wav");

        if (sound)
        {
            Mix_VolumeChunk(sound->getSound(), 64);
            Mix_PlayChannel(-1, sound->getSound(), 0);
        }
    }
}
  