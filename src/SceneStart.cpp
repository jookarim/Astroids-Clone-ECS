#include "SceneStart.h"
#include "AssetManager.h"
#include "RenderSystem.h"
#include "Collision.h"
#include <SDL2/SDL.h>


void SceneStart::createSystems()
{
    m_systems.addSystem<RenderSystem>("Render", m_entities, m_window);
    m_physicsSystem = m_systems.addSystem<PhysicsSystem>("Physics", m_entities, m_window);
}

void SceneStart::createEntities()
{
    auto background = m_entities.addEntity("Background");

    background->addComponent<CTransform>(
        Vec2f{ 0.f, 0.f }, 0.f, Vec2f{ 1.41, 1.47f });

    background->addComponent<CSprite>(
        AssetManager::getInstance().getTexture("assets/images/background.png"));

    background->addComponent<CBackgroundTag>();

    auto startBtn = m_entities.addEntity("Start");

    auto startTex =
        AssetManager::getInstance().getTexture("assets/images/start.png");

    Vec2f startScale{ 0.45f, 0.45f };
    Vec2i startSize = startTex->getSize();

    Vec2f startPos{
        m_window.getWidth() / 2.f - (startSize.x * startScale.x) / 2.f,
        m_window.getHeight() / 2.f - (startSize.y * startScale.y) / 2.f - 80.f
    };

    startBtn->addComponent<CSprite>(startTex);
    startBtn->addComponent<CTransform>(startPos, 0.f, startScale);

    Vec2f startBBSize{
        startSize.x * startScale.x,
        startSize.y * startScale.y
    };

    startBtn->addComponent<CBoundingBox>(
        startPos,
        startPos + startBBSize
    );

    startBtn->addComponent<CButtonTag>();
    startBtn->addComponent<CStartButtonTag>();

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

void SceneStart::init()
{
    createSystems();
    createEntities();

    m_entities.update();
}

SceneStart::SceneStart(Window& window)
    : m_window(window)
{
    init();
}

void SceneStart::handleEvents()
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

void SceneStart::update()
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

void SceneStart::render()
{
    m_window.clear();
    m_systems.render();
    m_window.present();
}
