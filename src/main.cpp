// C++
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <optional>
#include <algorithm>

enum class GameState
{
    MainMenu,
    Start,
    Settings
};

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1280u, 720u}),
        "Untitled Adventure Game",
        sf::Style::None
    );
    window.setPosition(sf::Vector2i(100, 100));
    window.setFramerateLimit(144);

    GameState currentState = GameState::MainMenu;

    // Load and set window icon
    sf::Image icon;
    if (!icon.loadFromFile("assets/images/logo.png"))
        return 1;
    window.setIcon(icon);

    // Load background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/menuBackground.jpg"))
        return 1;
    backgroundTexture.setSmooth(true);
    sf::Sprite backgroundSprite(backgroundTexture);

    // Load logo
    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("assets/images/logo.png"))
        return 1;
    sf::Sprite logoSprite(logoTexture);
    logoSprite.setScale({0.8f, 0.8f});

    // Load title
    sf::Texture titleTexture;
    if (!titleTexture.loadFromFile("assets/images/title.png"))
        return 1;
    sf::Sprite titleSprite(titleTexture);
    titleSprite.setScale({0.8f, 0.8f});

    // Load start button
    sf::Texture startTexture;
    if (!startTexture.loadFromFile("assets/images/start.png"))
        return 1;
    sf::Sprite startSprite(startTexture);
    startSprite.setScale({0.8f, 0.8f});

    // Load settings button
    sf::Texture settingsTexture;
    if (!settingsTexture.loadFromFile("assets/images/settings.png"))
        return 1;
    sf::Sprite settingsSprite(settingsTexture);
    settingsSprite.setScale({0.8f, 0.8f});

    // Helper to update UI positions
    auto updateUIPositions = [&] {
        const auto ws = window.getSize();
        const auto ts = backgroundTexture.getSize();
        backgroundSprite.setScale(
            sf::Vector2f{
                static_cast<float>(ws.x) / static_cast<float>(ts.x),
                static_cast<float>(ws.y) / static_cast<float>(ts.y)
            }
        );

        logoSprite.setPosition(sf::Vector2f(20.f, 50.f));

        auto titleBounds = titleSprite.getLocalBounds();
        titleSprite.setOrigin({titleBounds.size.x / 2.f, titleBounds.size.y / 2.f});
        titleSprite.setPosition({ws.x / 2.f, ws.y / 3.f});

        auto startBounds = startSprite.getLocalBounds();
        startSprite.setOrigin({startBounds.size.x / 2.f, startBounds.size.y / 2.f});
        startSprite.setPosition({ws.x / 2.f, ws.y / 3.f + 125.f});

        auto settingsBounds = settingsSprite.getLocalBounds();
        settingsSprite.setOrigin({settingsBounds.size.x / 2.f, settingsBounds.size.y / 2.f});
        settingsSprite.setPosition({ws.x / 2.f, ws.y / 3.f + 250.f});
    };

    updateUIPositions();

    // Custom titlebar
    const float titlebarHeight = 40.f;
    sf::RectangleShape titlebar({static_cast<float>(window.getSize().x), titlebarHeight});
    titlebar.setFillColor(sf::Color(30, 30, 30));

    sf::Font font;
    if (!font.openFromFile("assets/fonts/MedievalSharp.ttf"))
        return 1;

    // Load and play background music
    sf::Music music;
    if (!music.openFromFile("assets/sfx/Title.mp3"))
        return 1;
    music.setLooping(true);
    music.play();

    sf::Text titleText(font);
    titleText.setString("Untitled Adventure Game");
    titleText.setCharacterSize(16);
    titleText.setPosition(sf::Vector2f(10.f, 10.f));
    titleText.setFillColor(sf::Color::White);

    sf::Text closeText(font);
    closeText.setString("X");
    closeText.setCharacterSize(20);
    closeText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - 30.f, 8.f));
    closeText.setFillColor(sf::Color::Red);

    sf::Text fullscreenText(font);
    fullscreenText.setString("[ ]");
    fullscreenText.setCharacterSize(20);
    fullscreenText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - 60.f, 8.f));
    fullscreenText.setFillColor(sf::Color::Cyan);

    // Placeholder texts for other screens
    sf::Text startScreenText(font);
    startScreenText.setString("START");
    startScreenText.setCharacterSize(80);
    startScreenText.setFillColor(sf::Color::White);

    sf::Text settingsScreenText(font);
    settingsScreenText.setString("SETTINGS");
    settingsScreenText.setCharacterSize(80);
    settingsScreenText.setFillColor(sf::Color::White);

    bool isFullscreen = false;
    sf::Vector2u windowedSize(1280u, 720u);
    sf::Vector2i windowedPosition(100, 100);

    bool isDragging = false;
    sf::Vector2i dragOffset;

    bool adjustingSize = false;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                unsigned int width = resized->size.x;
                unsigned int height = static_cast<unsigned int>(width * 9.0f / 16.0f);
                
                window.setSize(sf::Vector2u(width, height));
                
                sf::FloatRect visibleArea({0.f, 0.f}, {static_cast<float>(width), static_cast<float>(height)});
                window.setView(sf::View(visibleArea));
                
                updateUIPositions();
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                auto mousePos = sf::Mouse::getPosition(window);
                
                if (closeText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    window.close();
                }
                else if (fullscreenText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    isFullscreen = !isFullscreen;
                    
                    if (isFullscreen)
                    {
                        windowedSize = window.getSize();
                        windowedPosition = window.getPosition();
                        
                        window.create(sf::VideoMode::getDesktopMode(), "Untitled Adventure Game", sf::Style::None);
                        window.setPosition(sf::Vector2i(0, 0));
                    }
                    else
                    {
                        window.create(sf::VideoMode(windowedSize), "Untitled Adventure Game", sf::Style::None);
                        window.setPosition(windowedPosition);
                    }
                    
                    window.setFramerateLimit(144);
                    updateUIPositions();
                    
                    titlebar.setSize({static_cast<float>(window.getSize().x), titlebarHeight});
                    closeText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - 30.f, 8.f));
                    fullscreenText.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) - 60.f, 8.f));
                }
                else if (mousePos.y < titlebarHeight && !isFullscreen)
                {
                    isDragging = true;
                    dragOffset = sf::Mouse::getPosition() - window.getPosition();
                }
                else if (currentState == GameState::MainMenu)
                {
                    // Check start button click
                    if (startSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        currentState = GameState::Start;
                    }
                    // Check settings button click
                    else if (settingsSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        currentState = GameState::Settings;
                    }
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
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                // Escape key returns to main menu
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    currentState = GameState::MainMenu;
                }
            }
        }

        // Handle hover effects on main menu
        if (currentState == GameState::MainMenu)
        {
            auto mousePos = sf::Mouse::getPosition(window);
            
            // Start button hover
            if (startSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                startSprite.setColor(sf::Color(180, 180, 180));
            }
            else
            {
                startSprite.setColor(sf::Color::White);
            }
            
            // Settings button hover
            if (settingsSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                settingsSprite.setColor(sf::Color(180, 180, 180));
            }
            else
            {
                settingsSprite.setColor(sf::Color::White);
            }
        }

        updateUIPositions();

        window.clear();
        window.draw(backgroundSprite);
        
        // Draw based on current state
        if (currentState == GameState::MainMenu)
        {
            window.draw(logoSprite);
            window.draw(titleSprite);
            window.draw(startSprite);
            window.draw(settingsSprite);
        }
        else if (currentState == GameState::Start)
        {
            auto ws = window.getSize();
            auto textBounds = startScreenText.getLocalBounds();
            startScreenText.setOrigin({textBounds.size.x / 2.f, textBounds.size.y / 2.f});
            startScreenText.setPosition({ws.x / 2.f, ws.y / 2.f});
            window.draw(startScreenText);
        }
        else if (currentState == GameState::Settings)
        {
            auto ws = window.getSize();
            auto textBounds = settingsScreenText.getLocalBounds();
            settingsScreenText.setOrigin({textBounds.size.x / 2.f, textBounds.size.y / 2.f});
            settingsScreenText.setPosition({ws.x / 2.f, ws.y / 2.f});
            window.draw(settingsScreenText);
        }
        
        window.draw(titlebar);
        window.draw(titleText);
        window.draw(fullscreenText);
        window.draw(closeText);
        window.display();
    }

    return 0;
}
