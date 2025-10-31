// SFML 3.x

#include "Button.h"

std::unique_ptr<sf::Sound> Button::clickSound;

Button::Button(ResourceManager& resources, sf::Texture& texture, const sf::Vector2f& position)
    : sprite(texture), 
      isHovered(false)
{
    sprite.setPosition(position);
    if (!Button::clickSound) {
        Button::clickSound = std::make_unique<sf::Sound>(resources.getSoundBuffer("click"));
    }
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
            sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x), 
                                  static_cast<float>(mousePressed->position.y));
            if (sprite.getGlobalBounds().contains(mousePos))
            {
                if (Button::clickSound) Button::clickSound->play();
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

void Button::prime(ResourceManager& resources)
{
    if (!Button::clickSound) {
        Button::clickSound = std::make_unique<sf::Sound>(resources.getSoundBuffer("click"));
        float old = Button::clickSound->getVolume();
        Button::clickSound->setVolume(0.f);   // warm up silently
        Button::clickSound->play();
        Button::clickSound->stop();
        Button::clickSound->setVolume(old);
    }
}