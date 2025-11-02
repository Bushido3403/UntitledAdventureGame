// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class DialogBox {
public:
    DialogBox(const sf::Font& font);
    
    void setText(const std::string& text, const std::string& speaker, const std::string& speakerColor = "#FFD700");
    void updateLayout(const sf::FloatRect& bounds, float boxPadding, float scaleY, unsigned int dialogSize, unsigned int speakerSize);
    void draw(sf::RenderWindow& window) const;
    
    sf::FloatRect getTextBounds() const;
    const sf::Text& getDialogText() const { return dialogText; }
    sf::Text& getDialogText() { return dialogText; }
    
    static std::string wrapText(const std::string& text, unsigned int maxWidth, 
                                const sf::Font& font, unsigned int characterSize);
    static sf::Color parseHexColor(const std::string& hexColor);  // Add this helper

private:
    const sf::Font& font;
    sf::Text speakerText;
    sf::Text dialogText;
};