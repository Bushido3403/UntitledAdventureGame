// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h" // Add this include
#include <functional>
#include <memory>

class Button
{
public:
    static void prime(ResourceManager& resources);
    
    Button(ResourceManager& resources, sf::Texture& texture, const sf::Vector2f& position);
    
    void setPosition(const sf::Vector2f& position);
    void setScale(const sf::Vector2f& scale);
    void setOnClick(std::function<void()> callback);
    
    void handleEvent(const sf::Event& event);
    void update(const sf::Vector2i& mousePos);
    void draw(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    std::function<void()> onClick;
    bool isHovered;
    static std::unique_ptr<sf::Sound> clickSound;
};