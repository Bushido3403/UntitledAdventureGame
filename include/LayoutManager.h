// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>

class LayoutManager {
public:
    struct ScaleFactors {
        float scaleX;
        float scaleY;
        float minScale;
        float scaledBuffer;
        float boxPadding;
    };

    struct LayoutMetrics {
        sf::Vector2f graphicsBoxPos;
        sf::Vector2f graphicsBoxSize;
        sf::Vector2f statsBoxPos;
        sf::Vector2f statsBoxSize;
        sf::Vector2f dialogBoxPos;
        sf::Vector2f dialogBoxSize;
        ScaleFactors scale;
    };

    LayoutManager(const sf::Vector2u& baseSize);
    
    LayoutMetrics calculate(const sf::Vector2u& windowSize, float titlebarHeight) const;
    unsigned int getScaledCharacterSize(unsigned int baseSize, const sf::Vector2u& currentSize) const;
    
private:
    sf::Vector2u baseWindowSize;
    static constexpr float BUFFER = 20.f;
    static constexpr float BOX_PADDING_BASE = 10.f;
};