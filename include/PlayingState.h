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
#include <unordered_map>

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
    void startTransition(const std::string& nextSceneId);
    void updateTransition(float deltaTime);

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

    // Save system
    std::unordered_map<std::string, bool> flags;
    std::unordered_map<std::string, int> stats;
    
    bool checkCondition(const Condition& condition) const;
    void applyEffects(const Effects& effects);
    void saveGame();
    void loadGame();

    // Transition system
    enum class TransitionState {
        None,
        FadingOut,
        FadingIn
    };
    
    TransitionState transitionState = TransitionState::None;
    float transitionAlpha = 0.f;
    float transitionDuration = 0.5f;  // 0.5 seconds per fade
    std::string nextSceneId;
    sf::RectangleShape transitionOverlay;
};