#pragma once

#include "Window.h"
#include "Texture.h"
#include "Vec2.h"

class Renderer
{
public:
    static void drawTexture(const Window& window, const Texture& texture, const Vec2f& position, const Vec2f& scale, float rotation);
    static void drawRect(const Window& window, const Vec2f& position, const Vec2i& size, const SDL_Color& color);
};
