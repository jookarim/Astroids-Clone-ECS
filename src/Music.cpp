#include "Music.h"

void Music::loadMusic(std::string_view path)
{
	m_music = Mix_LoadMUS(path.data());

	if (!m_music)
	{
		std::cout << "Failed to load sound: "
			<< path
			<< " | Error: "
			<< Mix_GetError()
			<< std::endl;
	}
}

Music::Music(std::string_view path)
{
	loadMusic(path);
}

Music::~Music()
{
	if (m_music)
	{
		Mix_FreeMusic(m_music);
	}
}