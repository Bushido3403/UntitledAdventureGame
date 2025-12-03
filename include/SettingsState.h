// SFML 3.x

#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

// Game state for managing settings (volume control)
class SettingsState : public GameState
{
public:
    SettingsState(ResourceManager& resources);
    
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    GameStateType getType() const override { return GameStateType::Settings; }
    
    // Set callback for when back/ESC is pressed
    void setOnBackClicked(std::function<void()> callback);
    
    // Update UI element positions based on window size
    void updatePositions(const sf::Vector2u& windowSize);

private:
    // Update the volume percentage display text
    void updateVolumeText();

    ResourceManager& resources;
    
    // UI text elements
    sf::Text titleText;
    sf::Text backText;
    sf::Text volumeLabel;
    sf::Text volumeValue;
    
    // Volume slider components
    sf::RectangleShape sliderBar;
    sf::RectangleShape sliderHandle;
    bool isDragging; // Track if user is dragging the slider
    
    std::function<void()> onBackClicked;
};