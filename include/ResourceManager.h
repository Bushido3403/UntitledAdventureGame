// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
    bool loadTexture(const std::string& id, const std::string& path);
    bool loadFont(const std::string& id, const std::string& path);
    bool loadMusic(const std::string& id, const std::string& path);
    bool loadSoundBuffer(const std::string& id, const std::string& path);
    
    sf::Texture& getTexture(const std::string& id);
    sf::Font& getFont(const std::string& id);
    sf::Music& getMusic(const std::string& id);
    sf::SoundBuffer& getSoundBuffer(const std::string& id);

private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> music;
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
};