#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <memory>
#include "ResourceManager.h"

struct InventoryItem;
struct ItemDefinition;
class InventorySystem;

enum class InventoryAction {
    None,
    DeleteRequested
};

struct InventoryInteraction {
    InventoryAction action = InventoryAction::None;
    int itemIndex = -1;
    bool removeAll = false;  // NEW: indicates shift-click to remove all
};

class InventoryUI {
public:
    InventoryUI(ResourceManager& resources);
    
    void updateLayout(const sf::FloatRect& containerBounds, float padding, float scaleY);
    InventoryInteraction handleEvent(const sf::Event& event, const InventorySystem& inventory);
    void update(const sf::Vector2i& mousePos, const InventorySystem& inventory);
    void draw(sf::RenderWindow& window, const InventorySystem& inventory);
    
private:
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
    int scrollOffset = 0;
    
    sf::FloatRect containerBounds;
    sf::Vector2f cellSize;
    int columns = 4;
    int visibleRows = 3;
    float cellPadding = 4.f;
    float currentPadding = 0.f;
    float currentScale = 1.f;
    
    // Tooltip
    sf::RectangleShape tooltipBackground;
    sf::Text tooltipTitle;
    sf::Text tooltipDescription;
    bool showTooltip = false;
};