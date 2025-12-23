#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <string_view>
#include "AssetManager.h"

class Window
{
private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    std::string   m_title;
    int           m_width = 0;
    int           m_height = 0;
    bool          m_running = true;

public:
    Window() = default;
    Window(std::string_view title, int width, int height);
    ~Window();

    bool isRunning() const;

    void pollEvents();
    void clear();
    void present();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;

    void setWindowIcon(std::string_view path);
};
