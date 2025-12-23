#include "Texture.h"

void Texture::loadTexture(SDL_Renderer* renderer, std::string_view path)
{
	SDL_Surface* surface = IMG_Load(path.data());
	if (!surface)
	{
		std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
		return;
	}
	m_texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!m_texture)
	{
		std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(surface);
		return;
	}
	m_size.x = surface->w;
	m_size.y = surface->h;
	SDL_FreeSurface(surface);
}

Texture::Texture(SDL_Renderer* renderer, const std::string& path)
	: m_texture(nullptr), m_size({0, 0}), m_path(path)
{
	loadTexture(renderer, path);
}

Texture::~Texture()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
	}
}

SDL_Texture* Texture::getTexture() const
{
	return m_texture;
}

std::string_view Texture::getPath() const
{
	return m_path;
}

const Vec2i& Texture::getSize() const
{
	return m_size;
}