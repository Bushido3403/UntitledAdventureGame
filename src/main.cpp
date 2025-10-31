// C++
#include <SFML/Graphics.hpp>
#include <cmath>
#include <optional>
#include <algorithm>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1920u, 1080u}),
        "Untitled Adventure Game",
        sf::Style::None  // Remove default titlebar
    );
    window.setFramerateLimit(144);

    // Load background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/menuBackground.jpg"))
        return 1;
    backgroundTexture.setSmooth(true);

    sf::Sprite backgroundSprite(backgroundTexture);

    // Helper to scale sprite to window
    auto updateBackgroundScale = [&] {
        const auto ws = window.getSize();
        const auto ts = backgroundTexture.getSize();
        backgroundSprite.setScale(
            sf::Vector2f{
                static_cast<float>(ws.x) / static_cast<float>(ts.x),
                static_cast<float>(ws.y) / static_cast<float>(ts.y)
            }
        );
    };

    updateBackgroundScale();

    // Custom titlebar
    const float titlebarHeight = 40.f;
    sf::RectangleShape titlebar({static_cast<float>(window.getSize().x), titlebarHeight});
    titlebar.setFillColor(sf::Color(30, 30, 30));

    sf::Font font;
    if (!font.openFromFile("assets/fonts/MedievalSharp.ttf"))
        return 1;

    sf::Text titleText(font);
    titleText.setString("Untitled Adventure Game");
    titleText.setCharacterSize(16);
    titleText.setPosition(sf::Vector2f(10.f, 10.f));
    titleText.setFillColor(sf::Color::White);

    // Close button
    sf::RectangleShape closeButton({40.f, titlebarHeight});
    closeButton.setFillColor(sf::Color(200, 50, 50));
    closeButton.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - 40.f, 0.f));

    sf::Text closeText(font);
    closeText.setString("X");
    closeText.setCharacterSize(20);
    closeText.setPosition(sf::Vector2f(closeButton.getPosition().x + 12.f, 8.f));
    closeText.setFillColor(sf::Color::White);

    // Dragging state
    bool isDragging = false;
    sf::Vector2i dragOffset;

    bool adjustingSize = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // Window closed
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            // Window resized
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // Lock to 16:9 aspect ratio
                unsigned int width = resized->size.x;
                unsigned int height = static_cast<unsigned int>(width * 9.0f / 16.0f);
                
                // Apply the corrected size
                window.setSize(sf::Vector2u(width, height));
                
                // Update the view to match the new size
                sf::FloatRect visibleArea({0.f, 0.f}, {static_cast<float>(width), static_cast<float>(height)});
                window.setView(sf::View(visibleArea));
                
                // Update background scaling
                updateBackgroundScale();
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                auto mousePos = sf::Mouse::getPosition(window);
                
                // Check close button
                if (closeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    window.close();
                }
                // Check titlebar for dragging
                else if (mousePos.y < titlebarHeight)
                {
                    isDragging = true;
                    dragOffset = sf::Mouse::getPosition() - window.getPosition();
                }
            }
            else if (event->is<sf::Event::MouseButtonReleased>())
            {
                isDragging = false;
            }
            else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                if (isDragging)
                {
                    window.setPosition(sf::Mouse::getPosition() - dragOffset);
                }
            }
        }

        // Safety: always match current window size
        updateBackgroundScale();

        window.clear();
        window.draw(backgroundSprite);
        window.draw(titlebar);        // Draw titlebar
        window.draw(titleText);        // Draw title
        window.draw(closeButton);      // Draw close button
        window.draw(closeText);        // Draw X text
        window.display();
    }

    return 0;
}
