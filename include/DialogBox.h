// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Dialog box for displaying speaker name and dialogue text
class DialogBox {
public:
    DialogBox(const sf::Font& font);
    
    // Set speaker name, text, and optional hex color for speaker
    void setText(const std::string& text, const std::string& speaker, const std::string& speakerColor = "#FFD700");
    
    // Position and size text elements within bounds
    void updateLayout(const sf::FloatRect& bounds, float boxPadding, float scaleY, unsigned int dialogSize, unsigned int speakerSize);
    
    void draw(sf::RenderWindow& window) const;
    
    sf::FloatRect getTextBounds() const;
    const sf::Text& getDialogText() const { return dialogText; }
    sf::Text& getDialogText() { return dialogText; }
    
    // Wrap text to fit within maxWidth
    static std::string wrapText(const std::string& text, unsigned int maxWidth, 
                                const sf::Font& font, unsigned int characterSize);
    
    // Convert hex color string to sf::Color
    static sf::Color parseHexColor(const std::string& hexColor);

private:
    const sf::Font& font;
    sf::Text speakerText;
    sf::Text dialogText;
};