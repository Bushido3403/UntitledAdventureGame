// SFML 3.x

#pragma once
#include "GameState.h"
#include "Button.h"
#include "ResourceManager.h"
#include <memory>
#include <SFML/Graphics.hpp>

class MainMenuState : public GameState
{
public:
    MainMenuState(ResourceManager& resources);

    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;  // Keep only this one
    void draw(sf::RenderWindow& window) override;
    GameStateType getType() const override { return GameStateType::MainMenu; }
    
    void setOnStartClicked(std::function<void()> callback);
    void setOnSettingsClicked(std::function<void()> callback);
    void updatePositions(const sf::Vector2u& windowSize) override;
    
private:
    ResourceManager& resources;
    sf::Sprite backgroundSprite;
    sf::Sprite logoSprite;
    sf::Sprite titleSprite;
    
    std::unique_ptr<Button> startButton;
    std::unique_ptr<Button> settingsButton;
    
    std::function<void()> onStartClicked;
    std::function<void()> onSettingsClicked;
};