// SFML 3.x

#pragma once
#include "ScriptParser.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <functional>

class SceneManager {
public:
    SceneManager(ResourceManager& resources);
    
    bool loadScript(const std::string& scriptPath);
    bool loadScene(const std::string& sceneId);
    
    const Scene* getCurrentScene() const { return currentScene; }
    const GameScript& getScript() const { return script; }
    std::unique_ptr<sf::Sprite>& getGraphicsSprite() { return graphicsSprite; }
    
    void setOnScriptComplete(std::function<void()> callback) { onScriptComplete = callback; }

private:
    ResourceManager& resources;
    GameScript script;
    const Scene* currentScene;
    std::unique_ptr<sf::Sprite> graphicsSprite;
    std::function<void()> onScriptComplete;
};