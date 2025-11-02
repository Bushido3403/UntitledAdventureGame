// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class DialogBox {
public:
    DialogBox(const sf::Font& font);
    
    void setText(const std::string& text, const std::string& speaker);
    void updateLayout(const sf::FloatRect& bounds, float boxPadding, float scaleY, unsigned int dialogSize, unsigned int speakerSize);
    void draw(sf::RenderWindow& window) const;
    
    sf::FloatRect getTextBounds() const;
    const sf::Text& getDialogText() const { return dialogText; }
    sf::Text& getDialogText() { return dialogText; }
    
    static std::string wrapText(const std::string& text, unsigned int maxWidth, 
                                const sf::Font& font, unsigned int characterSize);

private:
    const sf::Font& font;
    sf::Text speakerText;
    sf::Text dialogText;
};