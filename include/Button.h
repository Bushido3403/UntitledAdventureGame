// SFML 3.x

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <functional>
#include <memory>
#include <optional>
#include "ResourceManager.h"

class Button {
public:
    Button(ResourceManager& resources, sf::Texture* texture, const sf::Vector2f& position);
    
    void setPosition(const sf::Vector2f& position);
    void setScale(const sf::Vector2f& scale);
    void setOnClick(std::function<void()> callback);
    void handleEvent(const sf::Event& event);
    void update(const sf::Vector2i& mousePos);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    
    void setText(const std::string& text, const sf::Font& font, unsigned int characterSize = 24);
    
    static void prime(ResourceManager& resources);
    static std::unique_ptr<sf::Sound> clickSound;

private:
    std::optional<sf::Sprite> sprite;
    std::optional<sf::Text> buttonText;
    bool isHovered;
    bool hasTexture;
    std::function<void()> onClick;
};

#endif