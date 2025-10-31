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
        return false;
    }
    music[id] = std::move(musicPtr);
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