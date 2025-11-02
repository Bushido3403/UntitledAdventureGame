// SFML 3.x

#include "PlayingState.h"
#include "CustomWindow.h"
#include <iostream>

PlayingState::PlayingState(ResourceManager& resources, const std::string& scriptPath)
    : resources(resources),
      currentScene(nullptr),
      dialogText(resources.getFont("main"), "", 24),
      speakerText(resources.getFont("main"), "", 28),
      graphicsSprite(nullptr),
      windowSize(800, 600) // Default size
{
    auto scriptOpt = ScriptParser::loadScript(scriptPath);
    if (!scriptOpt) {
        std::cerr << "Failed to load script: " << scriptPath << std::endl;
        return;
    }
    
    script = *scriptOpt;
    
    // Initialize UI elements
    background.setFillColor(sf::Color(20, 20, 30));
    
    dialogBox.setFillColor(sf::Color(40, 40, 50, 220));
    dialogBox.setOutlineColor(sf::Color(100, 100, 120));
    dialogBox.setOutlineThickness(2.f);
    
    dialogText.setFillColor(sf::Color::White);
    speakerText.setFillColor(sf::Color(200, 200, 100));
    
    // Initialize graphics box
    graphicsBox.setFillColor(sf::Color(30, 30, 40));
    graphicsBox.setOutlineColor(sf::Color(100, 100, 120));
    graphicsBox.setOutlineThickness(2.f);
    
    // Initialize stats box
    statsBox.setFillColor(sf::Color(40, 40, 50, 220));
    statsBox.setOutlineColor(sf::Color(100, 100, 120));
    statsBox.setOutlineThickness(2.f);
    
    // Load first scene
    if (!script.scenes.empty()) {
        loadScene(script.scenes[0].id);
    }
}

void PlayingState::loadScene(const std::string& sceneId) {
    if (sceneId == "END") {
        if (onScriptComplete) {
            onScriptComplete();
        }
        return;
    }
    
    currentScene = ScriptParser::findScene(script, sceneId);
    if (!currentScene) {
        std::cerr << "Scene not found: " << sceneId << std::endl;
        return;
    }
    
    speakerText.setString("[" + currentScene->speaker + "]");
    dialogText.setString(currentScene->text);
    
    // Load scene graphic
    if (!currentScene->background.empty()) {
        // Try to get existing texture, or load it if not found
        try {
            sf::Texture& texture = resources.getTexture(currentScene->background);
            graphicsSprite = std::make_unique<sf::Sprite>(texture);
        } catch (const std::out_of_range&) {
            // Texture not loaded, try to load it dynamically
            std::string texturePath = "assets/images/" + currentScene->background + ".jpg";
            if (resources.loadTexture(currentScene->background, texturePath)) {
                graphicsSprite = std::make_unique<sf::Sprite>(resources.getTexture(currentScene->background));
            } else {
                // Try .png extension
                texturePath = "assets/images/" + currentScene->background + ".png";
                if (resources.loadTexture(currentScene->background, texturePath)) {
                    graphicsSprite = std::make_unique<sf::Sprite>(resources.getTexture(currentScene->background));
                } else {
                    std::cerr << "Failed to load texture: " << currentScene->background << std::endl;
                    graphicsSprite.reset();
                }
            }
        }
    } else {
        graphicsSprite.reset();
    }
    
    createChoiceTexts();
    updateChoicePositions(); // Update positions after creating choices
}

void PlayingState::createChoiceTexts() {
    choiceTexts.clear();
    choiceNextScenes.clear();
    
    if (!currentScene) return;
    
    const char labels[] = {'a', 'b', 'c', 'd'};
    
    for (size_t i = 0; i < currentScene->choices.size() && i < 4; ++i) {
        const auto& choice = currentScene->choices[i];
        
        sf::Text choiceText(resources.getFont("main"), "", 22);
        choiceText.setString(std::string(1, labels[i]) + ") " + choice.text);
        choiceText.setFillColor(sf::Color(180, 180, 200));
        
        choiceTexts.push_back(choiceText);
        choiceNextScenes.push_back(choice.nextScene);
    }
}

void PlayingState::updateChoicePositions() {
    const float BUFFER = 20.f;
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    float graphicsWidth = (static_cast<float>(windowSize.x) - (BUFFER * 3)) * 0.6f;
    float graphicsHeight = graphicsWidth * (9.f / 16.f);
    float graphicsY = TITLEBAR_HEIGHT + BUFFER;
    float dialogBoxY = graphicsHeight + graphicsY + BUFFER;
    
    float choiceStartY = dialogBoxY + 120.f; // Start below dialog text
    float choiceSpacing = 30.f;
    
    for (size_t i = 0; i < choiceTexts.size(); ++i) {
        choiceTexts[i].setPosition(sf::Vector2f(BUFFER + 20.f, choiceStartY + i * choiceSpacing));
    }
}

void PlayingState::updatePositions(const sf::Vector2u& newWindowSize) {
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    windowSize = sf::Vector2u(newWindowSize.x, 
                              newWindowSize.y - static_cast<unsigned int>(TITLEBAR_HEIGHT));
    const float BUFFER = 20.f; // Consistent buffer between all elements
    
    // Background should start below titlebar
    background.setSize(sf::Vector2f(static_cast<float>(newWindowSize.x), 
                                     static_cast<float>(newWindowSize.y) - TITLEBAR_HEIGHT));
    background.setPosition({0.f, TITLEBAR_HEIGHT});
    
    // Calculate available space for graphics
    float availableHeight = static_cast<float>(windowSize.y) - BUFFER * 2;
    
    // Calculate graphics box dimensions (16:9 aspect ratio)
    float graphicsWidth = (static_cast<float>(windowSize.x) - (BUFFER * 3)) * 0.6f;
    float graphicsHeight = graphicsWidth * (9.f / 16.f);
    
    // Reserve space for dialog box (at least 200px)
    float minDialogHeight = 200.f;
    float maxGraphicsHeight = availableHeight - minDialogHeight - BUFFER;
    
    // Limit graphics height if needed
    if (graphicsHeight > maxGraphicsHeight) {
        graphicsHeight = maxGraphicsHeight;
        graphicsWidth = graphicsHeight * (16.f / 9.f);
    }
    
    float graphicsY = TITLEBAR_HEIGHT + BUFFER;
    
    graphicsBox.setSize(sf::Vector2f(graphicsWidth, graphicsHeight));
    graphicsBox.setPosition(sf::Vector2f(BUFFER, graphicsY));
    
    // Stats box on the right side
    float statsWidth = static_cast<float>(windowSize.x) - graphicsWidth - (BUFFER * 3);
    statsBox.setSize(sf::Vector2f(statsWidth, graphicsHeight));
    statsBox.setPosition(sf::Vector2f(graphicsWidth + (BUFFER * 2), graphicsY));
    
    // Dialog box fills remaining vertical space below graphics
    float dialogBoxY = graphicsHeight + graphicsY + BUFFER;
    float boxHeight = static_cast<float>(newWindowSize.y) - dialogBoxY - BUFFER;
    float boxWidth = static_cast<float>(windowSize.x) - (BUFFER * 2);
    
    dialogBox.setSize(sf::Vector2f(boxWidth, boxHeight));
    dialogBox.setPosition(sf::Vector2f(BUFFER, dialogBoxY));
    
    // Speaker name inside dialog box at top-left
    speakerText.setPosition(sf::Vector2f(BUFFER + 10.f, dialogBoxY + 10.f));
    
    // Dialog text inside box, below speaker name
    dialogText.setPosition(sf::Vector2f(BUFFER + 10.f, dialogBoxY + 50.f));
    
    // Update choice positions
    updateChoicePositions();
}

void PlayingState::setOnScriptComplete(std::function<void()> callback) {
    onScriptComplete = callback;
}

void PlayingState::handleEvent(const sf::Event& event) {
    // Handle mouse clicks
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(static_cast<float>(mouseButtonPressed->position.x), 
                                  static_cast<float>(mouseButtonPressed->position.y));
        
            for (size_t i = 0; i < choiceTexts.size(); ++i) {
                sf::FloatRect bounds = choiceTexts[i].getGlobalBounds();
                if (bounds.contains(mousePos)) {
                    loadScene(choiceNextScenes[i]);
                    break;
                }
            }
        }
    }
    
    // Handle keyboard input
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        int choiceIndex = -1;
        
        switch (keyPressed->code) {
            case sf::Keyboard::Key::A:
                choiceIndex = 0;
                break;
            case sf::Keyboard::Key::B:
                choiceIndex = 1;
                break;
            case sf::Keyboard::Key::C:
                choiceIndex = 2;
                break;
            case sf::Keyboard::Key::D:
                choiceIndex = 3;
                break;
            default:
                break;
        }
        
        if (choiceIndex >= 0 && choiceIndex < static_cast<int>(choiceNextScenes.size())) {
            loadScene(choiceNextScenes[choiceIndex]);
        }
    }
}

void PlayingState::update(float deltaTime, sf::RenderWindow& window) {
    auto mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    // Update choice text colors on hover
    for (auto& choiceText : choiceTexts) {
        sf::FloatRect bounds = choiceText.getGlobalBounds();
        if (bounds.contains(mousePosF)) {
            choiceText.setFillColor(sf::Color(255, 255, 150)); // Highlight color
        } else {
            choiceText.setFillColor(sf::Color(180, 180, 200)); // Normal color
        }
    }
}

void PlayingState::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(graphicsBox);
    
    // Draw graphics sprite if available
    if (graphicsSprite) {
        sf::FloatRect texBounds = graphicsSprite->getLocalBounds();
        float graphicsWidth = graphicsBox.getSize().x;
        float graphicsHeight = graphicsBox.getSize().y;
        float scaleX = graphicsWidth / texBounds.size.x;
        float scaleY = graphicsHeight / texBounds.size.y;
        float scale = std::min(scaleX, scaleY);
        graphicsSprite->setScale(sf::Vector2f(scale, scale));
        graphicsSprite->setPosition(graphicsBox.getPosition());
        window.draw(*graphicsSprite);
    }
    
    window.draw(statsBox);
    window.draw(dialogBox);
    window.draw(speakerText);
    window.draw(dialogText);
    
    // Draw choice texts
    for (auto& choiceText : choiceTexts) {
        window.draw(choiceText);
    }
}