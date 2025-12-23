#include "Renderer.h"

void Renderer::drawTexture(
    const Window& window,
    const Texture& texture,
    const Vec2f& position,
    const Vec2f& scale,
    float rotation
)
{
    SDL_Rect dst{
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        static_cast<int>(texture.getSize().x * scale.x),
        static_cast<int>(texture.getSize().y * scale.y)
    };

    SDL_Point center{
        dst.w / 2,
        dst.h / 2
    };

    SDL_RenderCopyEx(
        window.getRenderer(),
        texture.getTexture(),
        nullptr,
        &dst,
        rotation,
        &center,
        SDL_FLIP_NONE
    );
}

void Renderer::drawRect(const Window& window, const Vec2f& position, const Vec2i& size, const SDL_Color& color)
{
    SDL_Rect dst{
       static_cast<int>(position.x),
       static_cast<int>(position.y),
       static_cast<int>(size.x),
       static_cast<int>(size.y)
    };

    SDL_SetRenderDrawColor(window.getRenderer(), color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(window.getRenderer(), &dst);
}