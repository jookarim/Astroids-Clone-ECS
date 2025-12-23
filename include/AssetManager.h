#pragma once

#include "Texture.h"
#include "Sound.h"
#include "Music.h"
#include "Text.h"

#include <map>
#include <memory>
#include <string>

class AssetManager
{
private:
    std::map<std::string, std::shared_ptr<Texture>> m_textures;
    std::map<std::string, std::shared_ptr<Sound>>   m_sounds;
    std::map<std::string, std::shared_ptr<Music>>   m_musics;
    std::map<std::string, std::shared_ptr<Text>>    m_texts;

public:
    AssetManager() = default;
    ~AssetManager() = default;
    
    std::shared_ptr<Texture> addTexture(SDL_Renderer* renderer, std::string_view path);
    void removeTexture(std::string_view path);
    std::shared_ptr<Texture> getTexture(std::string_view path) const;

    std::shared_ptr<Sound> addSound(std::string_view path);
    void removeSound(std::string_view path);
    std::shared_ptr<Sound> getSound(std::string_view path) const;

    std::shared_ptr<Music> addMusic(std::string_view path);
    void removeMusic(std::string_view path);
    std::shared_ptr<Music> getMusic(std::string_view path) const;
    
    std::shared_ptr<Text> addText(std::string_view path);
    void removeText(std::string_view path);
    std::shared_ptr<Text> getText(std::string_view path) const;
    
    void shutDown();

    static AssetManager& getInstance()
    {
        static AssetManager instance;
        return instance;
    }
};
