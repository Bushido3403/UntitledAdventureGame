// SFML 3.x

#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "DialogBox.h"
#include "LayoutManager.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

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
    void createChoiceButtons();
    void updateChoicePositions();
    void loadScene(const std::string& sceneId);

    ResourceManager& resources;
    std::unique_ptr<SceneManager> sceneManager;
    std::unique_ptr<DialogBox> dialogBox;
    std::unique_ptr<LayoutManager> layoutManager;
    
    sf::RectangleShape background;
    sf::RectangleShape dialogBoxShape;
    sf::RectangleShape graphicsBox;
    sf::RectangleShape statsBox;
    
    std::vector<std::unique_ptr<Button>> choiceButtons;
    
    sf::Vector2u windowSize;
    std::string pendingSceneId;
    std::function<void()> onScriptComplete;
};