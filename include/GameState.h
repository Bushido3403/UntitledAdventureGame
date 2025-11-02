// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>

enum class GameStateType {
    MainMenu,
    Start,
    Settings,
    Playing
};

class GameEngine;  // Forward declaration

class GameState {
public:
    virtual ~GameState() = default;
    
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float deltaTime, sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void updatePositions(const sf::Vector2u& windowSize) = 0;
    virtual GameStateType getType() const = 0;
    
    // Allow states to access the engine
    void setEngine(GameEngine* eng) { engine = eng; }
    
protected:
    GameEngine* engine = nullptr;
};