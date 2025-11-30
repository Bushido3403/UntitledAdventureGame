// SFML 3.x

#include "MainMenuState.h"

MainMenuState::MainMenuState(ResourceManager& resources)
    : resources(resources),
      backgroundSprite(resources.getTexture("background")),
      logoSprite(resources.getTexture("logo")),
      titleSprite(resources.getTexture("title"))
{
    logoSprite.setScale({0.8f, 0.8f});
    titleSprite.setScale({0.8f, 0.8f});
    
    startButton = std::make_unique<Button>(resources, &resources.getTexture("start"), sf::Vector2f(0, 0));
    startButton->setScale({0.8f, 0.8f});
    
    settingsButton = std::make_unique<Button>(resources, &resources.getTexture("settings"), sf::Vector2f(0, 0));
    settingsButton->setScale({0.8f, 0.8f});
    
    // Initialize transition overlay
    transitionOverlay.setFillColor(sf::Color(0, 0, 0, 0));
}

void MainMenuState::updatePositions(const sf::Vector2u& windowSize)
{
    const sf::Texture* bgTexture = &backgroundSprite.getTexture();
    const auto ts = bgTexture->getSize();
    backgroundSprite.setScale(
        sf::Vector2f{
            static_cast<float>(windowSize.x) / static_cast<float>(ts.x),
            static_cast<float>(windowSize.y) / static_cast<float>(ts.y)
        }
    );
    
    logoSprite.setPosition(sf::Vector2f(20.f, 50.f));
    
    auto titleBounds = titleSprite.getLocalBounds();
    titleSprite.setOrigin({titleBounds.size.x / 2.f, titleBounds.size.y / 2.f});
    titleSprite.setPosition({windowSize.x / 2.f, windowSize.y / 3.f});
    
    startButton->setPosition({windowSize.x / 2.f, windowSize.y / 3.f + 125.f});
    settingsButton->setPosition({windowSize.x / 2.f, windowSize.y / 3.f + 250.f});
    
    // Update transition overlay size
    transitionOverlay.setSize(sf::Vector2f(static_cast<float>(windowSize.x), 
                                           static_cast<float>(windowSize.y)));
    transitionOverlay.setPosition({0.f, 0.f});
}

void MainMenuState::setOnStartClicked(std::function<void()> callback)
{
    onStartClicked = callback;
    startButton->setOnClick([this, callback]() {
        if (!isTransitioning) {
            isTransitioning = true;
            transitionAlpha = 0.f;
        }
    });
}

void MainMenuState::setOnSettingsClicked(std::function<void()> callback)
{
    onSettingsClicked = callback;
    settingsButton->setOnClick(callback);
}

void MainMenuState::handleEvent(const sf::Event& event)
{
    // Don't allow input during transition
    if (isTransitioning) {
        return;
    }
    
    startButton->handleEvent(event);
    settingsButton->handleEvent(event);
}

void MainMenuState::update(float deltaTime, sf::RenderWindow& window)
{
    // Update transition
    if (isTransitioning) {
        float alphaSpeed = 255.f / transitionDuration;
        transitionAlpha += alphaSpeed * deltaTime;
        
        if (transitionAlpha >= 255.f) {
            transitionAlpha = 255.f;
            
            // Trigger the actual state change
            if (onStartClicked) {
                onStartClicked();
            }
        }
        
        // Update overlay alpha
        sf::Color overlayColor = transitionOverlay.getFillColor();
        float clampedAlpha = transitionAlpha;
        if (clampedAlpha < 0.f) {
            clampedAlpha = 0.f;
        } else if (clampedAlpha > 255.f) {
            clampedAlpha = 255.f;
        }
        overlayColor.a = static_cast<std::uint8_t>(clampedAlpha);
        transitionOverlay.setFillColor(overlayColor);
    } else {
        // Only update buttons when not transitioning
        auto mousePos = sf::Mouse::getPosition(window);
        startButton->update(mousePos);
        settingsButton->update(mousePos);
    }
}

void MainMenuState::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    window.draw(logoSprite);
    window.draw(titleSprite);
    startButton->draw(window);
    settingsButton->draw(window);
    
    // Draw transition overlay on top of everything
    if (isTransitioning) {
        window.draw(transitionOverlay);
    }
}

void MainMenuState::resetTransition() {
    isTransitioning = false;
    transitionAlpha = 0.f;
    transitionOverlay.setFillColor(sf::Color(0, 0, 0, 0));
}