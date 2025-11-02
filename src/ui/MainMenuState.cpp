// SFML 3.x

#include "MainMenuState.h"

MainMenuState::MainMenuState(ResourceManager& resources)
    : resources(resources), // Store resources
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
}

void MainMenuState::setOnStartClicked(std::function<void()> callback)
{
    onStartClicked = callback;
    startButton->setOnClick(callback);
}

void MainMenuState::setOnSettingsClicked(std::function<void()> callback)
{
    onSettingsClicked = callback;
    settingsButton->setOnClick(callback);
}

void MainMenuState::handleEvent(const sf::Event& event)
{
    startButton->handleEvent(event);
    settingsButton->handleEvent(event);
}

void MainMenuState::update(float deltaTime, sf::RenderWindow& window)
{
    auto mousePos = sf::Mouse::getPosition(window);
    startButton->update(mousePos);
    settingsButton->update(mousePos);
}

void MainMenuState::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    window.draw(logoSprite);
    window.draw(titleSprite);
    startButton->draw(window);
    settingsButton->draw(window);
}