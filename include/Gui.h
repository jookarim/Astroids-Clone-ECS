#pragma once

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "MovementSystem.h"
#include "PhysicsSystem.h"
#include "AudioSystem.h"

class SceneGame;

class Gui
{
private:
    void init(SDL_Renderer* renderer, SDL_Window* window);
    void SetImGuiDarkStyleMode();

    SceneGame& m_game;            
    SDL_Renderer* m_renderer = nullptr;
    SDL_Window* m_window = nullptr;

    ImFont* m_smallFont = nullptr;

    bool movement = true;
    bool lifeSpan = true;
    bool collision = true;
    bool spawning = true;
    float spawnRate = 1.f;

    EntityManager& m_entityManager;
    MovementSystem& m_movementSystem;
    PhysicsSystem& m_physicsSystem;
    AudioSystem& m_audioSystem;
public:
    Gui(SceneGame& game, EntityManager& entityManager, MovementSystem& movementSystem, PhysicsSystem& physicsSystem, AudioSystem& audioSystem);
    ~Gui();

    bool  isMovementEnabled()  const { return movement; }
    bool  isLifeSpanEnabled()  const { return lifeSpan; }
    bool  isCollisionEnabled() const { return collision; }
    bool  isSpawningEnabled()  const { return spawning; }
    float getSpawnRate()       const { return spawnRate; }

    void render();
};
