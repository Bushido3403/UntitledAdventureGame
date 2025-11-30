#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

class ConfirmationDialog {
public:
    ConfirmationDialog(const sf::Font& font);
    
    void show(const std::string& message, 
              const sf::Vector2u& windowSize, 
              float titlebarHeight);
    void hide();
    bool isVisible() const { return visible; }
    
    void updatePosition(const sf::Vector2u& windowSize, float titlebarHeight);
    void draw(sf::RenderWindow& window);
    
private:
    std::string wrapText(const std::string& text, float maxWidth, const sf::Font& font, unsigned int characterSize);
    
    sf::RectangleShape background;
    sf::RectangleShape dialogBox;
    sf::Text messageText;
    sf::Text instructionText;
    
    bool visible = false;
};