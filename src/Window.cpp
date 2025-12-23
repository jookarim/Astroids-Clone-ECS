#include "Window.h"
#include <iostream>

Window::Window(std::string_view title, int width, int height)
    : m_title(title), m_width(width), m_height(height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        m_running = false;
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer Error: " << Mix_GetError() << std::endl;
        m_running = false;
        return;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
    {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        m_running = false;
        return;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        m_running = false;
        return;
    }

    m_window = SDL_CreateWindow(
        std::string(title).c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!m_window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        m_running = false;
        return;
    }

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!m_renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        m_running = false;
    }
}

Window::~Window()
{
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();

    AssetManager::getInstance().shutDown();

    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window)   SDL_DestroyWindow(m_window);

    SDL_Quit();
}


bool Window::isRunning() const
{
    return m_running;
}

void Window::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_running = false;
        }
    }
}

void Window::clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Window::present()
{
    SDL_RenderPresent(m_renderer);
}

SDL_Window* Window::getWindow() const
{
    return m_window;
}

SDL_Renderer* Window::getRenderer() const
{
    return m_renderer;
}

void Window::setWindowIcon(std::string_view path)
{
    SDL_Surface* icon = IMG_Load(std::string(path).c_str());
    if (!icon)
    {
        std::cerr << "Failed to load icon: " << IMG_GetError() << '\n';
        return;
    }

    SDL_SetWindowIcon(m_window, icon);
    SDL_FreeSurface(icon);
}
