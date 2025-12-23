#include "SceneGame.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Input.h"
#include "AssetManager.h"
#include "Components.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "Timer.h"

SceneGame::SceneGame(Window& window)
    : m_window(window)
{
    auto* physics = m_systems.addSystem<PhysicsSystem>("Physics", m_entities, m_window);
    auto* movement = m_systems.addSystem<MovementSystem>("Movement", m_entities, m_actions, m_window);
    m_systems.addSystem<RenderSystem>("Render", m_entities, m_window);
    auto* audio = m_systems.addSystem<AudioSystem>("Audio", m_actions, *physics);
    m_systems.addSystem<LivesSystem>("Lives", *physics, m_entities);
    m_systems.addSystem<ScoreSystem>("Score", m_entities, *physics);

    m_gui = std::make_unique<Gui>(*this, m_entities, *movement, *physics, *audio);

    init();
}

void SceneGame::createEntities()
{
    auto background = m_entities.addEntity("Background");

    background->addComponent<CTransform>(Vec2f{ 0.f, 0.f }, 0.f, Vec2f{ 1.41f, 1.47f });

    background->addComponent<CSprite>(
        AssetManager::getInstance().getTexture(
            "assets/images/background.png"
        )
    );

    background->addComponent<CBackgroundTag>();


    auto player = m_entities.addEntity("Player");

    player->addComponent<CTransform>(
        Vec2f(static_cast<float>(m_window.getWidth() / 2.f), static_cast<float>(m_window.getHeight() / 2.f)),
        0.f,
        Vec2f(0.5f, 0.5f)
    );

    player->addComponent<CSprite>(
        AssetManager::getInstance().getTexture(
            "assets/images/spaceship.png"
        )
    );

    player->addComponent<CVelocity>(Vec2f(0.f, 0.f));
    player->addComponent<CBoundingBox>();
    player->addComponent<CPlayerTag>();

    auto enemySpawner = m_entities.addEntity("EnemySpawner");

    enemySpawner->addComponent<CTimer>(0.f, m_gui->getSpawnRate());
    enemySpawner->addComponent<CEnemySpawnerTag>();
    auto lives = m_entities.addEntity("Lives");
    
    lives->addComponent<CTransform>(
        Vec2f{ 20.f, 20.f },
        0.f,
        Vec2f{ 0.02f, 0.02f }
    );
    lives->addComponent<CSprite>(
        AssetManager::getInstance().getTexture("assets/images/heart.png")
    );
    
    lives->addComponent<CLive>(10);
    
    auto scoreText = m_entities.addEntity("Score");
    scoreText->addComponent<CTransform>(Vec2f{ 20.f, 80.f }, 0.f, Vec2f{ 1.f, 1.f });
    scoreText->addComponent<CText>(
        "Score: 0",
        AssetManager::getInstance().getText("assets/fonts/arial.ttf")->getFont(),
        SDL_Color{ 255,255,255,255 }
    );
    scoreText->addComponent<CScore>();
}

void SceneGame::bindActions()
{
    m_actions.clearActions();

    m_actions.bindKey(SDLK_w, "MoveUp");
    m_actions.bindKey(SDLK_s, "MoveDown");
    m_actions.bindKey(SDLK_UP, "MoveUp");
    m_actions.bindKey(SDLK_DOWN, "MoveDown");
    m_actions.bindKey(SDLK_e, "RotateRight");
    m_actions.bindKey(SDLK_q, "RotateLeft");
    m_actions.bindKey(SDLK_RIGHT, "RotateRight");
    m_actions.bindKey(SDLK_LEFT, "RotateLeft");
    m_actions.bindKey(SDLK_SPACE, "Shoot");
    m_actions.bindKey(SDLK_m, "Mute");
}

void SceneGame::init()
{     
    createEntities();  
    bindActions();
}


void SceneGame::handleEvents()
{
    Input::beginFrame();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        {
            m_running = false;
            m_state = GameState::Exit;
            return;
        }
        if (event.type == SDL_KEYDOWN && !event.key.repeat)
            Input::onKeyDown(event.key.keysym.sym);
        if (event.type == SDL_KEYUP)
            Input::onKeyUp(event.key.keysym.sym);
    }
}

void SceneGame::update()
{
    m_actions.update();
    Timer::update();
    float delta = Timer::getDeltaTime();

    for (auto& e : m_entities.getEntities("EnemySpawner"))
    {
        auto& timer = e->getComponent<CTimer>();

        timer.time += delta;

        if (timer.time >= timer.interval)
        {
            spawnEnemy();
            timer.time -= timer.interval;
        }
    }

    for (auto& action : m_actions.getActions())
    {
        if (action.getName() == "Shoot" && action.isPressed())
        {
            spawnBullet();
        }
    }

    m_systems.update(delta);
    m_entities.update();

    for (auto& e : m_entities.getEntities("Lives"))
    {
        if (!e->hasComponent<CLive>())
            continue;

        auto& lives = e->getComponent<CLive>();

        if (lives.m_lives <= 0)   
        {
            m_state = GameState::GameOver;
            break;
        }
    }

    bool isPlayer = false;

    for (auto& e : m_entities.getEntities())
    {
        if (e->getTag() == "Player") isPlayer = true;
    }

    if (!isPlayer) m_state = GameState::GameOver;
    m_actions.clearActions();
}

void SceneGame::render()
{
    m_window.clear();

    m_systems.render();
    m_gui->render();

    m_window.present();
}

void SceneGame::spawnBullet()
{
    auto player = m_entities.getEntities("Player")[0];
    auto bullet = m_entities.addEntity("Bullet");

    auto& pt = player->getComponent<CTransform>();
    auto& ps = player->getComponent<CSprite>();

    float rad = (pt.m_rotation - 90.f) * 3.14159265f / 180.f;

    Vec2f dir{
        cos(rad),
        sin(rad)
    };

    float shipW = ps.m_texture->getSize().x * pt.m_scale.x;
    float shipH = ps.m_texture->getSize().y * pt.m_scale.y;

    Vec2f shipCenter = pt.m_position + Vec2f(shipW * 0.5f, shipH * 0.5f);

    Vec2f nosePos = shipCenter + dir * (shipH * 0.5f);

    auto bulletTex =
        AssetManager::getInstance().getTexture("assets/images/bullet.png");

    Vec2f bulletScale{ 0.3f, 0.3f };
    float bulletW = bulletTex->getSize().x * bulletScale.x;
    float bulletH = bulletTex->getSize().y * bulletScale.y;

    Vec2f spawnPos = nosePos - Vec2f(bulletW * 0.5f, bulletH * 0.5f);

    bullet->addComponent<CTransform>(
        spawnPos,
        pt.m_rotation,
        bulletScale
    );

    bullet->addComponent<CVelocity>(dir * 600.f);

    bullet->addComponent<CSprite>(bulletTex);
    bullet->addComponent<CBoundingBox>();
    bullet->addComponent<CBulletTag>();
    bullet->addComponent<CLifetime>(2.f);
}

void SceneGame::spawnEnemy(bool canSpawnNotSpawnEnabled)
{
    if (m_gui->isSpawningEnabled() || canSpawnNotSpawnEnabled)
    {
        auto enemy = m_entities.addEntity("Enemy");

        auto enemyTex = AssetManager::getInstance().getTexture("assets/images/enemy.png");

        float random = 0.35f + (rand() / (float)RAND_MAX) * 0.3f;
        Vec2f enemyScale{ random, random };

        float enemyW = enemyTex->getSize().x * enemyScale.x;
        float enemyH = enemyTex->getSize().y * enemyScale.y;

        float x = static_cast<float>(
            rand() % (m_window.getWidth() - static_cast<int>(enemyW))
            );

        float y = -enemyH;

        float angDeg = 45.f + static_cast<float>(rand() % 90);
        float angRad = angDeg * 3.14159265f / 180.f;

        Vec2f dir{
            cos(angRad),
            sin(angRad)
        };

        float rotation = angDeg + 90.f;
        
        enemy->addComponent<CTransform>(
            Vec2f(x, y),
            rotation,
            enemyScale
        );

        enemy->addComponent<CVelocity>(dir * 120.f);

        enemy->addComponent<CSprite>(enemyTex);
        enemy->addComponent<CBoundingBox>();
        enemy->addComponent<CEnemyTag>();
        enemy->addComponent<CLifetime>(12.f);

        enemy->addComponent<CColor>(
            SDL_Color{
                (Uint8)(rand() % 200 + 30),
                (Uint8)(rand() % 200 + 30),
                (Uint8)(rand() % 200 + 30),
                255
            }
        );

        for (auto& entity : m_entities.getEntities("EnemySpawner"))
        {
            entity->getComponent<CTimer>().interval = m_gui->getSpawnRate();
        }
    }
}
