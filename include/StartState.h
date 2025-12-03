// SFML 3.x

#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

// Placeholder game state for when the game starts
class StartState : public GameState
{
public:
    StartState(ResourceManager& resources);
    
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    GameStateType getType() const override { return GameStateType::Start; }
    
    // Set callback for when ESC is pressed
    void setOnBackClicked(std::function<void()> callback);
    
    // Update UI element positions based on window size
    void updatePositions(const sf::Vector2u& windowSize);

private:
    sf::Text placeholderText; // Main display text
    sf::Text backText;        // Instructions for returning to menu
    std::function<void()> onBackClicked;
};