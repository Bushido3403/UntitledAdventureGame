// SFML 3.x

#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include "CustomWindow.h"
#include <memory>
#include <stack>
#include <functional>

class GameEngine {
public:
    GameEngine();
    void run();
    
    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeState(std::unique_ptr<GameState> state);
    
    ResourceManager& getResources() { return resources; }
    CustomWindow& getWindow() { return *window; }
    
    // Factory methods for creating states
    std::unique_ptr<GameState> createMainMenuState();
    std::unique_ptr<GameState> createStartState();
    std::unique_ptr<GameState> createSettingsState();
    std::unique_ptr<GameState> createPlayingState(const std::string& scriptPath);
    
private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void setupStateCallbacks(GameState* state);
    
    ResourceManager resources;
    std::unique_ptr<CustomWindow> window;
    std::stack<std::unique_ptr<GameState>> stateStack;
    sf::Clock clock;
};