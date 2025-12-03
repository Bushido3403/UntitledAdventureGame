#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <memory>
#include "ResourceManager.h"

struct InventoryItem;
struct ItemDefinition;
class InventorySystem;

// Actions that can be performed on inventory items
enum class InventoryAction {
    None,
    DeleteRequested
};

// Result of user interaction with inventory UI
struct InventoryInteraction {
    InventoryAction action = InventoryAction::None;
    int itemIndex = -1;
    bool removeAll = false;  // True if shift+right-click
};

// Renders inventory grid, handles mouse interactions, and shows tooltips
class InventoryUI {
public:
    InventoryUI(ResourceManager& resources);
    
    // Recreate grid layout when window resizes
    void updateLayout(const sf::FloatRect& containerBounds, float padding, float scaleY);
    
    // Process mouse clicks and scrolling
    InventoryInteraction handleEvent(const sf::Event& event, const InventorySystem& inventory);
    
    // Update hover state and tooltip
    void update(const sf::Vector2i& mousePos, const InventorySystem& inventory);
    
    // Render grid, items, and tooltip
    void draw(sf::RenderWindow& window, const InventorySystem& inventory);
    
private:
    // Single cell in the inventory grid
    struct GridCell {
        sf::FloatRect bounds;
        sf::RectangleShape background;
    };
    
    void createGrid(const sf::FloatRect& containerBounds, float padding);
    int getCellAtPosition(const sf::Vector2f& pos) const;
    void updateScroll(float delta, int totalItems);
    int getMaxScroll(int totalItems) const;
    
    ResourceManager& resources;
    std::vector<GridCell> grid;
    
    int hoveredCell = -1;
    int scrollOffset = 0;  // How many rows have been scrolled
    
    sf::FloatRect containerBounds;
    sf::Vector2f cellSize;
    int columns = 4;
    int visibleRows = 3;
    float cellPadding = 4.f;
    float currentPadding = 0.f;
    float currentScale = 1.f;
    
    // Tooltip elements
    sf::RectangleShape tooltipBackground;
    sf::Text tooltipTitle;
    sf::Text tooltipDescription;
    bool showTooltip = false;
};