// SFML 3.x

#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include "ScriptParser.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>

class PlayingState : public GameState {
public:
    PlayingState(ResourceManager& resources, const std::string& scriptPath);

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    GameStateType getType() const override { return GameStateType::Playing; }
    
    void updatePositions(const sf::Vector2u& windowSize) override;
    void setOnScriptComplete(std::function<void()> callback);

private:
    void loadScene(const std::string& sceneId);
    void createChoiceTexts();
    void updateChoicePositions();

    ResourceManager& resources;
    GameScript script;
    const Scene* currentScene;
    
    sf::RectangleShape background;
    sf::Text dialogText;
    sf::Text speakerText;
    sf::RectangleShape dialogBox;
    sf::RectangleShape graphicsBox;
    std::unique_ptr<sf::Sprite> graphicsSprite;
    sf::RectangleShape statsBox;
    
    std::vector<sf::Text> choiceTexts;
    std::vector<std::string> choiceNextScenes;
    
    sf::Vector2u windowSize;
    
    std::function<void()> onScriptComplete;
};