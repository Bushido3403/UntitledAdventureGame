// SFML 3.x

#include "PlayingState.h"
#include <iostream>

PlayingState::PlayingState(ResourceManager& resources, const std::string& scriptPath)
    : resources(resources),
      currentScene(nullptr),
      dialogText(resources.getFont("main"), "", 24),
      speakerText(resources.getFont("main"), "", 28),
      graphicsSprite(nullptr)
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

void PlayingState::updatePositions(const sf::Vector2u& windowSize) {
    const float BUFFER = 20.f; // Consistent buffer between all elements
    
    background.setSize(sf::Vector2f(static_cast<float>(windowSize.x), 
                                     static_cast<float>(windowSize.y)));
    
    // Dialog box at bottom of screen
    float boxHeight = 200.f;
    float boxWidth = static_cast<float>(windowSize.x) - (BUFFER * 2);
    dialogBox.setSize(sf::Vector2f(boxWidth, boxHeight));
    dialogBox.setPosition(sf::Vector2f(BUFFER, static_cast<float>(windowSize.y) - boxHeight - BUFFER));
    
    // Calculate graphics box dimensions (16:9 aspect ratio)
    float graphicsWidth = (static_cast<float>(windowSize.x) - (BUFFER * 3)) * 0.6f;
    float graphicsHeight = graphicsWidth * (9.f / 16.f);
    float graphicsY = static_cast<float>(windowSize.y) - boxHeight - graphicsHeight - (BUFFER * 2);
    
    graphicsBox.setSize(sf::Vector2f(graphicsWidth, graphicsHeight));
    graphicsBox.setPosition(sf::Vector2f(BUFFER, graphicsY));
    
    // Stats box on the right side
    float statsWidth = static_cast<float>(windowSize.x) - graphicsWidth - (BUFFER * 3);
    statsBox.setSize(sf::Vector2f(statsWidth, graphicsHeight));
    statsBox.setPosition(sf::Vector2f(graphicsWidth + (BUFFER * 2), graphicsY));
    
    // Speaker name inside dialog box at top-left
    speakerText.setPosition(sf::Vector2f(BUFFER + 10.f, static_cast<float>(windowSize.y) - boxHeight - BUFFER + 10.f));
    
    // Dialog text inside box, below speaker name
    dialogText.setPosition(sf::Vector2f(BUFFER + 10.f, static_cast<float>(windowSize.y) - boxHeight - BUFFER + 50.f));
    
    // Position choice texts
    float choiceStartY = static_cast<float>(windowSize.y) - boxHeight - BUFFER + 120.f;
    float choiceSpacing = 30.f;
    
    for (size_t i = 0; i < choiceTexts.size(); ++i) {
        choiceTexts[i].setPosition(sf::Vector2f(BUFFER + 20.f, choiceStartY + i * choiceSpacing));
    }
}

void PlayingState::setOnScriptComplete(std::function<void()> callback) {
    onScriptComplete = callback;
}

void PlayingState::handleEvent(const sf::Event& event) {
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