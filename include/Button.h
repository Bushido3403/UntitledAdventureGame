#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
public:
    Button(sf::Texture& texture, const sf::Vector2f& position);
    
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
};