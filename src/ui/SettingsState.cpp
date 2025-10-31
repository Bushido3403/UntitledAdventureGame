#include "SettingsState.h"

SettingsState::SettingsState(ResourceManager& resources)
    : placeholderText(resources.getFont("main"), "Settings Menu (Coming Soon)", 48)
    , backText(resources.getFont("main"), "Press ESC to go back", 24)
{
    placeholderText.setFillColor(sf::Color::White);
    backText.setFillColor(sf::Color(200, 200, 200));
}

void SettingsState::updatePositions(const sf::Vector2u& windowSize)
{
    auto placeholderBounds = placeholderText.getLocalBounds();
    placeholderText.setOrigin({placeholderBounds.size.x / 2.f, placeholderBounds.size.y / 2.f});
    placeholderText.setPosition({windowSize.x / 2.f, windowSize.y / 2.f});
    
    auto backBounds = backText.getLocalBounds();
    backText.setOrigin({backBounds.size.x / 2.f, backBounds.size.y / 2.f});
    backText.setPosition({windowSize.x / 2.f, windowSize.y / 2.f + 100.f});
}

void SettingsState::setOnBackClicked(std::function<void()> callback)
{
    onBackClicked = callback;
}

void SettingsState::handleEvent(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Escape && onBackClicked)
        {
            onBackClicked();
        }
    }
}

void SettingsState::update(float deltaTime, sf::RenderWindow& window)
{
    // Nothing to update for now
}

void SettingsState::draw(sf::RenderWindow& window)
{
    window.draw(placeholderText);
    window.draw(backText);
}