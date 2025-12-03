// SFML 3.x

#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(ResourceManager& resources)
    : resources(resources), currentScene(nullptr) {}

bool SceneManager::loadScript(const std::string& scriptPath) {
    // Parse script file
    auto scriptOpt = ScriptParser::loadScript(scriptPath);
    if (!scriptOpt) {
        return false;
    }
    
    script = *scriptOpt;
    
    std::cout << "Loaded script: " << script.title 
              << " (Chapter " << script.metadata.chapter << ")" << std::endl;
    
    // Load first scene
    return !script.scenes.empty() && loadScene(script.scenes[0].id);
}

bool SceneManager::loadScene(const std::string& sceneId) {
    // Check for script end
    if (sceneId == "END") {
        if (onScriptComplete) {
            onScriptComplete();
        }
        return false;
    }
    
    // Find scene in script
    currentScene = ScriptParser::findScene(script, sceneId);
    if (!currentScene) {
        std::cerr << "Scene not found: " << sceneId << std::endl;
        return false;
    }
    
    // Load background texture
    if (!currentScene->background.empty()) {
        try {
            // Try to get already loaded texture
            sf::Texture& texture = resources.getTexture(currentScene->background);
            graphicsSprite = std::make_unique<sf::Sprite>(texture);
        } catch (const std::out_of_range&) {
            // Load texture from file (try .jpeg first, then .png)
            std::string texturePath = "assets/images/" + currentScene->background + ".jpeg";
            if (resources.loadTexture(currentScene->background, texturePath)) {
                graphicsSprite = std::make_unique<sf::Sprite>(resources.getTexture(currentScene->background));
            } else {
                texturePath = "assets/images/" + currentScene->background + ".png";
                if (resources.loadTexture(currentScene->background, texturePath)) {
                    graphicsSprite = std::make_unique<sf::Sprite>(resources.getTexture(currentScene->background));
                } else {
                    std::cerr << "Failed to load texture: " << currentScene->background << std::endl;
                    graphicsSprite.reset();
                }
            }
        }
    } else {
        graphicsSprite.reset();
    }
    
    return true;
}