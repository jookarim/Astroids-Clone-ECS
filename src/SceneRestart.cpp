#include "SceneRestart.h"
#include "AssetManager.h"
#include "RenderSystem.h"
#include "Collision.h"
#include <SDL2/SDL.h>


void SceneRestart::createSystems()
{
    m_systems.addSystem<RenderSystem>("Render", m_entities, m_window);
    m_physicsSystem = m_systems.addSystem<PhysicsSystem>("Physics", m_entities, m_window);
}

void SceneRestart::createEntities()
{
    auto background = m_entities.addEntity("Background");

    background->addComponent<CTransform>(
        Vec2f{ 0.f, 0.f }, 0.f, Vec2f{ 1.41f, 1.47f });

    background->addComponent<CSprite>(
        AssetManager::getInstance().getTexture("assets/images/background.png"));

    background->addComponent<CBackgroundTag>();

    auto restartBtn = m_entities.addEntity("Restart");

    auto restartTex =
        AssetManager::getInstance().getTexture("assets/images/restart.png");

    Vec2f restartScale{ 0.45f, 0.45f };
    Vec2i restartSize = restartTex->getSize();

    Vec2f restartPos{
        m_window.getWidth() / 2.f - (restartSize.x * restartScale.x) / 2.f,
        m_window.getHeight() / 2.f - (restartSize.y * restartScale.y) / 2.f - 80.f
    };

    restartBtn->addComponent<CSprite>(restartTex);
    restartBtn->addComponent<CTransform>(restartPos, 0.f, restartScale);

    Vec2f startBBSize{
        restartSize.x * restartScale.x,
        restartSize.y * restartScale.y
    };

    restartBtn->addComponent<CBoundingBox>(
        restartPos,
        restartPos + startBBSize
    );

    restartBtn->addComponent<CButtonTag>();
    restartBtn->addComponent<CStartButtonTag>();

    auto exitBtn = m_entities.addEntity("Exit");

    auto exitTex =
        AssetManager::getInstance().getTexture("assets/images/exit.png");

    Vec2f exitScale{ 0.45f, 0.45f };
    Vec2i exitSize = exitTex->getSize();

    Vec2f exitPos{
        m_window.getWidth() / 2.f - (exitSize.x * exitScale.x) / 2.f,
        m_window.getHeight() / 2.f - (exitSize.y * exitScale.y) / 2.f + 80.f
    };

    exitBtn->addComponent<CSprite>(exitTex);
    exitBtn->addComponent<CTransform>(exitPos, 0.f, exitScale);

    Vec2f exitBBSize{
        exitSize.x * exitScale.x,
        exitSize.y * exitScale.y
    };

    exitBtn->addComponent<CBoundingBox>(
        exitPos,
        exitPos + exitBBSize
    );

    exitBtn->addComponent<CButtonTag>();
    exitBtn->addComponent<CExitButtonTag>();
}

void SceneRestart::init()
{
    createSystems();
    createEntities();

    m_entities.update();
}

SceneRestart::SceneRestart(Window& window)
    : m_window(window)
{
    init();
}

void SceneRestart::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_state = GameState::Exit;
        }
    }
}

void SceneRestart::update()
{
    float dt = Timer::getDeltaTime();

    m_systems.update(dt);

    if (m_physicsSystem->getStartPressed())
    {
        m_state = GameState::StartGame;
    }

    if (m_physicsSystem->getExitPressed())
    {
        m_state = GameState::Exit;
    }
}

void SceneRestart::render()
{
    m_window.clear();
    m_systems.render();
    m_window.present();
}
