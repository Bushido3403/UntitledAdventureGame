#include "Button.h"

Button::Button(sf::Texture& texture, const sf::Vector2f& position)
    : sprite(texture), isHovered(false)
{
    sprite.setPosition(position);
}

void Button::setPosition(const sf::Vector2f& position)
{
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
    sprite.setPosition(position);
}

void Button::setScale(const sf::Vector2f& scale)
{
    sprite.setScale(scale);
}

void Button::setOnClick(std::function<void()> callback)
{
    onClick = callback;
}

void Button::handleEvent(const sf::Event& event)
{
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            // mousePressed->position is already in window coordinates
            sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x), 
                                 static_cast<float>(mousePressed->position.y));
            if (sprite.getGlobalBounds().contains(mousePos))
            {
                if (onClick)
                    onClick();
            }
        }
    }
}

void Button::update(const sf::Vector2i& mousePos)
{
    isHovered = sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    sprite.setColor(isHovered ? sf::Color(180, 180, 180) : sf::Color::White);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::FloatRect Button::getBounds() const
{
    return sprite.getGlobalBounds();
}