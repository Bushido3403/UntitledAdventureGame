#pragma once
#include <SFML/Graphics.hpp>

enum class GameStateType
{
    MainMenu,
    Start,
    Settings
};

class GameState
{
public:
    virtual ~GameState() = default;
    
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float deltaTime, sf::RenderWindow& window) = 0;  // Add window param
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void updatePositions(const sf::Vector2u& windowSize) = 0;
    
    virtual GameStateType getType() const = 0;
};