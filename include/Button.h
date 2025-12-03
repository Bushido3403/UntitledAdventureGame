// SFML 3.x

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include <memory>
#include <optional>
#include "ResourceManager.h"

// Interactive button with optional texture/text and click sound
class Button {
public:
    // Create button with optional texture at position
    Button(ResourceManager& resources, sf::Texture* texture, const sf::Vector2f& position);
    
    void handleEvent(const sf::Event& event);
    void update(const sf::Vector2i& mousePos);
    void draw(sf::RenderWindow& window);
    
    void setPosition(const sf::Vector2f& position);
    void setScale(const sf::Vector2f& scale);
    void setText(const std::string& text, const sf::Font& font, unsigned int characterSize);
    void setTextSize(unsigned int characterSize);
    void setOnClick(std::function<void()> callback);
    
    sf::FloatRect getBounds() const;
    
    // Pre-load click sound (prevents delay on first click)
    static void prime(ResourceManager& resources);

private:
    std::optional<sf::Sprite> sprite;
    std::optional<sf::Text> buttonText;
    bool isHovered;
    bool hasTexture;
    std::function<void()> onClick;
    
    // Shared click sound for all buttons
    static std::unique_ptr<sf::Sound> clickSound;
};

#endif