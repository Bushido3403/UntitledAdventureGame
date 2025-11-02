// SFML 3.x

#include "ResourceManager.h"
#include <iostream>

bool ResourceManager::loadTexture(const std::string& id, const std::string& path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return false;
    }
    texture.setSmooth(true);
    textures[id] = std::move(texture);
    return true;
}

bool ResourceManager::loadFont(const std::string& id, const std::string& path)
{
    sf::Font font;
    if (!font.openFromFile(path))
    {
        std::cerr << "Failed to load font: " << path << std::endl;
        return false;
    }
    fonts[id] = std::move(font);
    return true;
}

bool ResourceManager::loadMusic(const std::string& id, const std::string& path)
{
    auto musicPtr = std::make_unique<sf::Music>();
    if (!musicPtr->openFromFile(path))
    {
        std::cerr << "Failed to load music: " << path << std::endl;
        std::cerr << "Current working directory: " << std::filesystem::current_path() << std::endl;
        return false;
    }
    music[id] = std::move(musicPtr);
    std::cout << "Successfully loaded music: " << id << std::endl; // Add this
    return true;
}

bool ResourceManager::loadSoundBuffer(const std::string& id, const std::string& path)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(path))
    {
        std::cerr << "Failed to load sound buffer: " << path << std::endl;
        return false;
    }
    soundBuffers[id] = std::move(buffer);
    return true;
}

sf::Texture& ResourceManager::getTexture(const std::string& id)
{
    return textures.at(id);
}

sf::Font& ResourceManager::getFont(const std::string& id)
{
    return fonts.at(id);
}

sf::Music& ResourceManager::getMusic(const std::string& id)
{
    return *music.at(id);
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& id)
{
    return soundBuffers.at(id);
}