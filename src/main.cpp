#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "CustomWindow.h"
#include "MainMenuState.h"
#include "StartState.h"
#include "SettingsState.h"
#include <memory>

// Add this helper function before main()
void setupMainMenuCallbacks(MainMenuState* menuState, std::unique_ptr<GameState>& nextState, 
                           ResourceManager& resources, CustomWindow& customWindow);

void setupMainMenuCallbacks(MainMenuState* menuState, std::unique_ptr<GameState>& nextState,
                           ResourceManager& resources, CustomWindow& customWindow)
{
    menuState->setOnStartClicked([&]() {
        auto startState = std::make_unique<StartState>(resources);
        startState->setOnBackClicked([&]() {
            auto newMenuState = std::make_unique<MainMenuState>(resources);
            setupMainMenuCallbacks(newMenuState.get(), nextState, resources, customWindow);
            nextState = std::move(newMenuState);
        });
        nextState = std::move(startState);
    });

    menuState->setOnSettingsClicked([&]() {
        auto settingsState = std::make_unique<SettingsState>(resources);
        settingsState->setOnBackClicked([&]() {
            auto newMenuState = std::make_unique<MainMenuState>(resources);
            setupMainMenuCallbacks(newMenuState.get(), nextState, resources, customWindow);
            nextState = std::move(newMenuState);
        });
        nextState = std::move(settingsState);
    });
}

int main()
{
    // Load resources
    ResourceManager resources;
    resources.loadTexture("background", "assets/images/menuBackground.jpg");
    resources.loadTexture("logo", "assets/images/logo.png");
    resources.loadTexture("title", "assets/images/title.png");
    resources.loadTexture("start", "assets/images/start.png");
    resources.loadTexture("settings", "assets/images/settings.png");
    resources.loadFont("main", "assets/fonts/MedievalSharp.ttf");
    resources.loadMusic("title", "assets/sfx/Title.mp3");
    
    resources.getMusic("title").setLooping(true);
    resources.getMusic("title").play();

    // Initialize custom window
    CustomWindow customWindow(
        sf::Vector2u(1280u, 720u),
        "Untitled Adventure Game",
        resources.getFont("main")
    );

    // Set icon
    sf::Image icon;
    if (icon.loadFromFile("assets/images/logo.png"))
        customWindow.getWindow().setIcon(icon);
    
    // Initialize state
    std::unique_ptr<GameState> currentState = std::make_unique<MainMenuState>(
        resources  // Remove window parameter
    );
    currentState->updatePositions(customWindow.getSize());  // Initialize positions
    
    std::unique_ptr<GameState> nextState = nullptr;

    auto* menuState = dynamic_cast<MainMenuState*>(currentState.get());
    
    setupMainMenuCallbacks(menuState, nextState, resources, customWindow);

    while (customWindow.isOpen())
    {
        while (const std::optional event = customWindow.pollEvent())
        {
            if (event->is<sf::Event::Resized>())
            {
                customWindow.handleEvent(*event);
                currentState->updatePositions(customWindow.getSize());  // Much simpler!
            }
            else
            {
                customWindow.handleEvent(*event);
                
                // Check if fullscreen was toggled (window recreated)
                if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    static sf::Vector2u lastSize = customWindow.getSize();
                    sf::Vector2u currentSize = customWindow.getSize();
                    
                    if (currentSize != lastSize)
                    {
                        currentState->updatePositions(currentSize);  // Much simpler!
                        lastSize = currentSize;
                    }
                }
            }
            
            if (customWindow.getShouldClose()) {
                customWindow.close();
                break;
            }
            
            if (event->is<sf::Event::Closed>())
                customWindow.close();
                
            currentState->handleEvent(*event);
        }

        if (nextState) {
            currentState = std::move(nextState);
            currentState->updatePositions(customWindow.getSize());
            if (auto* menuState = dynamic_cast<MainMenuState*>(currentState.get())) {
                setupMainMenuCallbacks(menuState, nextState, resources, customWindow);
            }
        }

        currentState->update(0.016f, customWindow.getWindow());
        
        customWindow.clear();
        currentState->draw(customWindow.getWindow());
        customWindow.drawTitlebar();
        customWindow.display();
    }

    return 0;
}