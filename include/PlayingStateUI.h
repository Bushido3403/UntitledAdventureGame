#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "ResourceManager.h"
#include "DialogBox.h"
#include "Button.h"
#include "LayoutManager.h"

class SceneManager;
struct Scene;

class PlayingStateUI {
public:
    PlayingStateUI(ResourceManager& resources);
    
    void updatePositions(const sf::Vector2u& newWindowSize, const Scene* currentScene);
    void updateChoiceButtons(const std::vector<std::unique_ptr<Button>>& buttons, const Scene* currentScene);
    void draw(sf::RenderWindow& window, const std::vector<std::unique_ptr<Button>>& buttons, 
              sf::Sprite* graphicsSprite);
    
    DialogBox& getDialogBox() { return *dialogBox; }
    const sf::Vector2u& getWindowSize() const { return windowSize; }
    
private:
    void updateChoicePositions(const std::vector<std::unique_ptr<Button>>& buttons, const Scene* currentScene);
    
    ResourceManager& resources;
    std::unique_ptr<DialogBox> dialogBox;
    std::unique_ptr<LayoutManager> layoutManager;
    
    sf::RectangleShape background;
    sf::RectangleShape dialogBoxShape;
    sf::RectangleShape graphicsBox;
    sf::RectangleShape statsBox;
    
    sf::Vector2u windowSize;
};