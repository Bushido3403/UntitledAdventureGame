#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

// Modal dialog for yes/no confirmations
class ConfirmationDialog {
public:
    ConfirmationDialog(const sf::Font& font);
    
    // Display the dialog with a message
    void show(const std::string& message, 
              const sf::Vector2u& windowSize, 
              float titlebarHeight);
    void hide();
    bool isVisible() const { return visible; }
    
    // Update positions when window is resized
    void updatePosition(const sf::Vector2u& windowSize, float titlebarHeight);
    void draw(sf::RenderWindow& window);
    
private:
    // Wrap text to fit within a maximum width
    std::string wrapText(const std::string& text, float maxWidth, const sf::Font& font, unsigned int characterSize);
    
    sf::RectangleShape background;    // Semi-transparent overlay
    sf::RectangleShape dialogBox;     // Dialog container
    sf::Text messageText;             // Main message
    sf::Text instructionText;         // Y/N instructions
    
    bool visible = false;
};