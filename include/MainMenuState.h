// MAINMENUSTATE.H

// SFML 3.x

#pragma once
#include "GameState.h"
#include "Button.h"
#include "ResourceManager.h"
#include <memory>
#include <SFML/Graphics.hpp>

// Main menu screen with buttons and fade-to-black transition
class MainMenuState : public GameState
{
public:
    MainMenuState(ResourceManager& resources);

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    GameStateType getType() const override { return GameStateType::MainMenu; }
    
    // Register callbacks for button clicks
    void setOnStartClicked(std::function<void()> callback);
    void setOnSettingsClicked(std::function<void()> callback);
    
    // Recalculate positions when window resizes
    void updatePositions(const sf::Vector2u& windowSize) override;
    
    // Reset fade effect when returning to menu
    void resetTransition();
    
private:
    ResourceManager& resources;
    sf::Sprite backgroundSprite;
    sf::Sprite logoSprite;
    sf::Sprite titleSprite;
    
    std::unique_ptr<Button> startButton;
    std::unique_ptr<Button> settingsButton;
    
    std::function<void()> onStartClicked;
    std::function<void()> onSettingsClicked;
    
    // Transition system
    bool isTransitioning = false;
    float transitionAlpha = 0.f;
    float transitionDuration = 1.0f;  // 1 second fade to black
    sf::RectangleShape transitionOverlay;
};