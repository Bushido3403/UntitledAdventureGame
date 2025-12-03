// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>

// Different screens/modes of the game
enum class GameStateType {
    MainMenu,
    Start,
    Settings,
    Playing
};

class GameEngine;  // Forward declaration

// Base class for all game states (menu, playing, settings, etc.)
class GameState {
public:
    virtual ~GameState() = default;
    
    // Process user input events
    virtual void handleEvent(const sf::Event& event) = 0;
    
    // Update game logic each frame
    virtual void update(float deltaTime, sf::RenderWindow& window) = 0;
    
    // Render the state to the window
    virtual void draw(sf::RenderWindow& window) = 0;
    
    // Recalculate positions when window is resized
    virtual void updatePositions(const sf::Vector2u& windowSize) = 0;
    
    // Return which type of state this is
    virtual GameStateType getType() const = 0;
    
    // Allow states to access the engine for state transitions
    void setEngine(GameEngine* eng) { engine = eng; }
    
protected:
    GameEngine* engine = nullptr;
};