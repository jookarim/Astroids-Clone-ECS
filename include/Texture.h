#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vec2.h"
#include <memory>

class AssetManager;

class Texture
{
private:
	SDL_Texture* m_texture;
	Vec2i m_size;
	std::string m_path;
	
	void loadTexture(SDL_Renderer* renderer, std::string_view path);

	Texture(SDL_Renderer* renderer, const std::string& path);

	friend class AssetManager;
public:
	~Texture();
	SDL_Texture* getTexture() const;
	const Vec2i& getSize() const;
	std::string_view getPath() const;
};

