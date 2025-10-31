// SFML 3.x

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class CustomWindow
{
private:
    sf::RenderWindow window;
    sf::RectangleShape titlebar;
    sf::Text titleText;
    sf::Text closeText;
    sf::Text fullscreenText;
    
    bool dragging;
    sf::Vector2i dragOffset;
    bool shouldClose;
    bool fullscreen;
    sf::Vector2u windowedSize;
    sf::Vector2i windowedPosition;
    
    sf::Image icon;  // Add this
    bool hasIcon = false;  // Add this
    
    static constexpr float titlebarHeight = 40.f;
    
    void updateTitlebarElements();

public:
    CustomWindow(const sf::Vector2u& size, const std::string& title, const sf::Font& font);
    
    void handleEvent(const sf::Event& event);
    void drawTitlebar();
    void clear();
    void display();
    void draw(const sf::Drawable& drawable);
    
    bool isOpen() const { return window.isOpen(); }
    bool getShouldClose() const { return shouldClose; }
    void close() { window.close(); }
    
    sf::Vector2u getSize() const;
    void setView(const sf::View& view) { window.setView(view); }
    
    std::optional<sf::Event> pollEvent() { return window.pollEvent(); }
    
    sf::RenderWindow& getWindow() { return window; }
    
    void setIcon(const sf::Image& iconImage);  // Add this method
};