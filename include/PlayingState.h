#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PlayingStateUI.h"
#include "GameStateManager.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class PlayingState : public GameState {
public:
    PlayingState(ResourceManager& resources, const std::string& scriptPath);
    
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void updatePositions(const sf::Vector2u& windowSize) override;
    GameStateType getType() const override { return GameStateType::Playing; }
    
    void setOnScriptComplete(std::function<void()> callback);
    
private:
    void loadScene(const std::string& sceneId);
    void createChoiceButtons();
    void startTransition(const std::string& sceneId);
    void updateTransition(float deltaTime);
    
    enum class TransitionState {
        None,
        FadingOut,
        FadingIn
    };
    
    ResourceManager& resources;
    std::unique_ptr<SceneManager> sceneManager;
    std::unique_ptr<PlayingStateUI> ui;
    std::unique_ptr<GameStateManager> gameState;
    
    std::vector<std::unique_ptr<Button>> choiceButtons;
    
    TransitionState transitionState = TransitionState::None;
    float transitionAlpha = 0.f;
    std::string nextSceneId;
    sf::RectangleShape transitionOverlay;
    const float transitionDuration = 0.25f;
    
    std::function<void()> onScriptComplete;
};