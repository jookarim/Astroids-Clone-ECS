#pragma once

#include <iostream>
#include <string_view>
#include <SDL2/SDL_mixer.h>

class AssetManager;

class Music
{
private:
	Mix_Music* m_music = nullptr;

	Music(std::string_view path);

	void loadMusic(std::string_view path);

	friend class AssetManager;
public:
	~Music();

	Mix_Music* getMusic() const { return m_music; }
};

