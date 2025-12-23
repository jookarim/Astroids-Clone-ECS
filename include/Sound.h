#pragma once

#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <string_view>

class AssetManager;

class Sound
{
private:
	Mix_Chunk* m_sound = nullptr;
	
	void loadSound(std::string_view path);
	
	Sound(std::string_view path);

	friend class AssetManager;
public:
	~Sound();
	Mix_Chunk* getSound() const;

};