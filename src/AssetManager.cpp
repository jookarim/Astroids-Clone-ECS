#include "AssetManager.h"

std::shared_ptr<Texture> AssetManager::addTexture(SDL_Renderer* renderer, std::string_view path)
{
    std::string key(path);

    auto it = m_textures.find(key);
    if (it != m_textures.end())
        return it->second;

    auto texture = std::shared_ptr<Texture>(new Texture(renderer, key));

    if (texture->getPath() != "")
        m_textures[key] = texture;

    return texture;
}

void AssetManager::removeTexture(std::string_view path)
{
    m_textures.erase(std::string(path));
}

std::shared_ptr<Texture> AssetManager::getTexture(std::string_view path) const
{
    auto it = m_textures.find(std::string(path));
    return (it != m_textures.end()) ? it->second : nullptr;
}

std::shared_ptr<Sound> AssetManager::addSound(std::string_view path)
{
    std::string key(path);

    auto it = m_sounds.find(key);
    if (it != m_sounds.end())
        return it->second;

    auto sound = std::shared_ptr<Sound>(new Sound(key));

    if (sound->getSound())
        m_sounds[key] = sound;

    return sound;
}

void AssetManager::removeSound(std::string_view path)
{
    m_sounds.erase(std::string(path));
}

std::shared_ptr<Sound> AssetManager::getSound(std::string_view path) const
{
    auto it = m_sounds.find(std::string(path));
    return (it != m_sounds.end()) ? it->second : nullptr;
}

std::shared_ptr<Music> AssetManager::addMusic(std::string_view path)
{
    std::string key(path);

    auto it = m_musics.find(key);
    if (it != m_musics.end())
        return it->second;

    auto music = std::shared_ptr<Music>(new Music(key));

    if (music->getMusic())
        m_musics[key] = music;

    return music;
}

void AssetManager::removeMusic(std::string_view path)
{
    m_musics.erase(std::string(path));
}

std::shared_ptr<Music> AssetManager::getMusic(std::string_view path) const
{
    auto it = m_musics.find(std::string(path));
    return (it != m_musics.end()) ? it->second : nullptr;
}

std::shared_ptr<Text> AssetManager::addText(std::string_view path)
{
    std::string key(path);

    auto it = m_texts.find(key);
    if (it != m_texts.end())
        return it->second;

    auto text = std::shared_ptr<Text>(new Text(key));

    if (text->getFont())
        m_texts[key] = text;

    return text;
}

void AssetManager::removeText(std::string_view path)
{
    m_texts.erase(std::string(path));
}

std::shared_ptr<Text> AssetManager::getText(std::string_view path) const
{
    auto it = m_texts.find(std::string(path));
    return (it != m_texts.end()) ? it->second : nullptr;
}

void AssetManager::shutDown()
{
    m_textures.clear();
    m_musics.clear();
    m_sounds.clear();
    m_texts.clear();
}
