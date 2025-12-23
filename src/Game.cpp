#include "Game.h"
#include "Timer.h"
#include "Input.h"

#include <SDL2/SDL_mixer.h>

Game::Game()
    : m_window("Astroids Clone", 1270, 820)
{
    m_window.setWindowIcon("assets/images/spaceship.png");
    loadAssets();
    Timer::start();

    m_sceneStart = std::make_unique<SceneStart>(m_window);
    m_activeScene = ActiveScene::Start;

    Mix_PlayMusic(AssetManager::getInstance().getMusic("assets/sounds/game_music.mp3")->getMusic(), -1);

}

void Game::loadAssets()
{
    auto& assets = AssetManager::getInstance();
    auto* renderer = m_window.getRenderer();

    assets.addTexture(renderer, "assets/images/background.png");
    assets.addTexture(renderer, "assets/images/start.png");
    assets.addTexture(renderer, "assets/images/exit.png");
    assets.addTexture(renderer, "assets/images/restart.png");
    assets.addTexture(renderer, "assets/images/spaceship.png");
    assets.addTexture(renderer, "assets/images/bullet.png");
    assets.addTexture(renderer, "assets/images/enemy.png");
    assets.addTexture(renderer, "assets/images/heart.png");
    assets.addText("assets/fonts/arial.ttf");
    assets.addMusic("assets/sounds/game_music.mp3");
    assets.addMusic("assets/sounds/lose.mp3");
    assets.addSound("assets/sounds/laser.mp3");
    assets.addSound("assets/sounds/boom.wav");
}

void Game::run()
{
    while (m_running && m_window.isRunning())
    {
        if (m_activeScene == ActiveScene::Start)
        {
            updateStartScene();
        }
        else if (m_activeScene == ActiveScene::Game)
        {
            updateGameScene();
        }
        else if (m_activeScene == ActiveScene::Restart)
        {
            updateRestartScene();
        }
    }
}

void Game::updateStartScene()
{
    m_sceneStart->handleEvents();
    m_sceneStart->update();
    m_sceneStart->render();

    if (m_sceneStart->getState() == GameState::StartGame)
    {
        Input::reset();
        Timer::reset();

        m_sceneGame = std::make_unique<SceneGame>(m_window);
        m_sceneStart.reset();

        m_activeScene = ActiveScene::Game;
    }
    else if (m_sceneStart->getState() == GameState::Exit)
    {
        m_running = false;   
    }
}

void Game::updateGameScene()
{
    m_sceneGame->handleEvents();
    m_sceneGame->update();
    m_sceneGame->render();

    if (m_sceneGame->getGameState() == GameState::GameOver)
    {
        Input::reset();
        Timer::reset();

        m_sceneRestart = std::make_unique<SceneRestart>(m_window);
        m_sceneGame.reset();

        Mix_HaltMusic();
        Mix_PlayMusic(
            AssetManager::getInstance()
            .getMusic("assets/sounds/lose.mp3")
            ->getMusic(),
            1
        );

        m_activeScene = ActiveScene::Restart;
    }
    else if (m_sceneGame->getGameState() == GameState::Exit)
    {
        m_running = false;   
    }
}

void Game::updateRestartScene()
{
    m_sceneRestart->handleEvents();
    m_sceneRestart->update();
    m_sceneRestart->render();

    if (m_sceneRestart->getState() == GameState::StartGame)
    {
        Input::reset();
        Timer::reset();

        Mix_HaltMusic();
        Mix_PlayMusic(
            AssetManager::getInstance()
            .getMusic("assets/sounds/game_music.mp3")
            ->getMusic(),
            -1
        );

        m_sceneGame = std::make_unique<SceneGame>(m_window);
        m_sceneRestart.reset();

        m_activeScene = ActiveScene::Game;
    }
    else if (m_sceneRestart->getState() == GameState::Exit)
    {
        m_running = false;   
    }
}
