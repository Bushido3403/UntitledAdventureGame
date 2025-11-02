// SFML 3.x

#include "PlayingState.h"
#include "CustomWindow.h"
#include <iostream>
#include <sstream>

PlayingState::PlayingState(ResourceManager& resources, const std::string& scriptPath)
    : resources(resources),
      currentScene(nullptr),
      dialogText(resources.getFont("main"), "", 24),
      speakerText(resources.getFont("main"), "", 28),
      graphicsSprite(nullptr),
      windowSize(800, 600),
      baseWindowSize(800, 600),  // Set base reference size
      currentScriptPath(scriptPath)
{
    auto scriptOpt = ScriptParser::loadScript(scriptPath);
    if (!scriptOpt) {
        std::cerr << "Failed to load script: " << scriptPath << std::endl;
        return;
    }
    
    script = *scriptOpt;
    
    // Log script info
    std::cout << "Loaded script: " << script.title 
              << " (Chapter " << script.metadata.chapter << ")" << std::endl;
    
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

unsigned int PlayingState::getScaledCharacterSize(unsigned int baseSize) const {
    // Calculate scale factor based on window width (or height, or average)
    float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(baseWindowSize.x);
    float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(baseWindowSize.y);
    
    // Use the smaller scale to ensure text fits
    float scale = std::min(scaleX, scaleY);
    
    // Clamp the scale to reasonable bounds (e.g., 0.5x to 2.0x)
    scale = std::max(0.5f, std::min(2.0f, scale));
    
    return static_cast<unsigned int>(baseSize * scale);
}

void PlayingState::updateTextSizes() {
    // Update dialog text size
    unsigned int dialogSize = getScaledCharacterSize(24);
    dialogText.setCharacterSize(dialogSize);
    
    // Update speaker text size
    unsigned int speakerSize = getScaledCharacterSize(28);
    speakerText.setCharacterSize(speakerSize);
    
    // Update choice button text sizes
    unsigned int choiceSize = getScaledCharacterSize(22);
    for (auto& button : choiceButtons) {
        button->setTextSize(choiceSize);
    }
}

std::string PlayingState::wrapText(const std::string& text, unsigned int maxWidth, const sf::Font& font, unsigned int characterSize) {
    std::istringstream words(text);
    std::ostringstream wrapped;
    std::string word;
    std::string line;
    
    sf::Text testText(font, "", characterSize);
    
    while (words >> word) {
        std::string testLine = line.empty() ? word : line + " " + word;
        testText.setString(testLine);
        
        if (testText.getLocalBounds().size.x > maxWidth) {
            if (!line.empty()) {
                wrapped << line << "\n";
                line = word;
            } else {
                // Word is too long, force it on its own line
                wrapped << word << "\n";
                line = "";
            }
        } else {
            line = testLine;
        }
    }
    
    if (!line.empty()) {
        wrapped << line;
    }
    
    return wrapped.str();
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
    
    // Wrap the dialog text with scaled character size
    unsigned int dialogSize = getScaledCharacterSize(24);
    float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(baseWindowSize.x);
    float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(baseWindowSize.y);
    float boxPadding = 10.f * std::min(scaleX, scaleY);
    float maxTextWidth = dialogBox.getSize().x - (boxPadding * 2);
    
    std::string wrappedText = wrapText(currentScene->text, static_cast<unsigned int>(maxTextWidth), 
                                       resources.getFont("main"), dialogSize);
    dialogText.setString(wrappedText);
    
    // Load scene graphic
    if (!currentScene->background.empty()) {
        try {
            sf::Texture& texture = resources.getTexture(currentScene->background);
            graphicsSprite = std::make_unique<sf::Sprite>(texture);
        } catch (const std::out_of_range&) {
            std::string texturePath = "assets/images/" + currentScene->background + ".jpg";
            if (resources.loadTexture(currentScene->background, texturePath)) {
                graphicsSprite = std::make_unique<sf::Sprite>(resources.getTexture(currentScene->background));
            } else {
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
    updateChoicePositions();
}

void PlayingState::loadNextScript(const std::string& nextScriptPath) {
    std::cout << "Loading next script: " << nextScriptPath << std::endl;
    
    auto scriptOpt = ScriptParser::loadScript(nextScriptPath);
    if (!scriptOpt) {
        std::cerr << "Failed to load next script: " << nextScriptPath << std::endl;
        if (onScriptComplete) {
            onScriptComplete();
        }
        return;
    }
    
    script = *scriptOpt;
    currentScriptPath = nextScriptPath;
    
    std::cout << "Loaded script: " << script.title 
              << " (Chapter " << script.metadata.chapter << ")" << std::endl;
    
    if (!script.scenes.empty()) {
        loadScene(script.scenes[0].id);
    }
}

void PlayingState::createChoiceTexts() {
    choiceTexts.clear();
    choiceButtons.clear();
    
    if (!currentScene) return;
    
    const char labels[] = {'a', 'b', 'c', 'd'};
    unsigned int choiceSize = getScaledCharacterSize(22);
    
    for (size_t i = 0; i < currentScene->choices.size() && i < 4; ++i) {
        const auto& choice = currentScene->choices[i];
        
        auto button = std::make_unique<Button>(resources, nullptr, sf::Vector2f(0, 0));
        
        button->setText(std::string(1, labels[i]) + ") " + choice.text, resources.getFont("main"), choiceSize);
        button->setPosition(sf::Vector2f(0, 0));
        
        std::string nextScene = choice.nextScene;
        std::string nextScript = choice.nextScript;
        
        button->setOnClick([this, nextScene, nextScript]() {
            if (!nextScript.empty()) {
                loadNextScript(nextScript);
            } else {
                pendingSceneId = nextScene;
            }
        });
        
        choiceButtons.push_back(std::move(button));
    }
    
    updateChoicePositions();
}

void PlayingState::updateChoicePositions() {
    if (!currentScene) return;
    
    const float BUFFER = 20.f;
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    
    // Calculate scale factors
    float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(baseWindowSize.x);
    float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(baseWindowSize.y);
    float boxPadding = 10.f * std::min(scaleX, scaleY);
    
    // Get dialog text bounds to position choices below it
    sf::FloatRect dialogTextBounds = dialogText.getGlobalBounds();
    
    // Calculate starting Y position for choices (below the wrapped text)
    float baseChoiceSpacing = 35.f;  // Space between choices
    float baseTextToChoiceGap = 20.f;  // Gap between text and first choice
    
    float choiceSpacing = baseChoiceSpacing * scaleY;
    float textToChoiceGap = baseTextToChoiceGap * scaleY;
    
    // Start choices below the dialogue text
    float choiceStartY = dialogTextBounds.position.y + dialogTextBounds.size.y + textToChoiceGap;
    
    // Get dialog box bounds to check if choices fit
    sf::FloatRect dialogBoxBounds = dialogBox.getGlobalBounds();
    float dialogBoxBottom = dialogBoxBounds.position.y + dialogBoxBounds.size.y;
    
    // Calculate total height needed for all choices
    float totalChoiceHeight = (choiceButtons.size() - 1) * choiceSpacing;
    if (!choiceButtons.empty()) {
        // Estimate choice button height (use first button as reference)
        sf::FloatRect firstChoiceBounds = choiceButtons[0]->getBounds();
        totalChoiceHeight += firstChoiceBounds.size.y;
    }
    
    float choicesEndY = choiceStartY + totalChoiceHeight + boxPadding;
    
    // If choices would overflow, shrink the dialog text
    if (choicesEndY > dialogBoxBottom) {
        std::cout << "Text too large, shrinking to fit choices..." << std::endl;
        
        // Reduce text size until it fits
        unsigned int currentSize = dialogText.getCharacterSize();
        unsigned int minSize = static_cast<unsigned int>(12 * std::min(scaleX, scaleY));
        
        while (currentSize > minSize && choicesEndY > dialogBoxBottom) {
            currentSize -= 1;
            dialogText.setCharacterSize(currentSize);
            
            // Re-wrap with new size
            std::string wrappedText = wrapText(currentScene->text, 
                                               static_cast<unsigned int>(dialogBox.getSize().x - (boxPadding * 2)), 
                                               resources.getFont("main"), 
                                               currentSize);
            dialogText.setString(wrappedText);
            
            // Recalculate positions
            dialogTextBounds = dialogText.getGlobalBounds();
            choiceStartY = dialogTextBounds.position.y + dialogTextBounds.size.y + textToChoiceGap;
            choicesEndY = choiceStartY + totalChoiceHeight + boxPadding;
        }
    }
    
    // Position all choice buttons with consistent padding
    for (size_t i = 0; i < choiceButtons.size(); ++i) {
        float xPos = dialogBox.getPosition().x + boxPadding;
        choiceButtons[i]->setPosition(sf::Vector2f(xPos, choiceStartY + i * choiceSpacing));
    }
}

void PlayingState::updatePositions(const sf::Vector2u& newWindowSize) {
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    windowSize = sf::Vector2u(newWindowSize.x, 
                              newWindowSize.y - static_cast<unsigned int>(TITLEBAR_HEIGHT));
    const float BUFFER = 20.f;
    
    // Update text sizes based on new window size
    updateTextSizes();
    
    background.setSize(sf::Vector2f(static_cast<float>(newWindowSize.x), 
                                     static_cast<float>(newWindowSize.y) - TITLEBAR_HEIGHT));
    background.setPosition({0.f, TITLEBAR_HEIGHT});
    
    // Calculate scale factor for positioning
    float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(baseWindowSize.x);
    float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(baseWindowSize.y);
    float scaledBuffer = BUFFER * std::min(scaleX, scaleY);
    float boxPadding = 10.f * std::min(scaleX, scaleY);  // Consistent internal padding
    
    float availableHeight = static_cast<float>(windowSize.y) - scaledBuffer * 2;
    
    // Calculate graphics box dimensions (maintain 16:9 aspect ratio)
    float graphicsWidth = (static_cast<float>(windowSize.x) - (scaledBuffer * 3)) * 0.6f;
    float graphicsHeight = graphicsWidth * (9.f / 16.f);
    
    // Reserve space for dialog box (scale the minimum height)
    float baseMinDialogHeight = 200.f;
    float minDialogHeight = baseMinDialogHeight * scaleY;
    float maxGraphicsHeight = availableHeight - minDialogHeight - scaledBuffer;
    
    // Limit graphics height if needed
    if (graphicsHeight > maxGraphicsHeight) {
        graphicsHeight = maxGraphicsHeight;
        graphicsWidth = graphicsHeight * (16.f / 9.f);
    }
    
    float graphicsY = TITLEBAR_HEIGHT + scaledBuffer;
    
    graphicsBox.setSize(sf::Vector2f(graphicsWidth, graphicsHeight));
    graphicsBox.setPosition(sf::Vector2f(scaledBuffer, graphicsY));
    
    // Stats box on the right side
    float statsWidth = static_cast<float>(windowSize.x) - graphicsWidth - (scaledBuffer * 3);
    statsBox.setSize(sf::Vector2f(statsWidth, graphicsHeight));
    statsBox.setPosition(sf::Vector2f(graphicsWidth + (scaledBuffer * 2), graphicsY));
    
    // Dialog box fills remaining vertical space below graphics
    float dialogBoxY = graphicsHeight + graphicsY + scaledBuffer;
    float boxHeight = static_cast<float>(newWindowSize.y) - dialogBoxY - scaledBuffer - TITLEBAR_HEIGHT;
    float boxWidth = static_cast<float>(windowSize.x) - (scaledBuffer * 2);
    
    dialogBox.setSize(sf::Vector2f(boxWidth, boxHeight));
    dialogBox.setPosition(sf::Vector2f(scaledBuffer, dialogBoxY));
    
    // Position speaker and dialog text inside dialog box with CONSISTENT padding
    speakerText.setPosition(sf::Vector2f(dialogBox.getPosition().x + boxPadding, 
                                         dialogBoxY + boxPadding));
    
    // Dialog text below speaker with consistent spacing
    float speakerHeight = speakerText.getGlobalBounds().size.y;
    float speakerToTextGap = 10.f * scaleY;
    
    dialogText.setPosition(sf::Vector2f(dialogBox.getPosition().x + boxPadding, 
                                       dialogBoxY + boxPadding + speakerHeight + speakerToTextGap));
    
    // Re-wrap text with new box width and scaled character size
    if (currentScene) {
        unsigned int dialogSize = getScaledCharacterSize(24);
        float maxTextWidth = dialogBox.getSize().x - (boxPadding * 2);
        std::string wrappedText = wrapText(currentScene->text, static_cast<unsigned int>(maxTextWidth), 
                                           resources.getFont("main"), dialogSize);
        dialogText.setString(wrappedText);
    }
    
    // Update choice positions AFTER text has been wrapped and positioned
    updateChoicePositions();
}

void PlayingState::setOnScriptComplete(std::function<void()> callback) {
    onScriptComplete = callback;
}

void PlayingState::setOnScriptChain(std::function<void(const std::string&)> callback) {
    onScriptChain = callback;
}

void PlayingState::handleEvent(const sf::Event& event) {
    for (auto& button : choiceButtons) {
        button->handleEvent(event);
    }
    
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
        
        if (currentScene && choiceIndex >= 0 && choiceIndex < static_cast<int>(currentScene->choices.size())) {
            const auto& choice = currentScene->choices[choiceIndex];
            if (!choice.nextScript.empty()) {
                loadNextScript(choice.nextScript);
            } else {
                loadScene(choice.nextScene);
            }
        }
    }
}

void PlayingState::update(float deltaTime, sf::RenderWindow& window) {
    auto mousePos = sf::Mouse::getPosition(window);
    
    for (auto& button : choiceButtons) {
        button->update(mousePos);
    }
    
    if (!pendingSceneId.empty()) {
        std::string sceneToLoad = pendingSceneId;
        pendingSceneId.clear();
        loadScene(sceneToLoad);
    }
}

void PlayingState::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(graphicsBox);
    
    if (graphicsSprite) {
        sf::FloatRect texBounds = graphicsSprite->getLocalBounds();
        float graphicsWidth = graphicsBox.getSize().x;
        float graphicsHeight = graphicsBox.getSize().y;
        float scaleX = graphicsWidth / texBounds.size.x;
        float scaleY = graphicsHeight / texBounds.size.y;
        float scale = std::min(scaleX, scaleY);
        graphicsSprite->setScale(sf::Vector2f(scale, scale));
        
        // Center the sprite in the graphics box
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
    window.draw(dialogBox);
    window.draw(speakerText);
    window.draw(dialogText);
    
    for (auto& button : choiceButtons) {
        button->draw(window);
    }
}