// LAYOUTMANAGER.H

// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>

class LayoutManager {
public:
    // Scale factors for responsive UI sizing
    struct ScaleFactors {
        float scaleX;           // Horizontal scale ratio
        float scaleY;           // Vertical scale ratio
        float minScale;         // Smaller of scaleX/scaleY for uniform scaling
        float scaledBuffer;     // Scaled margin/spacing
        float boxPadding;       // Scaled internal padding
    };

    // Calculated positions and sizes for all UI boxes
    struct LayoutMetrics {
        sf::Vector2f graphicsBoxPos;    // Top-left corner of game view
        sf::Vector2f graphicsBoxSize;   // Dimensions of game view
        sf::Vector2f statsBoxPos;       // Top-left corner of stats panel
        sf::Vector2f statsBoxSize;      // Dimensions of stats panel
        sf::Vector2f dialogBoxPos;      // Top-left corner of dialog area
        sf::Vector2f dialogBoxSize;     // Dimensions of dialog area
        ScaleFactors scale;             // Scaling information
    };

    LayoutManager(const sf::Vector2u& baseSize);
    
    // Calculate all UI element positions for current window size
    LayoutMetrics calculate(const sf::Vector2u& windowSize, float titlebarHeight) const;
    
    // Scale font size based on window dimensions
    unsigned int getScaledCharacterSize(unsigned int baseSize, const sf::Vector2u& currentSize) const;
    
private:
    sf::Vector2u baseWindowSize;        // Reference resolution (1920x1080)
    static constexpr float BUFFER = 20.f;           // Base spacing between elements
    static constexpr float BOX_PADDING_BASE = 10.f; // Base internal padding
};