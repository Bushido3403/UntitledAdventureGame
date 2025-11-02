// SFML 3.x

#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include "ScriptParser.h"
#include "Button.h"
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
    void setOnScriptChain(std::function<void(const std::string&)> callback);

private:
    void loadScene(const std::string& sceneId);
    void loadNextScript(const std::string& nextScriptPath);
    void createChoiceTexts();
    void updateChoicePositions();
    void updateTextSizes();  // Add this
    std::string wrapText(const std::string& text, unsigned int maxWidth, const sf::Font& font, unsigned int characterSize);
    unsigned int getScaledCharacterSize(unsigned int baseSize) const;  // Add this

    ResourceManager& resources;
    GameScript script;
    const Scene* currentScene;
    std::string currentScriptPath;
    
    sf::RectangleShape background;
    sf::Text dialogText;
    sf::Text speakerText;
    sf::RectangleShape dialogBox;
    sf::RectangleShape graphicsBox;
    std::unique_ptr<sf::Sprite> graphicsSprite;
    sf::RectangleShape statsBox;
    
    std::vector<sf::Text> choiceTexts;
    std::vector<std::string> choiceNextScenes;
    std::vector<std::unique_ptr<Button>> choiceButtons;
    
    sf::Vector2u windowSize;
    sf::Vector2u baseWindowSize;  // Add this - reference size for scaling
    
    std::function<void()> onScriptComplete;
    std::function<void(const std::string&)> onScriptChain;
    std::string pendingSceneId;
};