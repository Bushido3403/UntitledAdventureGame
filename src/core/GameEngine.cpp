// SFML 3.x

#include "GameEngine.h"
#include "MainMenuState.h"
#include "StartState.h"
#include "SettingsState.h"
#include "Button.h"
#include "PlayingState.h"
#include <iostream>

GameEngine::GameEngine() {
    resources.loadFont("main", "assets/fonts/MedievalSharp.ttf");
    resources.loadTexture("cursor", "assets/images/cursor.png");  // Load cursor first
    
    resources.loadTexture("background", "assets/images/menuBackground.jpeg");
    resources.loadTexture("logo", "assets/images/logo.png");
    resources.loadTexture("title", "assets/images/title.png");
    resources.loadTexture("start", "assets/images/start.png");
    resources.loadTexture("settings", "assets/images/settings.png");
    resources.loadSoundBuffer("click", "assets/sfx/click.wav");
    resources.loadMusic("title", "assets/sfx/title.mp3");
    
    // Load icon BEFORE creating window
    sf::Image icon;
    if (!icon.loadFromFile("assets/images/logo.png")) {
        // Handle error - could log or use a default icon
        // For now, just continue without icon
    }
    
    // NOW construct the window (use 'window', not 'customWindow')
    window = std::make_unique<CustomWindow>(
        sf::Vector2u(1280u, 720u), 
        "Untitled Adventure Game", 
        resources.getFont("main"),
        resources.getTexture("cursor")  // Pass cursor texture as 4th parameter
    );
    
    // Set icon immediately (only if loaded successfully)
    if (icon.getSize().x > 0) {
        window->setIcon(icon);
    }
    
    Button::prime(resources);
    resources.getMusic("title").setVolume(100.f);
    resources.getMusic("title").setLooping(true);
    resources.getMusic("title").play();

    // Check status
    std::cout << "Music status: " << static_cast<int>(resources.getMusic("title").getStatus()) << std::endl;
    // 0=Stopped, 1=Paused, 2=Playing
}

void GameEngine::run() {
    while (window->isOpen() && !stateStack.empty()) {
        processEvents();
        
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}

void GameEngine::pushState(std::unique_ptr<GameState> state) {
    setupStateCallbacks(state.get());
    state->updatePositions(window->getSize());
    stateStack.push(std::move(state));
}

void GameEngine::popState() {
    if (!stateStack.empty()) {
        stateStack.pop();
        if (!stateStack.empty()) {
            stateStack.top()->updatePositions(window->getSize());
            
            // Reset main menu transition state when returning to it
            if (stateStack.top()->getType() == GameStateType::MainMenu) {
                auto* mainMenu = static_cast<MainMenuState*>(stateStack.top().get());
                mainMenu->resetTransition();
            }
        }
    }
}

void GameEngine::changeState(std::unique_ptr<GameState> state) {
    if (!stateStack.empty()) {
        stateStack.pop();
    }
    pushState(std::move(state));
}

std::unique_ptr<GameState> GameEngine::createMainMenuState() {
    return std::make_unique<MainMenuState>(resources);
}

std::unique_ptr<GameState> GameEngine::createStartState() {
    return std::make_unique<StartState>(resources);
}

std::unique_ptr<GameState> GameEngine::createSettingsState() {
    return std::make_unique<SettingsState>(resources);
}

std::unique_ptr<GameState> GameEngine::createPlayingState(const std::string& scriptPath) {
    return std::make_unique<PlayingState>(resources, scriptPath);
}

void GameEngine::setupStateCallbacks(GameState* state) {
    switch (state->getType()) {
        case GameStateType::MainMenu: {
            auto* mainMenu = static_cast<MainMenuState*>(state);
            
            mainMenu->setOnStartClicked([this]() {
                // Change this line to load your script instead of the placeholder StartState
                pushState(createPlayingState("assets/scripts/intro.json"));
            });
            
            mainMenu->setOnSettingsClicked([this]() {
                pushState(createSettingsState());
            });
            break;
        }
        
        case GameStateType::Start: {
            auto* startState = static_cast<StartState*>(state);
            
            startState->setOnBackClicked([this]() {
                popState();
            });
            break;
        }
        
        case GameStateType::Settings: {
            auto* settingsState = static_cast<SettingsState*>(state);
            
            settingsState->setOnBackClicked([this]() {
                popState();
            });
            break;
        }
        
        case GameStateType::Playing: {
            auto* playingState = static_cast<PlayingState*>(state);
            
            playingState->setOnScriptComplete([this, playingState]() {
                // Clear save data when the script ends
                playingState->getGameStateManager().clearSave();
                popState(); // returns to main menu
            });
            break;
        }
        
        default:
            break;
    }
}

void GameEngine::processEvents() {
    while (const std::optional event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>() || window->getShouldClose()) {
            window->close();
            return;
        }
        
        window->handleEvent(*event);
        
        if (event->is<sf::Event::Resized>()) {
            if (!stateStack.empty()) {
                stateStack.top()->updatePositions(window->getSize());
            }
        }
        
        if (!stateStack.empty()) {
            stateStack.top()->handleEvent(*event);
        }
    }
    
    // Check if window was resized due to fullscreen toggle
    if (window->wasResized()) {
        if (!stateStack.empty()) {
            stateStack.top()->updatePositions(window->getSize());
        }
        window->clearResized();
    }
}

void GameEngine::update(float deltaTime) {
    if (!stateStack.empty()) {
        stateStack.top()->update(deltaTime, window->getWindow());
    }
}

void GameEngine::render() {
    window->clear();
    
    if (!stateStack.empty()) {
        stateStack.top()->draw(window->getWindow());
    }
                  
    window->drawTitlebar();
    window->display();
}