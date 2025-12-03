#include "PlayingState.h"
#include "CustomWindow.h"
#include <iostream>

PlayingState::PlayingState(ResourceManager& resources, const std::string& scriptPath)
    : resources(resources),
      sceneManager(std::make_unique<SceneManager>(resources)),
      ui(std::make_unique<PlayingStateUI>(resources)),
      gameState(std::make_unique<GameStateManager>()),
      inventorySystem(std::make_unique<InventorySystem>(resources))
{
    ui->setInventorySystem(inventorySystem.get());
    
    // Initialize transition overlay to full opacity
    transitionOverlay.setFillColor(sf::Color(0, 0, 0, 255));
    transitionOverlay.setSize(sf::Vector2f(800.f, 600.f));
    
    // Load game state first
    gameState->loadGame(inventorySystem.get());
    
    // Determine which script and scene to load
    std::string scriptToLoad = scriptPath;
    std::string sceneToLoad;
    
    if (gameState->hasSaveData()) {
        // If we have save data, check if it matches the requested script
        std::string savedScript = gameState->getCurrentScript();
        
        // Extract script ID from path (e.g., "assets/scripts/intro.json" -> "intro")
        std::string requestedScriptId = scriptPath;
        size_t lastSlash = requestedScriptId.find_last_of("/\\");
        if (lastSlash != std::string::npos) {
            requestedScriptId = requestedScriptId.substr(lastSlash + 1);
        }
        size_t lastDot = requestedScriptId.find_last_of(".");
        if (lastDot != std::string::npos) {
            requestedScriptId = requestedScriptId.substr(0, lastDot);
        }
        
        // If saved script matches requested script, load from save
        if (savedScript == requestedScriptId) {
            sceneToLoad = gameState->getCurrentScene();
            std::cout << "Continuing from saved scene: " << sceneToLoad << std::endl;
        }
    }
    
    // Load the script
    if (sceneManager->loadScript(scriptToLoad)) {
        // If we have a scene to load, use it; otherwise start from first scene
        if (!sceneToLoad.empty()) {
            loadScene(sceneToLoad);
        } else {
            loadScene(sceneManager->getScript().scenes[0].id);
        }
    }
    
    // Start with fade-in transition
    transitionState = TransitionState::FadingIn;
    transitionAlpha = 255.f;
}

void PlayingState::setOnScriptComplete(std::function<void()> callback) {
    onScriptComplete = callback;
    sceneManager->setOnScriptComplete(callback);
}

// Load a scene, apply effects, save state, and create choice buttons
void PlayingState::loadScene(const std::string& sceneId) {
    if (!sceneManager->loadScene(sceneId)) {
        return;
    }
    
    const Scene* currentScene = sceneManager->getCurrentScene();
    if (!currentScene) return;
    
    // Apply effects if present (modify stats, add items, etc.)
    if (currentScene->effects.has_value()) {
        gameState->applyEffects(currentScene->effects.value(), inventorySystem.get());
    }
    
    // Save game state on EVERY scene transition
    gameState->saveGame(sceneManager->getScript().scriptId, currentScene->id, 
                      inventorySystem.get());
    
    // Calculate layout metrics for text wrapping
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    sf::Vector2u fullWindowSize(ui->getWindowSize().x, 
                                ui->getWindowSize().y + static_cast<unsigned int>(TITLEBAR_HEIGHT));
    
    LayoutManager tempLayoutManager(sf::Vector2u(800, 600));
    auto metrics = tempLayoutManager.calculate(fullWindowSize, TITLEBAR_HEIGHT);
    unsigned int dialogSize = tempLayoutManager.getScaledCharacterSize(24, ui->getWindowSize());
    
    // Wrap text to fit dialog box
    float maxTextWidth = metrics.dialogBoxSize.x - (metrics.scale.boxPadding * 2);
    std::string wrappedText = DialogBox::wrapText(currentScene->text, 
                                                  static_cast<unsigned int>(maxTextWidth), 
                                                  resources.getFont("main"), 
                                                  dialogSize);
    
    ui->getDialogBox().setText(wrappedText, currentScene->speaker, currentScene->speakerColor);
    
    createChoiceButtons();
    updatePositions(fullWindowSize);
}

// Initiate fade-out transition to next scene
void PlayingState::startTransition(const std::string& sceneId) {
    if (transitionState != TransitionState::None) {
        return;
    }
    
    nextSceneId = sceneId;
    transitionState = TransitionState::FadingOut;
    transitionAlpha = 0.f;
}

// Update fade transition and load next scene at midpoint
void PlayingState::updateTransition(float deltaTime) {
    if (transitionState == TransitionState::None) {
        return;
    }
    
    float alphaSpeed = 255.f / transitionDuration;
    
    if (transitionState == TransitionState::FadingOut) {
        transitionAlpha += alphaSpeed * deltaTime;
        
        if (transitionAlpha >= 255.f) {
            transitionAlpha = 255.f;
            
            std::string sceneToLoad = nextSceneId;
            nextSceneId.clear();
            
            // Check if story is complete
            if (sceneToLoad == "END") {
                if (onScriptComplete) {
                    onScriptComplete();
                }
                return;
            }
            
            // Load next scene at peak of fade
            loadScene(sceneToLoad);
            transitionState = TransitionState::FadingIn;
        }
    }
    else if (transitionState == TransitionState::FadingIn) {
        transitionAlpha -= alphaSpeed * deltaTime;
        
        if (transitionAlpha <= 0.f) {
            transitionAlpha = 0.f;
            transitionState = TransitionState::None;
        }
    }
    
    // Update overlay transparency
    sf::Color overlayColor = transitionOverlay.getFillColor();
    overlayColor.a = static_cast<std::uint8_t>(std::clamp(transitionAlpha, 0.f, 255.f));
    transitionOverlay.setFillColor(overlayColor);
}

// Create buttons for all visible choices (filtered by conditions)
void PlayingState::createChoiceButtons() {
    choiceButtons.clear();
    
    const Scene* currentScene = sceneManager->getCurrentScene();
    if (!currentScene) return;
    
    const char labels[] = {'a', 'b', 'c', 'd'};
    size_t labelIndex = 0;
    
    for (size_t i = 0; i < currentScene->choices.size() && labelIndex < 4; ++i) {
        const auto& choice = currentScene->choices[i];
        
        // Skip choices that don't meet conditions
        if (choice.condition.has_value() && !gameState->checkCondition(choice.condition.value())) {
            continue;
        }
        
        auto button = std::make_unique<Button>(resources, nullptr, sf::Vector2f(0, 0));
        button->setText(std::string(1, labels[labelIndex]) + ") " + choice.text, 
                       resources.getFont("main"), 22);
        
        std::string nextScene = choice.nextScene;
        std::string nextScript = choice.nextScript;
        
        // Handle script changes or scene transitions
        button->setOnClick([this, nextScene, nextScript]() {
            if (!nextScript.empty()) {
                sceneManager->loadScript(nextScript);
                if (!sceneManager->getScript().scenes.empty()) {
                    startTransition(sceneManager->getScript().scenes[0].id);
                }
            } else {
                startTransition(nextScene);
            }
        });
        
        choiceButtons.push_back(std::move(button));
        labelIndex++;
    }
}

void PlayingState::updatePositions(const sf::Vector2u& newWindowSize) {
    currentWindowSize = newWindowSize;  // Store for later use
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    
    transitionOverlay.setSize(sf::Vector2f(static_cast<float>(newWindowSize.x), 
                                           static_cast<float>(newWindowSize.y) - TITLEBAR_HEIGHT));
    transitionOverlay.setPosition({0.f, TITLEBAR_HEIGHT});
    
    const Scene* currentScene = sceneManager->getCurrentScene();
    ui->updatePositions(newWindowSize, currentScene);
    ui->updateChoiceButtons(choiceButtons, currentScene);
}

// Show Y/N confirmation dialog for item deletion
void PlayingState::showConfirmationDialog(ConfirmationType type, int itemIndex, 
                                   const sf::Vector2u& windowSize, float titlebarHeight) {
    confirmationType = type;
    pendingActionItemIndex = itemIndex;
    
    std::string message;
    
    if (type == ConfirmationType::ThrowOut) {
        const auto& items = inventorySystem->getItems();
        if (itemIndex >= 0 && itemIndex < static_cast<int>(items.size())) {
            const ItemDefinition* def = inventorySystem->getItemDefinition(items[itemIndex].id);
            if (def) {
                message = "Throw out " + def->name + "?";
            }
        }
    } else if (type == ConfirmationType::ThrowOutAll) {
        const auto& items = inventorySystem->getItems();
        if (itemIndex >= 0 && itemIndex < static_cast<int>(items.size())) {
            const ItemDefinition* def = inventorySystem->getItemDefinition(items[itemIndex].id);
            if (def) {
                message = "Throw out all " + def->name + " (" + 
                         std::to_string(items[itemIndex].quantity) + ")?";
            }
        }
    }
    
    ui->getConfirmationDialog().show(message, windowSize, titlebarHeight);
}

// Execute confirmed action or cancel
void PlayingState::handleConfirmation(bool confirmed) {
    ui->getConfirmationDialog().hide();
    
    if (!confirmed) {
        confirmationType = ConfirmationType::None;
        pendingActionItemIndex = -1;
        return;
    }
    
    const auto& items = inventorySystem->getItems();
    if (pendingActionItemIndex < 0 || pendingActionItemIndex >= static_cast<int>(items.size())) {
        confirmationType = ConfirmationType::None;
        pendingActionItemIndex = -1;
        return;
    }
    
    // Remove item(s) and save game state
    if (confirmationType == ConfirmationType::ThrowOut) {
        inventorySystem->removeItemAtIndex(pendingActionItemIndex, 1, gameState.get());
        gameState->saveGame(sceneManager->getScript().scriptId, 
                          sceneManager->getCurrentScene()->id,
                          inventorySystem.get());
    }
    else if (confirmationType == ConfirmationType::ThrowOutAll) {
        inventorySystem->removeItemAtIndex(pendingActionItemIndex, items[pendingActionItemIndex].quantity, gameState.get());
        gameState->saveGame(sceneManager->getScript().scriptId, 
                          sceneManager->getCurrentScene()->id,
                          inventorySystem.get());
    }
    
    confirmationType = ConfirmationType::None;
    pendingActionItemIndex = -1;
}

void PlayingState::handleEvent(const sf::Event& event) {
    // Handle confirmation dialog input first
    if (confirmationType != ConfirmationType::None) {
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Y) {
                handleConfirmation(true);
            } else if (keyPressed->code == sf::Keyboard::Key::N) {
                handleConfirmation(false);
            }
        }
        return;
    }
    
    // Don't allow input during transition
    if (transitionState != TransitionState::None) {
        return;
    }
    
    // Handle inventory interactions (right-click to delete items)
    auto interaction = ui->handleInventoryEvent(event);

    if (interaction.action == InventoryAction::DeleteRequested) {
        showConfirmationDialog(interaction.removeAll ? ConfirmationType::ThrowOutAll : ConfirmationType::ThrowOut, 
                              interaction.itemIndex,
                              currentWindowSize, CustomWindow::getTitlebarHeight());
        return;
    }
    
    // Handle choice button clicks
    for (auto& button : choiceButtons) {
        button->handleEvent(event);
    }
    
    // Handle keyboard shortcuts for choices (A, B, C, D)
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        int choiceIndex = -1;
        
        switch (keyPressed->code) {
            case sf::Keyboard::Key::A: choiceIndex = 0; break;
            case sf::Keyboard::Key::B: choiceIndex = 1; break;
            case sf::Keyboard::Key::C: choiceIndex = 2; break;
            case sf::Keyboard::Key::D: choiceIndex = 3; break;
            default: break;
        }
        
        const Scene* currentScene = sceneManager->getCurrentScene();
        if (currentScene && choiceIndex >= 0 && 
            choiceIndex < static_cast<int>(currentScene->choices.size())) {
            const auto& choice = currentScene->choices[choiceIndex];
            if (!choice.nextScript.empty()) {
                sceneManager->loadScript(choice.nextScript);
                if (!sceneManager->getScript().scenes.empty()) {
                    startTransition(sceneManager->getScript().scenes[0].id);
                }
            } else {
                startTransition(choice.nextScene);
            }
        }
    }
}

void PlayingState::update(float deltaTime, sf::RenderWindow& window) {
    updateTransition(deltaTime);
    
    // Only update interactive elements when not transitioning or confirming
    if (transitionState == TransitionState::None && confirmationType == ConfirmationType::None) {
        auto mousePos = sf::Mouse::getPosition(window);
        
        for (auto& button : choiceButtons) {
            button->update(mousePos);
        }
        
        ui->updateInventory(mousePos);
    }
}

void PlayingState::draw(sf::RenderWindow& window) {
    auto& graphicsSprite = sceneManager->getGraphicsSprite();
    ui->draw(window, choiceButtons, graphicsSprite.get());
    
    // Draw transition overlay on top of everything
    if (transitionState != TransitionState::None) {
        window.draw(transitionOverlay);
    }
}