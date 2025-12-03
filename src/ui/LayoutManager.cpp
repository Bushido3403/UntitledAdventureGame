// LAYOUTMANAGER.CPP

// SFML 3.x

#include "LayoutManager.h"
#include "CustomWindow.h"
#include <algorithm>

LayoutManager::LayoutManager(const sf::Vector2u& baseSize)
    : baseWindowSize(baseSize) {}

// Calculate responsive layout for all UI boxes based on current window size
LayoutManager::LayoutMetrics LayoutManager::calculate(const sf::Vector2u& windowSize, float titlebarHeight) const {
    LayoutMetrics metrics;
    
    // Calculate scale factors based on window size vs base size
    metrics.scale.scaleX = static_cast<float>(windowSize.x) / static_cast<float>(baseWindowSize.x);
    metrics.scale.scaleY = static_cast<float>(windowSize.y) / static_cast<float>(baseWindowSize.y);
    metrics.scale.minScale = std::min(metrics.scale.scaleX, metrics.scale.scaleY);
    metrics.scale.scaledBuffer = BUFFER * metrics.scale.minScale;
    metrics.scale.boxPadding = BOX_PADDING_BASE * metrics.scale.minScale;
    
    float availableHeight = static_cast<float>(windowSize.y) - titlebarHeight - (metrics.scale.scaledBuffer * 2);
    
    // Calculate graphics box dimensions (maintain 16:9 aspect ratio)
    float graphicsWidth = (static_cast<float>(windowSize.x) - (metrics.scale.scaledBuffer * 3)) * 0.6f;
    float graphicsHeight = graphicsWidth * (9.f / 16.f);
    
    // Reserve space for dialog box (ensure it has minimum height)
    float baseMinDialogHeight = 200.f;
    float minDialogHeight = baseMinDialogHeight * metrics.scale.scaleY;
    float maxGraphicsHeight = availableHeight - minDialogHeight - metrics.scale.scaledBuffer;
    
    // Limit graphics height if needed to make room for dialog
    if (graphicsHeight > maxGraphicsHeight) {
        graphicsHeight = maxGraphicsHeight;
        graphicsWidth = graphicsHeight * (16.f / 9.f);
    }
    
    float graphicsY = titlebarHeight + metrics.scale.scaledBuffer;
    
    // Graphics box (left side, 60% of width)
    metrics.graphicsBoxPos = sf::Vector2f(metrics.scale.scaledBuffer, graphicsY);
    metrics.graphicsBoxSize = sf::Vector2f(graphicsWidth, graphicsHeight);
    
    // Stats box (right side, 40% of width, same height as graphics)
    float statsWidth = static_cast<float>(windowSize.x) - graphicsWidth - (metrics.scale.scaledBuffer * 3);
    metrics.statsBoxPos = sf::Vector2f(graphicsWidth + (metrics.scale.scaledBuffer * 2), graphicsY);
    metrics.statsBoxSize = sf::Vector2f(statsWidth, graphicsHeight);
    
    // Dialog box (bottom, spans full width)
    float dialogBoxY = graphicsHeight + graphicsY + metrics.scale.scaledBuffer;
    float boxHeight = static_cast<float>(windowSize.y) - dialogBoxY - metrics.scale.scaledBuffer - titlebarHeight;
    float boxWidth = static_cast<float>(windowSize.x) - (metrics.scale.scaledBuffer * 2);
    
    metrics.dialogBoxPos = sf::Vector2f(metrics.scale.scaledBuffer, dialogBoxY);
    metrics.dialogBoxSize = sf::Vector2f(boxWidth, boxHeight);
    
    return metrics;
}

// Scale font size proportionally to window size, clamped between 0.5x and 2.0x
unsigned int LayoutManager::getScaledCharacterSize(unsigned int baseSize, const sf::Vector2u& currentSize) const {
    float scaleX = static_cast<float>(currentSize.x) / static_cast<float>(baseWindowSize.x);
    float scaleY = static_cast<float>(currentSize.y) / static_cast<float>(baseWindowSize.y);
    float scale = std::min(scaleX, scaleY);
    scale = std::max(0.5f, std::min(2.0f, scale)); // Clamp scale factor
    return static_cast<unsigned int>(baseSize * scale);
}