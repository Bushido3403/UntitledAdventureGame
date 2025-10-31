// SFML 3.x

#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

class StartState : public GameState
{
public:
    StartState(ResourceManager& resources);  // Remove window parameter
    
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    GameStateType getType() const override { return GameStateType::Start; }
    
    void setOnBackClicked(std::function<void()> callback);
    void updatePositions(const sf::Vector2u& windowSize);

private:
    sf::Text placeholderText;
    sf::Text backText;
    std::function<void()> onBackClicked;
};