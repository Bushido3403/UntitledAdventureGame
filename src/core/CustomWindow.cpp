// SFML 3.x

#include "CustomWindow.h"

CustomWindow::CustomWindow(const sf::Vector2u& size, const std::string& title, const sf::Font& font) 
    : window(sf::VideoMode(size), title, sf::Style::None),
      dragging(false), 
      shouldClose(false),
      fullscreen(false),
      resized(false),
      windowedSize(size),
      windowedPosition(100, 100),
      titleText(font, title, 16),
      closeText(font, "X", 20),
      fullscreenText(font, "[ ]", 20) {
    
    window.setPosition(windowedPosition);
    window.setFramerateLimit(60);
    
    // Initialize titlebar
    titlebar.setSize(sf::Vector2f(static_cast<float>(size.x), titlebarHeight));
    titlebar.setFillColor(sf::Color(30, 30, 30));
    titlebar.setPosition(sf::Vector2f(0.f, 0.f));
    
    // Configure title text
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(sf::Vector2f(10.f, 10.f));
    
    // Configure close button
    closeText.setFillColor(sf::Color::Red);
    
    // Configure fullscreen button
    fullscreenText.setFillColor(sf::Color::Cyan);
    
    updateTitlebarElements();
}

void CustomWindow::updateTitlebarElements() {
    auto size = window.getSize();
    titlebar.setSize(sf::Vector2f(static_cast<float>(size.x), titlebarHeight));
    closeText.setPosition(sf::Vector2f(static_cast<float>(size.x) - 30.f, 8.f));
    fullscreenText.setPosition(sf::Vector2f(static_cast<float>(size.x) - 60.f, 8.f));
}

void CustomWindow::handleEvent(const sf::Event& event) {
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            auto mousePos = sf::Vector2i(mouseButtonPressed->position.x, 
                                         mouseButtonPressed->position.y);
            
            // Check if close button was clicked
            if (closeText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                shouldClose = true;
                return;
            }
            
            // Check if fullscreen button was clicked
            if (fullscreenText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                fullscreen = !fullscreen;
                
                if (fullscreen) {
                    windowedSize = window.getSize();
                    windowedPosition = window.getPosition();
                    
                    auto desktopMode = sf::VideoMode::getDesktopMode();
                    
                    window.create(desktopMode, titleText.getString(), sf::Style::None);
                    window.setPosition(sf::Vector2i(0, 0));
                    
                    // Update view to match new size
                    sf::FloatRect visibleArea({0.f, 0.f}, 
                        {static_cast<float>(desktopMode.size.x), 
                         static_cast<float>(desktopMode.size.y)});
                    window.setView(sf::View(visibleArea));
                } else {
                    window.create(sf::VideoMode(windowedSize), titleText.getString(), sf::Style::None);
                    window.setPosition(windowedPosition);
                    
                    // Restore windowed view
                    sf::FloatRect visibleArea({0.f, 0.f}, 
                        {static_cast<float>(windowedSize.x), 
                         static_cast<float>(windowedSize.y)});
                    window.setView(sf::View(visibleArea));
                }
                
                window.setFramerateLimit(144);
                
                // Restore icon if it was set
                if (hasIcon) {
                    window.setIcon(icon);
                }
                
                updateTitlebarElements();
                resized = true;
                return;
            }
            
            // Check if titlebar was clicked for dragging
            if (mousePos.y < titlebarHeight && !fullscreen) {
                dragging = true;
                dragOffset = sf::Mouse::getPosition() - window.getPosition();
            }
        }
    }
    else if (const auto* mouseButtonReleased = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mouseButtonReleased->button == sf::Mouse::Button::Left) {
            dragging = false;
        }
    }
    else if (event.is<sf::Event::MouseMoved>()) {
        if (dragging) {
            window.setPosition(sf::Mouse::getPosition() - dragOffset);
        }
    }
    else if (const auto* resized = event.getIf<sf::Event::Resized>()) {
        unsigned int width = resized->size.x;
        unsigned int height = static_cast<unsigned int>(width * 9.0f / 16.0f);
        
        window.setSize(sf::Vector2u(width, height));
        
        sf::FloatRect visibleArea({0.f, 0.f}, 
            {static_cast<float>(width), static_cast<float>(height)});
        window.setView(sf::View(visibleArea));
        
        updateTitlebarElements();
    }
}

void CustomWindow::drawTitlebar() {
    window.draw(titlebar);
    window.draw(titleText);
    window.draw(fullscreenText);
    window.draw(closeText);
}

void CustomWindow::clear() {
    window.clear();
}

void CustomWindow::display() {
    window.display();
}

void CustomWindow::draw(const sf::Drawable& drawable) {
    window.draw(drawable);
}

sf::Vector2u CustomWindow::getSize() const { 
    return window.getSize(); 
}

sf::Vector2u CustomWindow::getDrawableSize() const {
    auto size = window.getSize();
    return sf::Vector2u(size.x, size.y - static_cast<unsigned int>(titlebarHeight));
}

void CustomWindow::setIcon(const sf::Image& iconImage) {
    icon = iconImage;
    hasIcon = true;
    window.setIcon(icon);
}