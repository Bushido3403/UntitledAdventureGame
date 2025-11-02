// SFML 3.x

#include "Button.h"

std::unique_ptr<sf::Sound> Button::clickSound;

Button::Button(ResourceManager& resources, sf::Texture* texture, const sf::Vector2f& position)
    : isHovered(false),
      hasTexture(texture != nullptr)
{
    if (texture) {
        sprite.emplace(*texture);
        sprite->setPosition(position);
    }
    
    if (!Button::clickSound) {
        Button::clickSound = std::make_unique<sf::Sound>(resources.getSoundBuffer("click"));
    }
}

void Button::setPosition(const sf::Vector2f& position)
{
    if (hasTexture && sprite) {
        auto bounds = sprite->getLocalBounds();
        sprite->setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
        sprite->setPosition(position);
    } else if (buttonText) {
        buttonText->setPosition(position);
    }
}

void Button::setScale(const sf::Vector2f& scale)
{
    if (hasTexture && sprite) {
        sprite->setScale(scale);
    } else if (buttonText) {
        buttonText->setScale(scale);
    }
}

void Button::setText(const std::string& text, const sf::Font& font, unsigned int characterSize)
{
    buttonText.emplace(font, text, characterSize);
    buttonText->setFillColor(sf::Color(180, 180, 200));
}

void Button::setOnClick(std::function<void()> callback)
{
    onClick = callback;
}

void Button::handleEvent(const sf::Event& event)
{
    // if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    // {
    //     if (mousePressed->button == sf::Mouse::Button::Left)
    //     {
    //         sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x), 
    //                               static_cast<float>(mousePressed->position.y));
    //         if (getBounds().contains(mousePos))
    //         {
    //             if (Button::clickSound) Button::clickSound->play();
    //             if (onClick)
    //                 onClick();
    //         }
    //     }
    // }
    if (const auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseReleased->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos(static_cast<float>(mouseReleased->position.x), 
                                  static_cast<float>(mouseReleased->position.y));
            if (getBounds().contains(mousePos))
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
    isHovered = getBounds().contains(static_cast<sf::Vector2f>(mousePos));
    
    if (hasTexture && sprite) {
        sprite->setColor(isHovered ? sf::Color(180, 180, 180) : sf::Color::White);
    } else if (buttonText) {
        buttonText->setFillColor(isHovered ? sf::Color(255, 255, 150) : sf::Color(180, 180, 200));
    }
}

void Button::draw(sf::RenderWindow& window)
{
    if (hasTexture && sprite) {
        window.draw(*sprite);
    } else if (buttonText) {
        window.draw(*buttonText);
    }
}

sf::FloatRect Button::getBounds() const
{
    if (hasTexture && sprite) {
        return sprite->getGlobalBounds();
    } else if (buttonText) {
        return buttonText->getGlobalBounds();
    }
    return sf::FloatRect();
}

void Button::prime(ResourceManager& resources)
{
    if (!Button::clickSound) {
        Button::clickSound = std::make_unique<sf::Sound>(resources.getSoundBuffer("click"));
        float old = Button::clickSound->getVolume();
        Button::clickSound->setVolume(0.f);
        Button::clickSound->play();
        Button::clickSound->stop();
        Button::clickSound->setVolume(old);
    }
}