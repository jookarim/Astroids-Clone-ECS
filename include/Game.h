#pragma once

#include <memory>
#include "Window.h"
#include "AssetManager.h"

#include "SceneStart.h"
#include "SceneGame.h"
#include "SceneRestart.h"

enum class ActiveScene
{
    Start,
    Game,
    Restart,
};

class Game
{
private:
    Window m_window;

    std::unique_ptr<SceneStart>   m_sceneStart;
    std::unique_ptr<SceneGame>    m_sceneGame;
    std::unique_ptr<SceneRestart> m_sceneRestart;

    ActiveScene m_activeScene = ActiveScene::Start;
    bool m_running = true;   

private:
    void loadAssets();

    void updateStartScene();
    void updateGameScene();
    void updateRestartScene();

public:
    Game();
    void run();
};
