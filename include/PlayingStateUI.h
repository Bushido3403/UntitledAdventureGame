#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "ResourceManager.h"
#include "DialogBox.h"
#include "Button.h"
#include "LayoutManager.h"
#include "InventoryUI.h"
#include "InventorySystem.h"
#include "ConfirmationDialog.h"

class SceneManager;
struct Scene;

// Manages all UI elements for the playing state
class PlayingStateUI {
public:
    PlayingStateUI(ResourceManager& resources);
    
    // Update UI element positions based on window size
    void updatePositions(const sf::Vector2u& newWindowSize, const Scene* currentScene);
    
    // Update choice button positions and sizes
    void updateChoiceButtons(const std::vector<std::unique_ptr<Button>>& buttons, const Scene* currentScene);
    
    // Draw all UI elements to the window
    void draw(sf::RenderWindow& window, const std::vector<std::unique_ptr<Button>>& buttons, 
              sf::Sprite* graphicsSprite);
    
    // Get the dialog box
    DialogBox& getDialogBox() { return *dialogBox; }
    
    // Get current window size
    const sf::Vector2u& getWindowSize() const { return windowSize; }
    
    // Set the inventory system reference
    void setInventorySystem(InventorySystem* inventory);
    
    // Handle inventory-related events
    InventoryInteraction handleInventoryEvent(const sf::Event& event);
    
    // Update inventory hover state
    void updateInventory(const sf::Vector2i& mousePos);
    
    // Draw the confirmation dialog
    void drawConfirmationDialog(sf::RenderWindow& window);
    
    // Get the confirmation dialog
    ConfirmationDialog& getConfirmationDialog() { return *confirmationDialog; }
    
private:
    // Update positions of choice buttons
    void updateChoicePositions(const std::vector<std::unique_ptr<Button>>& buttons, const Scene* currentScene);
    
    ResourceManager& resources;
    std::unique_ptr<DialogBox> dialogBox;
    std::unique_ptr<LayoutManager> layoutManager;
    
    // Background shapes for different UI sections
    sf::RectangleShape background;
    sf::RectangleShape dialogBoxShape;
    sf::RectangleShape graphicsBox;
    sf::RectangleShape statsBox;
    
    sf::Vector2u windowSize;
    std::unique_ptr<InventoryUI> inventoryUI;
    InventorySystem* inventorySystem = nullptr;
    std::unique_ptr<ConfirmationDialog> confirmationDialog;
};