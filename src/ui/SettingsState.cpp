#include "SettingsState.h"
#include <algorithm> // For std::max and std::min

SettingsState::SettingsState(ResourceManager& resources)
    : resources(resources),
      titleText(resources.getFont("main"), "Settings", 48),
      backText(resources.getFont("main"), "Press ESC to go back", 24),
      volumeLabel(resources.getFont("main"), "Music Volume", 32),
      volumeValue(resources.getFont("main"), "", 32),
      isDragging(false)
{
    titleText.setFillColor(sf::Color::White);
    backText.setFillColor(sf::Color(200, 200, 200));
    volumeLabel.setFillColor(sf::Color::White);
    volumeValue.setFillColor(sf::Color::White);

    sliderBar.setSize({400.f, 10.f});
    sliderBar.setFillColor(sf::Color(100, 100, 100));

    sliderHandle.setSize({20.f, 40.f});
    sliderHandle.setFillColor(sf::Color::White);

    updateVolumeText();
}

void SettingsState::updatePositions(const sf::Vector2u& windowSize)
{
    auto titleBounds = titleText.getLocalBounds();
    titleText.setOrigin({titleBounds.size.x / 2.f, titleBounds.size.y / 2.f});
    titleText.setPosition({windowSize.x / 2.f, windowSize.y / 4.f});

    auto volumeLabelBounds = volumeLabel.getLocalBounds();
    volumeLabel.setOrigin({volumeLabelBounds.size.x / 2.f, volumeLabelBounds.size.y / 2.f});
    volumeLabel.setPosition({windowSize.x / 2.f - 150.f, windowSize.y / 2.f});

    sliderBar.setOrigin({sliderBar.getSize().x / 2.f, sliderBar.getSize().y / 2.f});
    sliderBar.setPosition({windowSize.x / 2.f, windowSize.y / 2.f + 50.f});

    float volume = resources.getMusic("title").getVolume();
    float sliderPercent = volume / 2.0f; // Map volume (0-200) to slider percentage (0-100)
    float handleX = sliderBar.getPosition().x - sliderBar.getSize().x / 2.f + (sliderPercent / 100.f) * sliderBar.getSize().x;
    sliderHandle.setOrigin({sliderHandle.getSize().x / 2.f, sliderHandle.getSize().y / 2.f});
    sliderHandle.setPosition({handleX, sliderBar.getPosition().y});

    auto volumeValueBounds = volumeValue.getLocalBounds();
    volumeValue.setOrigin({volumeValueBounds.size.x / 2.f, volumeValueBounds.size.y / 2.f});
    volumeValue.setPosition({windowSize.x / 2.f + 150.f, windowSize.y / 2.f});

    auto backBounds = backText.getLocalBounds();
    backText.setOrigin({backBounds.size.x / 2.f, backBounds.size.y / 2.f});
    backText.setPosition({windowSize.x / 2.f, windowSize.y * 0.8f});
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
    else if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x), static_cast<float>(mousePressed->position.y));
            if (sliderHandle.getGlobalBounds().contains(mousePos) || sliderBar.getGlobalBounds().contains(mousePos))
            {
                isDragging = true;
            }
        }
    }
    else if (const auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseReleased->button == sf::Mouse::Button::Left)
        {
            isDragging = false;
        }
    }
    else if (event.is<sf::Event::MouseMoved>())
    {
        if (isDragging)
        {
            float mouseX = static_cast<float>(event.getIf<sf::Event::MouseMoved>()->position.x);
            float barStart = sliderBar.getPosition().x - sliderBar.getSize().x / 2.f;
            float barWidth = sliderBar.getSize().x;
            
            float sliderPercent = (mouseX - barStart) / barWidth * 100.f;
            sliderPercent = std::max(0.f, std::min(100.f, sliderPercent)); // Clamp slider 0-100

            float newVolume = sliderPercent * 2.0f; // Map slider (0-100) to volume (0-200)
            resources.getMusic("title").setVolume(newVolume);
            updateVolumeText();

            float handleX = barStart + (sliderPercent / 100.f) * barWidth;
            sliderHandle.setPosition({handleX, sliderHandle.getPosition().y});
        }
    }
}

void SettingsState::update(float deltaTime, sf::RenderWindow& window)
{
    // Nothing to update for now
}

void SettingsState::draw(sf::RenderWindow& window)
{
    window.draw(titleText);
    window.draw(backText);
    window.draw(volumeLabel);
    window.draw(sliderBar);
    window.draw(sliderHandle);
    window.draw(volumeValue);
}

void SettingsState::updateVolumeText()
{
    int volume = static_cast<int>(resources.getMusic("title").getVolume());
    volumeValue.setString(std::to_string(volume / 2) + "%");
}