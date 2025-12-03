// SFML 3.x

#pragma once
#include "ScriptParser.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <functional>
#include <unordered_map>

// Manages game scenes and script progression
class SceneManager {
public:
    SceneManager(ResourceManager& resources);
    
    // Load a game script from file
    bool loadScript(const std::string& scriptPath);
    
    // Load and display a specific scene by ID
    bool loadScene(const std::string& sceneId);
    
    // Getters for current state
    const Scene* getCurrentScene() const { return currentScene; }
    const GameScript& getScript() const { return script; }
    std::unique_ptr<sf::Sprite>& getGraphicsSprite() { return graphicsSprite; }
    
    // Set callback for when script completes
    void setOnScriptComplete(std::function<void()> callback) { onScriptComplete = callback; }

private:
    ResourceManager& resources;
    GameScript script;
    const Scene* currentScene;
    std::unique_ptr<sf::Sprite> graphicsSprite;
    std::function<void()> onScriptComplete;
};