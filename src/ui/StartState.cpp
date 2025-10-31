// SFML 3.x

#include "StartState.h"

StartState::StartState(ResourceManager& resources)
    : placeholderText(resources.getFont("main"), "Game Starting... (Placeholder)", 48)
    , backText(resources.getFont("main"), "Press ESC to return to menu", 24)
{
    placeholderText.setFillColor(sf::Color::White);
    backText.setFillColor(sf::Color(200, 200, 200));
}

void StartState::updatePositions(const sf::Vector2u& windowSize)
{
    auto placeholderBounds = placeholderText.getLocalBounds();
    placeholderText.setOrigin({placeholderBounds.size.x / 2.f, placeholderBounds.size.y / 2.f});
    placeholderText.setPosition({windowSize.x / 2.f, windowSize.y / 2.f});
    
    auto backBounds = backText.getLocalBounds();
    backText.setOrigin({backBounds.size.x / 2.f, backBounds.size.y / 2.f});
    backText.setPosition({windowSize.x / 2.f, windowSize.y / 2.f + 100.f});
}

void StartState::setOnBackClicked(std::function<void()> callback)
{
    onBackClicked = callback;
}

void StartState::handleEvent(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Escape && onBackClicked)
        {
            onBackClicked();
        }
    }
}

void StartState::update(float deltaTime, sf::RenderWindow& window)
{
    // Nothing to update
}

void StartState::draw(sf::RenderWindow& window)
{
    window.draw(placeholderText);
    window.draw(backText);
}