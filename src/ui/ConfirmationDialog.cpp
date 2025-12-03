// SFML 3.x
#include "ConfirmationDialog.h"

ConfirmationDialog::ConfirmationDialog(const sf::Font& font)
    : messageText(font, "", 20),
      instructionText(font, "Press ", 20)
{
    // Semi-transparent black background overlay
    background.setFillColor(sf::Color(0, 0, 0, 180));
    
    // Dialog box styling (matching DialogBox style)
    dialogBox.setFillColor(sf::Color(40, 40, 50, 240));
    dialogBox.setOutlineColor(sf::Color(100, 100, 120));
    dialogBox.setOutlineThickness(2.f);
    
    messageText.setFillColor(sf::Color::White);
    instructionText.setFillColor(sf::Color(200, 200, 200));
    
    visible = false;
}

void ConfirmationDialog::show(const std::string& message, 
                              const sf::Vector2u& windowSize, 
                              float titlebarHeight) {
    messageText.setString(message);
    visible = true;
    updatePosition(windowSize, titlebarHeight);
}

void ConfirmationDialog::hide() {
    visible = false;
}

std::string ConfirmationDialog::wrapText(const std::string& text, float maxWidth, const sf::Font& font, unsigned int characterSize) {
    std::string wrappedText;
    std::string currentLine;
    std::istringstream words(text);
    std::string word;
    
    sf::Text testText(font, "", characterSize);
    
    // Build lines word by word, wrapping when width exceeded
    while (words >> word) {
        std::string testLine = currentLine.empty() ? word : currentLine + " " + word;
        testText.setString(testLine);
        
        if (testText.getLocalBounds().size.x > maxWidth) {
            if (!currentLine.empty()) {
                wrappedText += currentLine + "\n";
                currentLine = word;
            } else {
                // Single word is too long, add it anyway
                wrappedText += word + "\n";
                currentLine = "";
            }
        } else {
            currentLine = testLine;
        }
    }
    
    if (!currentLine.empty()) {
        wrappedText += currentLine;
    }
    
    return wrappedText;
}

void ConfirmationDialog::updatePosition(const sf::Vector2u& windowSize, float titlebarHeight) {
    // Cover the entire window (below titlebar)
    background.setSize(sf::Vector2f(static_cast<float>(windowSize.x), 
                                     static_cast<float>(windowSize.y) - titlebarHeight));
    background.setPosition(sf::Vector2f(0.f, titlebarHeight));
    
    // Center the dialog box
    float dialogWidth = 500.f;
    float dialogHeight = 200.f;
    float dialogX = (static_cast<float>(windowSize.x) - dialogWidth) / 2.f;
    float dialogY = (static_cast<float>(windowSize.y) - titlebarHeight - dialogHeight) / 2.f + titlebarHeight;
    
    dialogBox.setSize(sf::Vector2f(dialogWidth, dialogHeight));
    dialogBox.setPosition(sf::Vector2f(dialogX, dialogY));
    
    // Wrap and position message text
    float textPadding = 40.f;
    float maxTextWidth = dialogWidth - (textPadding * 2);
    const sf::Font& msgFont = messageText.getFont();
    std::string wrappedMessage = wrapText(messageText.getString(), maxTextWidth, 
                                          msgFont, messageText.getCharacterSize());
    messageText.setString(wrappedMessage);
    
    // Center the message text
    sf::FloatRect messageBounds = messageText.getLocalBounds();
    float dialogCenterX = dialogX + dialogWidth / 2.f;
    messageText.setPosition(sf::Vector2f(
        dialogCenterX - messageBounds.size.x / 2.f - messageBounds.position.x,
        dialogY + 40.f - messageBounds.position.y
    ));
    
    // Center instruction text at bottom
    instructionText.setString("Press Y to confirm or N to cancel");
    sf::FloatRect instructionBounds = instructionText.getLocalBounds();
    instructionText.setPosition(sf::Vector2f(
        dialogX + (dialogWidth - instructionBounds.size.x) / 2.f - instructionBounds.position.x,
        dialogY + dialogHeight - 60.f - instructionBounds.position.y
    ));
}

void ConfirmationDialog::draw(sf::RenderWindow& window) {
    if (!visible) return;
    
    window.draw(background);
    window.draw(dialogBox);
    window.draw(messageText);
    
    // Draw instruction text with colored Y (green) and N (red)
    const std::string fullText = "Press Y to confirm or N to cancel";
    const sf::Font& font = instructionText.getFont();
    unsigned int charSize = instructionText.getCharacterSize();
    sf::Vector2f basePos = instructionText.getPosition();
    
    float xOffset = 0.f;
    
    for (size_t i = 0; i < fullText.length(); ++i) {
        sf::Text charText(font, std::string(1, fullText[i]), charSize);
        
        // Color Y green and N red
        if (fullText[i] == 'Y') {
            charText.setFillColor(sf::Color::Green);
        } else if (fullText[i] == 'N') {
            charText.setFillColor(sf::Color::Red);
        } else {
            charText.setFillColor(sf::Color(200, 200, 200));
        }
        
        charText.setPosition(sf::Vector2f(basePos.x + xOffset, basePos.y));
        window.draw(charText);
        
        xOffset += charText.getLocalBounds().size.x;
    }
}