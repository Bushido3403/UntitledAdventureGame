// SFML 3.x

#include "DialogBox.h"
#include <sstream>

DialogBox::DialogBox(const sf::Font& font)
    : font(font),
      speakerText(font, "", 28),
      dialogText(font, "", 24)
{
    speakerText.setFillColor(sf::Color(200, 200, 100));
    dialogText.setFillColor(sf::Color::White);
}

void DialogBox::setText(const std::string& text, const std::string& speaker, const std::string& speakerColor) {
    speakerText.setString("[" + speaker + "]");
    speakerText.setFillColor(parseHexColor(speakerColor));
    dialogText.setString(text);
}

sf::Color DialogBox::parseHexColor(const std::string& hexColor) {
    std::string hex = hexColor;
    
    // Remove '#' if present
    if (hex[0] == '#') {
        hex = hex.substr(1);
    }
    
    // Default to gold if parsing fails
    if (hex.length() != 6) {
        return sf::Color(200, 200, 100);
    }
    
    try {
        unsigned int r = std::stoi(hex.substr(0, 2), nullptr, 16);
        unsigned int g = std::stoi(hex.substr(2, 2), nullptr, 16);
        unsigned int b = std::stoi(hex.substr(4, 2), nullptr, 16);
        return sf::Color(r, g, b);
    } catch (...) {
        return sf::Color(200, 200, 100);  // Default gold color
    }
}

void DialogBox::updateLayout(const sf::FloatRect& bounds, float boxPadding, float scaleY, 
                             unsigned int dialogSize, unsigned int speakerSize) {
    speakerText.setCharacterSize(speakerSize);
    dialogText.setCharacterSize(dialogSize);
    
    speakerText.setPosition(sf::Vector2f(bounds.position.x + boxPadding, 
                                         bounds.position.y + boxPadding));
    
    float speakerHeight = speakerText.getGlobalBounds().size.y;
    float speakerToTextGap = 10.f * scaleY;
    
    dialogText.setPosition(sf::Vector2f(bounds.position.x + boxPadding, 
                                       bounds.position.y + boxPadding + speakerHeight + speakerToTextGap));
}

void DialogBox::draw(sf::RenderWindow& window) const {
    window.draw(speakerText);
    window.draw(dialogText);
}

sf::FloatRect DialogBox::getTextBounds() const {
    return dialogText.getGlobalBounds();
}

std::string DialogBox::wrapText(const std::string& text, unsigned int maxWidth, 
                                const sf::Font& font, unsigned int characterSize) {
    std::istringstream words(text);
    std::ostringstream wrapped;
    std::string word;
    std::string line;
    
    sf::Text testText(font, "", characterSize);
    
    while (words >> word) {
        std::string testLine = line.empty() ? word : line + " " + word;
        testText.setString(testLine);
        
        if (testText.getLocalBounds().size.x > maxWidth) {
            if (!line.empty()) {
                wrapped << line << "\n";
                line = word;
            } else {
                wrapped << word << "\n";
                line = "";
            }
        } else {
            line = testLine;
        }
    }
    
    if (!line.empty()) {
        wrapped << line;
    }
    
    return wrapped.str();
}