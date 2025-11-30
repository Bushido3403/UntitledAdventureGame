// SFML 3.x

#include "PlayingState.h"
#include "CustomWindow.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

// Constructor: Load saved data
PlayingState::PlayingState(ResourceManager& resources, const std::string& scriptPath)
    : resources(resources),
      sceneManager(std::make_unique<SceneManager>(resources)),
      dialogBox(std::make_unique<DialogBox>(resources.getFont("main"))),
      layoutManager(std::make_unique<LayoutManager>(sf::Vector2u(800, 600))),
      windowSize(800, 600)
{
    // Load save data first
    loadGame();
    
    // Initialize UI elements
    background.setFillColor(sf::Color(20, 20, 30));
    
    dialogBoxShape.setFillColor(sf::Color(40, 40, 50, 220));
    dialogBoxShape.setOutlineColor(sf::Color(100, 100, 120));
    dialogBoxShape.setOutlineThickness(2.f);
    
    graphicsBox.setFillColor(sf::Color(30, 30, 40));
    graphicsBox.setOutlineColor(sf::Color(100, 100, 120));
    graphicsBox.setOutlineThickness(2.f);
    
    statsBox.setFillColor(sf::Color(40, 40, 50, 220));
    statsBox.setOutlineColor(sf::Color(100, 100, 120));
    statsBox.setOutlineThickness(2.f);
    
    // Load script
    if (sceneManager->loadScript(scriptPath)) {
        loadScene(sceneManager->getScript().scenes[0].id);
    }
    
    // Initialize transition overlay
    transitionOverlay.setFillColor(sf::Color(0, 0, 0, 0));
    transitionOverlay.setSize(sf::Vector2f(800.f, 600.f));
}

bool PlayingState::checkCondition(const Condition& condition) const {
    if (condition.flag.empty()) {
        return true;  // No condition = always pass
    }
    
    auto it = flags.find(condition.flag);
    if (it == flags.end()) {
        return !condition.requiredValue;  // Flag doesn't exist
    }
    
    return it->second == condition.requiredValue;
}

void PlayingState::applyEffects(const Effects& effects) {
    // Add flag
    if (!effects.addFlag.empty()) {
        flags[effects.addFlag] = true;
    }
    
    // Remove flag (set to false)
    if (!effects.removeFlag.empty()) {
        flags[effects.removeFlag] = false;
    }
    
    // Modify stats
    for (const auto& [statName, modifier] : effects.modifyStats) {
        stats[statName] += modifier;
    }
    
    saveGame();
}

void PlayingState::saveGame() {
    using json = nlohmann::json;
    
    json saveData;
    saveData["playerName"] = "";  // TODO: Implement player naming
    saveData["currentScript"] = sceneManager->getScript().scriptId;
    
    const Scene* currentScene = sceneManager->getCurrentScene();
    if (currentScene) {
        saveData["currentScene"] = currentScene->id;
    }
    
    // Save flags
    json flagsJson = json::object();
    for (const auto& [key, value] : flags) {
        flagsJson[key] = value;
    }
    saveData["flags"] = flagsJson;
    
    // Save stats
    json statsJson = json::object();
    for (const auto& [key, value] : stats) {
        statsJson[key] = value;
    }
    saveData["stats"] = statsJson;
    
    // Write to file (FIXED PATH)
    std::ofstream file("assets/save_data.json");  // Changed from src/core/save_data.json
    if (file.is_open()) {
        file << saveData.dump(2);  // Pretty print with 2-space indent
        file.close();
        std::cout << "Game saved successfully" << std::endl;
    } else {
        std::cerr << "Failed to save game" << std::endl;
    }
}

void PlayingState::loadGame() {
    using json = nlohmann::json;
    
    std::ifstream file("assets/save_data.json");
    if (!file.is_open()) {
        std::cout << "No save file found, starting fresh" << std::endl;
        return;
    }
    
    try {
        json saveData;
        file >> saveData;
        
        // Check if the file was empty or contained invalid JSON
        if (saveData.is_null() || saveData.empty()) {
            std::cout << "Save file is empty, starting fresh" << std::endl;
            return;
        }
        
        // Load flags
        if (saveData.contains("flags") && saveData["flags"].is_object()) {
            for (auto& [key, value] : saveData["flags"].items()) {
                flags[key] = value;
            }
        }
        
        // Load stats
        if (saveData.contains("stats") && saveData["stats"].is_object()) {
            for (auto& [key, value] : saveData["stats"].items()) {
                stats[key] = value;
            }
        }
        
        std::cout << "Game loaded successfully" << std::endl;
    } catch (const json::exception& e) {
        std::cerr << "Failed to load save data: " << e.what() << std::endl;
        std::cout << "Starting fresh due to corrupted save" << std::endl;
    }
}

void PlayingState::setOnScriptComplete(std::function<void()> callback) {
    onScriptComplete = callback;
    sceneManager->setOnScriptComplete(callback);
}

void PlayingState::loadScene(const std::string& sceneId) {
    if (!sceneManager->loadScene(sceneId)) {
        return;
    }
    
    const Scene* currentScene = sceneManager->getCurrentScene();
    if (!currentScene) return;
    
    // Apply scene effects
    if (currentScene->effects.has_value()) {
        applyEffects(currentScene->effects.value());
    }
    
    // Calculate full window size (windowSize already has titlebar subtracted)
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    sf::Vector2u fullWindowSize(windowSize.x, windowSize.y + static_cast<unsigned int>(TITLEBAR_HEIGHT));
    auto metrics = layoutManager->calculate(fullWindowSize, TITLEBAR_HEIGHT);
    unsigned int dialogSize = layoutManager->getScaledCharacterSize(24, windowSize);
    
    float maxTextWidth = metrics.dialogBoxSize.x - (metrics.scale.boxPadding * 2);
    std::string wrappedText = DialogBox::wrapText(currentScene->text, 
                                                  static_cast<unsigned int>(maxTextWidth), 
                                                  resources.getFont("main"), 
                                                  dialogSize);
    
    dialogBox->setText(wrappedText, currentScene->speaker, currentScene->speakerColor);  // Pass speaker color
    
    createChoiceButtons();
    updatePositions(fullWindowSize);
}

void PlayingState::startTransition(const std::string& sceneId) {
    if (transitionState != TransitionState::None) {
        return;  // Already transitioning
    }
    
    nextSceneId = sceneId;
    transitionState = TransitionState::FadingOut;
    transitionAlpha = 0.f;
}

void PlayingState::updateTransition(float deltaTime) {
    if (transitionState == TransitionState::None) {
        return;
    }
    
    float alphaSpeed = 255.f / transitionDuration;
    
    if (transitionState == TransitionState::FadingOut) {
        transitionAlpha += alphaSpeed * deltaTime;
        
        if (transitionAlpha >= 255.f) {
            transitionAlpha = 255.f;
            
            // Load the new scene while screen is black
            loadScene(nextSceneId);
            nextSceneId.clear();
            
            // Start fading in
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
    
    // Update overlay color
    sf::Color overlayColor = transitionOverlay.getFillColor();
    overlayColor.a = static_cast<std::uint8_t>(std::clamp(transitionAlpha, 0.f, 255.f));
    transitionOverlay.setFillColor(overlayColor);
}

void PlayingState::createChoiceButtons() {
    choiceButtons.clear();
    
    const Scene* currentScene = sceneManager->getCurrentScene();
    if (!currentScene) return;
    
    const char labels[] = {'a', 'b', 'c', 'd'};
    size_t labelIndex = 0;
    
    for (size_t i = 0; i < currentScene->choices.size() && labelIndex < 4; ++i) {
        const auto& choice = currentScene->choices[i];
        
        // Check condition - skip this choice if condition fails
        if (choice.condition.has_value() && !checkCondition(choice.condition.value())) {
            continue;
        }
        
        auto button = std::make_unique<Button>(resources, nullptr, sf::Vector2f(0, 0));
        button->setText(std::string(1, labels[labelIndex]) + ") " + choice.text, 
                       resources.getFont("main"), 22);
        
        std::string nextScene = choice.nextScene;
        std::string nextScript = choice.nextScript;
        
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

void PlayingState::updateChoicePositions() {
    const Scene* currentScene = sceneManager->getCurrentScene();
    if (!currentScene || choiceButtons.empty()) return;
    
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    sf::Vector2u fullWindowSize(windowSize.x, windowSize.y + static_cast<unsigned int>(TITLEBAR_HEIGHT));
    auto metrics = layoutManager->calculate(fullWindowSize, TITLEBAR_HEIGHT);
    
    // Update button text sizes
    unsigned int choiceSize = layoutManager->getScaledCharacterSize(22, windowSize);
    for (auto& button : choiceButtons) {
        button->setTextSize(choiceSize);
    }
    
    sf::FloatRect dialogBoxBounds = dialogBoxShape.getGlobalBounds();
    
    float baseChoiceSpacing = 35.f;
    float choiceSpacing = baseChoiceSpacing * metrics.scale.scaleY;
    
    size_t numChoices = choiceButtons.size();
    bool useTwoColumns = numChoices > 2;
    
    float totalChoiceHeight;
    if (useTwoColumns) {
        // Calculate rows needed (3 choices per column max)
        size_t rows = (numChoices + 1) / 2;  // Ceiling division
        totalChoiceHeight = (rows - 1) * choiceSpacing;
        if (!choiceButtons.empty()) {
            totalChoiceHeight += choiceButtons[0]->getBounds().size.y;
        }
    } else {
        // Single column
        totalChoiceHeight = (numChoices - 1) * choiceSpacing;
        if (!choiceButtons.empty()) {
            totalChoiceHeight += choiceButtons[0]->getBounds().size.y;
        }
    }
    
    // Position choices from the bottom of the dialog box, working upward
    float dialogBoxBottom = dialogBoxBounds.position.y + dialogBoxBounds.size.y;
    float choiceStartY = dialogBoxBottom - totalChoiceHeight - metrics.scale.boxPadding;
    
    // Position buttons
    if (useTwoColumns) {
        float columnWidth = (metrics.dialogBoxSize.x - (metrics.scale.boxPadding * 3)) / 2.f;
        float leftColumnX = dialogBoxShape.getPosition().x + metrics.scale.boxPadding;
        float rightColumnX = leftColumnX + columnWidth + metrics.scale.boxPadding;
        
        for (size_t i = 0; i < choiceButtons.size(); ++i) {
            size_t row = i / 2;
            bool isLeftColumn = (i % 2 == 0);
            
            float xPos = isLeftColumn ? leftColumnX : rightColumnX;
            float yPos = choiceStartY + row * choiceSpacing;
            choiceButtons[i]->setPosition(sf::Vector2f(xPos, yPos));
        }
    } else {
        // Single column layout
        float xPos = dialogBoxShape.getPosition().x + metrics.scale.boxPadding;
        for (size_t i = 0; i < choiceButtons.size(); ++i) {
            float yPos = choiceStartY + i * choiceSpacing;
            choiceButtons[i]->setPosition(sf::Vector2f(xPos, yPos));
        }
    }
    
    // Now shrink dialog text if it overlaps with choices
    sf::FloatRect dialogTextBounds = dialogBox->getTextBounds();
    float textBottomY = dialogTextBounds.position.y + dialogTextBounds.size.y;
    float baseTextToChoiceGap = 20.f;
    float textToChoiceGap = baseTextToChoiceGap * metrics.scale.scaleY;
    float requiredTextEndY = choiceStartY - textToChoiceGap;
    
    if (textBottomY > requiredTextEndY) {
        unsigned int currentSize = dialogBox->getDialogText().getCharacterSize();
        unsigned int minSize = static_cast<unsigned int>(12 * metrics.scale.minScale);
        
        while (currentSize > minSize && textBottomY > requiredTextEndY) {
            currentSize -= 1;
            
            float maxTextWidth = metrics.dialogBoxSize.x - (metrics.scale.boxPadding * 2);
            std::string wrappedText = DialogBox::wrapText(currentScene->text, 
                                                         static_cast<unsigned int>(maxTextWidth), 
                                                         resources.getFont("main"), 
                                                         currentSize);
            
            dialogBox->getDialogText().setCharacterSize(currentSize);
            dialogBox->getDialogText().setString(wrappedText);
            
            dialogTextBounds = dialogBox->getTextBounds();
            textBottomY = dialogTextBounds.position.y + dialogTextBounds.size.y;
        }
    }
}

void PlayingState::updatePositions(const sf::Vector2u& newWindowSize) {
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    windowSize = sf::Vector2u(newWindowSize.x, 
                              newWindowSize.y - static_cast<unsigned int>(TITLEBAR_HEIGHT));
    
    // Update transition overlay size
    transitionOverlay.setSize(sf::Vector2f(static_cast<float>(newWindowSize.x), 
                                           static_cast<float>(newWindowSize.y) - TITLEBAR_HEIGHT));
    transitionOverlay.setPosition({0.f, TITLEBAR_HEIGHT});
    
    auto metrics = layoutManager->calculate(newWindowSize, TITLEBAR_HEIGHT);
    
    background.setSize(sf::Vector2f(static_cast<float>(newWindowSize.x), 
                                     static_cast<float>(newWindowSize.y) - TITLEBAR_HEIGHT));
    background.setPosition({0.f, TITLEBAR_HEIGHT});
    
    graphicsBox.setSize(metrics.graphicsBoxSize);
    graphicsBox.setPosition(metrics.graphicsBoxPos);
    
    statsBox.setSize(metrics.statsBoxSize);
    statsBox.setPosition(metrics.statsBoxPos);
    
    dialogBoxShape.setSize(metrics.dialogBoxSize);
    dialogBoxShape.setPosition(metrics.dialogBoxPos);
    
    // Update dialog box layout
    unsigned int dialogSize = layoutManager->getScaledCharacterSize(24, windowSize);
    unsigned int speakerSize = layoutManager->getScaledCharacterSize(28, windowSize);
    
    sf::FloatRect dialogBounds(metrics.dialogBoxPos, metrics.dialogBoxSize);
    dialogBox->updateLayout(dialogBounds, metrics.scale.boxPadding, 
                           metrics.scale.scaleY, dialogSize, speakerSize);
    
    // Re-wrap text
    const Scene* currentScene = sceneManager->getCurrentScene();
    if (currentScene) {
        float maxTextWidth = metrics.dialogBoxSize.x - (metrics.scale.boxPadding * 2);
        std::string wrappedText = DialogBox::wrapText(currentScene->text, 
                                                      static_cast<unsigned int>(maxTextWidth), 
                                                      resources.getFont("main"), 
                                                      dialogSize);
        dialogBox->setText(wrappedText, currentScene->speaker, currentScene->speakerColor);  // Pass speaker color
        dialogBox->updateLayout(dialogBounds, metrics.scale.boxPadding, 
                               metrics.scale.scaleY, dialogSize, speakerSize);
    }
    
    // Update choice positions
    updateChoicePositions();
}

void PlayingState::handleEvent(const sf::Event& event) {
    // Don't allow input during transitions
    if (transitionState != TransitionState::None) {
        return;
    }
    
    for (auto& button : choiceButtons) {
        button->handleEvent(event);
    }
    
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
    
    // Don't update buttons during transitions
    if (transitionState == TransitionState::None) {
        auto mousePos = sf::Mouse::getPosition(window);
        
        for (auto& button : choiceButtons) {
            button->update(mousePos);
        }
    }
}

void PlayingState::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(graphicsBox);
    
    auto& graphicsSprite = sceneManager->getGraphicsSprite();
    if (graphicsSprite) {
        sf::FloatRect texBounds = graphicsSprite->getLocalBounds();
        float graphicsWidth = graphicsBox.getSize().x;
        float graphicsHeight = graphicsBox.getSize().y;
        float scaleX = graphicsWidth / texBounds.size.x;
        float scaleY = graphicsHeight / texBounds.size.y;
        float scale = std::min(scaleX, scaleY);
        graphicsSprite->setScale(sf::Vector2f(scale, scale));
        
        sf::Vector2f spriteSize(texBounds.size.x * scale, texBounds.size.y * scale);
        sf::Vector2f boxPos = graphicsBox.getPosition();
        sf::Vector2f boxSize = graphicsBox.getSize();
        sf::Vector2f centeredPos(
            boxPos.x + (boxSize.x - spriteSize.x) / 2.f,
            boxPos.y + (boxSize.y - spriteSize.y) / 2.f
        );
        graphicsSprite->setPosition(centeredPos);
        
        window.draw(*graphicsSprite);
    }
    
    window.draw(statsBox);
    window.draw(dialogBoxShape);
    dialogBox->draw(window);
    
    for (auto& button : choiceButtons) {
        button->draw(window);
    }
    
    // Draw transition overlay last (on top of everything)
    if (transitionState != TransitionState::None) {
        window.draw(transitionOverlay);
    }
}