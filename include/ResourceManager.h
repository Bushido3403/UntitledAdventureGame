// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

// Centralized manager for loading and accessing game resources
class ResourceManager
{
public:
    // Load resources from file paths
    bool loadTexture(const std::string& id, const std::string& path);
    bool loadFont(const std::string& id, const std::string& path);
    bool loadMusic(const std::string& id, const std::string& path);
    bool loadSoundBuffer(const std::string& id, const std::string& path);
    
    // Get loaded resources by ID
    sf::Texture& getTexture(const std::string& id);
    sf::Font& getFont(const std::string& id);
    sf::Music& getMusic(const std::string& id);
    sf::SoundBuffer& getSoundBuffer(const std::string& id);

private:
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> music;  // Unique ptr since Music is non-copyable
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
};