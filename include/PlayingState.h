#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "PlayingStateUI.h"
#include "GameStateManager.h"
#include "InventorySystem.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

// Main gameplay state - manages scenes, choices, inventory, and transitions
class PlayingState : public GameState {
public:
    PlayingState(ResourceManager& resources, const std::string& scriptPath);
    
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void updatePositions(const sf::Vector2u& windowSize) override;
    GameStateType getType() const override { return GameStateType::Playing; }
    
    // Register callback for when script/story is complete
    void setOnScriptComplete(std::function<void()> callback);
    GameStateManager& getGameStateManager() { return *gameState; }
    
private:
    void loadScene(const std::string& sceneId);
    void createChoiceButtons();
    void startTransition(const std::string& sceneId);
    void updateTransition(float deltaTime);
    
    // Fade transition states between scenes
    enum class TransitionState {
        None,
        FadingOut,
        FadingIn
    };
    
    // Types of confirmation dialogs
    enum class ConfirmationType { None, ThrowOut, ThrowOutAll };
    
    void showConfirmationDialog(ConfirmationType type, int itemIndex, 
                                const sf::Vector2u& windowSize, float titlebarHeight);
    void handleConfirmation(bool confirmed);
    
    ResourceManager& resources;
    std::unique_ptr<SceneManager> sceneManager;
    std::unique_ptr<PlayingStateUI> ui;
    std::unique_ptr<GameStateManager> gameState;
    std::unique_ptr<InventorySystem> inventorySystem;
    
    std::vector<std::unique_ptr<Button>> choiceButtons;
    
    // Scene transition system
    TransitionState transitionState = TransitionState::None;
    float transitionAlpha = 0.f;
    std::string nextSceneId;
    sf::RectangleShape transitionOverlay;
    const float transitionDuration = 0.25f;
    
    // Confirmation dialog state
    ConfirmationType confirmationType = ConfirmationType::None;
    int pendingActionItemIndex = -1;
    
    std::function<void()> onScriptComplete;

    sf::Vector2u currentWindowSize;
};