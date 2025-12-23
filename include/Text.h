#pragma once

#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <string_view>

class AssetManager;

class Text
{
private:
	TTF_Font* m_font = nullptr;

	void loadFont(std::string_view path);

	Text(std::string_view path);
	
	friend class AssetManager;
public:
	~Text();

	TTF_Font* getFont() const
	{
		return m_font;
	}

};

