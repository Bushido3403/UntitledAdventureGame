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
    
    // Initialize shared click sound once
    if (!Button::clickSound) {
        Button::clickSound = std::make_unique<sf::Sound>(resources.getSoundBuffer("click"));
    }
}

void Button::setPosition(const sf::Vector2f& position)
{
    if (hasTexture && sprite) {
        // Center sprite on position
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
    if (!buttonText) {
        buttonText.emplace(font);
    }
    buttonText->setFont(font);
    buttonText->setString(text);
    buttonText->setCharacterSize(characterSize);
    
    // Center text on button sprite if texture is used
    if (hasTexture && sprite) {
        sf::FloatRect textBounds = buttonText->getLocalBounds();
        sf::FloatRect spriteBounds = sprite->getGlobalBounds();
        buttonText->setPosition(sf::Vector2f(
            spriteBounds.position.x + (spriteBounds.size.x - textBounds.size.x) / 2.f,
            spriteBounds.position.y + (spriteBounds.size.y - textBounds.size.y) / 2.f
        ));
    }
}

void Button::setTextSize(unsigned int characterSize)
{
    if (!buttonText) return;
    buttonText->setCharacterSize(characterSize);
    
    // Re-center text after size change
    if (hasTexture && sprite) {
        sf::FloatRect textBounds = buttonText->getLocalBounds();
        sf::FloatRect spriteBounds = sprite->getGlobalBounds();
        buttonText->setPosition(sf::Vector2f(
            spriteBounds.position.x + (spriteBounds.size.x - textBounds.size.x) / 2.f,
            spriteBounds.position.y + (spriteBounds.size.y - textBounds.size.y) / 2.f
        ));
    }
}

void Button::setOnClick(std::function<void()> callback)
{
    onClick = callback;
}

void Button::handleEvent(const sf::Event& event)
{
    if (const auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseReleased->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos(static_cast<float>(mouseReleased->position.x), 
                                  static_cast<float>(mouseReleased->position.y));
            // Check if click is within button bounds
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
    // Update hover state
    isHovered = getBounds().contains(static_cast<sf::Vector2f>(mousePos));
    
    // Change appearance when hovered
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
    }
    if (buttonText) {
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
    // Pre-load and "warm up" click sound to prevent first-click delay
    if (!Button::clickSound) {
        Button::clickSound = std::make_unique<sf::Sound>(resources.getSoundBuffer("click"));
        float old = Button::clickSound->getVolume();
        Button::clickSound->setVolume(0.f);
        Button::clickSound->play();
        Button::clickSound->stop();
        Button::clickSound->setVolume(old);
    }
}