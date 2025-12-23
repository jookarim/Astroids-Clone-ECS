#include "Text.h"

void Text::loadFont(std::string_view path)
{
    m_font = TTF_OpenFont(path.data(), 24);

    if (!m_font)
    {
        std::cerr << "Failed to load font: " << path
            << " | TTF_Error: " << TTF_GetError()
            << std::endl;
    }
}

Text::Text(std::string_view path)
{
    loadFont(path);
}

Text::~Text()
{
    if (m_font)
        TTF_CloseFont(m_font);
}
