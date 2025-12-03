#include "InventoryUI.h"
#include "InventorySystem.h"
#include <cmath>

InventoryUI::InventoryUI(ResourceManager& resources)
    : resources(resources),
      tooltipTitle(resources.getFont("main"), "", 18),
      tooltipDescription(resources.getFont("main"), "", 14)
{
    tooltipBackground.setFillColor(sf::Color(30, 30, 40, 240));
    tooltipBackground.setOutlineColor(sf::Color(100, 100, 120));
    tooltipBackground.setOutlineThickness(1.f);
    
    tooltipTitle.setFillColor(sf::Color::White);
    tooltipDescription.setFillColor(sf::Color(200, 200, 200));
}

// Store layout parameters and rebuild grid
void InventoryUI::updateLayout(const sf::FloatRect& containerBounds, float padding, float scaleY) {
    this->containerBounds = containerBounds;
    this->currentPadding = padding;
    this->currentScale = scaleY;
    
    createGrid(containerBounds, padding);
}

// Calculate grid cell positions and sizes
void InventoryUI::createGrid(const sf::FloatRect& bounds, float padding) {
    grid.clear();
    
    float availableWidth = bounds.size.x - (padding * 2);
    float availableHeight = bounds.size.y - (padding * 2);
    
    // Calculate cell size to fit grid
    float cellWidth = (availableWidth - (cellPadding * (columns - 1))) / columns;
    float cellHeight = (availableHeight - (cellPadding * (visibleRows - 1))) / visibleRows;
    float cellSide = std::min(cellWidth, cellHeight);
    
    cellSize = sf::Vector2f(cellSide, cellSide);
    
    // Center the grid horizontally
    float totalGridWidth = (cellSide * columns) + (cellPadding * (columns - 1));
    float startX = bounds.position.x + padding + (availableWidth - totalGridWidth) / 2.f;
    float startY = bounds.position.y + padding;
    
    // Create all visible cells
    for (int row = 0; row < visibleRows; ++row) {
        for (int col = 0; col < columns; ++col) {
            GridCell cell;
            
            float x = startX + col * (cellSide + cellPadding);
            float y = startY + row * (cellSide + cellPadding);
            
            cell.bounds = sf::FloatRect({x, y}, {cellSide, cellSide});
            cell.background.setSize({cellSide, cellSide});
            cell.background.setPosition({x, y});
            cell.background.setFillColor(sf::Color(50, 50, 60, 180));
            cell.background.setOutlineColor(sf::Color(80, 80, 90));
            cell.background.setOutlineThickness(1.f);
            
            grid.push_back(cell);
        }
    }
}

// Find which grid cell contains the given position
int InventoryUI::getCellAtPosition(const sf::Vector2f& pos) const {
    for (size_t i = 0; i < grid.size(); ++i) {
        if (grid[i].bounds.contains(pos)) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void InventoryUI::updateScroll(float delta, int totalItems) {
    scrollOffset += static_cast<int>(delta);
    scrollOffset = std::max(0, std::min(scrollOffset, getMaxScroll(totalItems)));
}

// Calculate maximum scroll offset based on item count
int InventoryUI::getMaxScroll(int totalItems) const {
    int totalRows = (totalItems + columns - 1) / columns;
    return std::max(0, totalRows - visibleRows);
}

// Handle mouse clicks and scrolling
InventoryInteraction InventoryUI::handleEvent(const sf::Event& event, const InventorySystem& inventory) {
    InventoryInteraction result;
    
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f mousePos(static_cast<float>(mouseButtonPressed->position.x),
                              static_cast<float>(mouseButtonPressed->position.y));
        
        int cellIndex = getCellAtPosition(mousePos);
        if (cellIndex >= 0) {
            // Convert cell index to item index accounting for scroll
            int itemIndex = (scrollOffset * columns) + cellIndex;
            
            if (itemIndex < static_cast<int>(inventory.getItems().size())) {
                // Right-click to delete (shift+right-click for all)
                if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
                    result.action = InventoryAction::DeleteRequested;
                    result.itemIndex = itemIndex;
                    result.removeAll = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || 
                                      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);
                }
            }
        }
    }
    else if (const auto* mouseWheelScrolled = event.getIf<sf::Event::MouseWheelScrolled>()) {
        sf::Vector2f mousePos(static_cast<float>(mouseWheelScrolled->position.x),
                              static_cast<float>(mouseWheelScrolled->position.y));
        
        // Only scroll if mouse is over inventory
        if (containerBounds.contains(mousePos)) {
            updateScroll(mouseWheelScrolled->delta, static_cast<int>(inventory.getItems().size()));
        }
    }
    
    return result;
}

// Update hover state and prepare tooltip
void InventoryUI::update(const sf::Vector2i& mousePos, const InventorySystem& inventory) {
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    hoveredCell = getCellAtPosition(mousePosF);
    showTooltip = false;
    
    if (hoveredCell >= 0) {
        // Calculate actual item index with scroll offset
        int itemIndex = (scrollOffset * columns) + hoveredCell;
        
        if (itemIndex < static_cast<int>(inventory.getItems().size())) {
            const auto& item = inventory.getItems()[itemIndex];
            const ItemDefinition* def = inventory.getItemDefinition(item.id);
            
            if (def) {
                showTooltip = true;
                
                // Setup tooltip text
                tooltipTitle.setString(def->name);
                tooltipDescription.setString(def->description);
                
                // Calculate tooltip size
                float tooltipPadding = 8.f;
                float tooltipWidth = std::max(tooltipTitle.getGlobalBounds().size.x,
                                             tooltipDescription.getGlobalBounds().size.x) + tooltipPadding * 2;
                float tooltipHeight = tooltipTitle.getGlobalBounds().size.y + 
                                     tooltipDescription.getGlobalBounds().size.y + 
                                     tooltipPadding * 3;
                
                // Position tooltip near mouse, adjusting to stay on screen
                sf::Vector2f tooltipPos(mousePosF.x + 15.f, mousePosF.y + 15.f);
                
                if (tooltipPos.x + tooltipWidth > containerBounds.position.x + containerBounds.size.x) {
                    tooltipPos.x = mousePosF.x - tooltipWidth - 15.f;
                }
                if (tooltipPos.y + tooltipHeight > containerBounds.position.y + containerBounds.size.y) {
                    tooltipPos.y = mousePosF.y - tooltipHeight - 15.f;
                }
                
                tooltipBackground.setSize({tooltipWidth, tooltipHeight});
                tooltipBackground.setPosition(tooltipPos);
                
                tooltipTitle.setPosition({tooltipPos.x + tooltipPadding, 
                                         tooltipPos.y + tooltipPadding});
                tooltipDescription.setPosition({tooltipPos.x + tooltipPadding,
                                               tooltipPos.y + tooltipPadding * 2 + 
                                               tooltipTitle.getGlobalBounds().size.y});
            }
        }
    }
    
    // Clamp scroll to valid range
    int totalItems = static_cast<int>(inventory.getItems().size());
    int maxScroll = getMaxScroll(totalItems);
    scrollOffset = std::clamp(scrollOffset, 0, maxScroll);
}

// Render grid cells, item sprites, and tooltip
void InventoryUI::draw(sf::RenderWindow& window, const InventorySystem& inventory) {
    const auto& items = inventory.getItems();
    
    for (size_t i = 0; i < grid.size(); ++i) {
        auto& cell = grid[i];
        int itemIndex = (scrollOffset * columns) + static_cast<int>(i);
        
        // Highlight hovered cell
        if (static_cast<int>(i) == hoveredCell && itemIndex < static_cast<int>(items.size())) {
            cell.background.setFillColor(sf::Color(70, 70, 80, 200));
        } else {
            cell.background.setFillColor(sf::Color(50, 50, 60, 180));
        }
        
        window.draw(cell.background);
        
        // Draw item sprite if cell has an item
        if (itemIndex < static_cast<int>(items.size())) {
            const auto& item = items[itemIndex];
            const ItemDefinition* def = inventory.getItemDefinition(item.id);
            
            if (def) {
                try {
                    const sf::Texture& texture = resources.getTexture(item.id);
                    sf::Sprite sprite(texture);
                    
                    // Scale sprite to fit cell with padding
                    float itemPadding = 4.f;
                    float maxSize = cellSize.x - itemPadding * 2;
                    sf::Vector2u texSize = texture.getSize();
                    float scale = maxSize / std::max(static_cast<float>(texSize.x), 
                                                    static_cast<float>(texSize.y));
                    sprite.setScale({scale, scale});
                    
                    // Center sprite in cell
                    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
                    sprite.setPosition({
                        cell.bounds.position.x + (cellSize.x - spriteBounds.size.x) / 2.f,
                        cell.bounds.position.y + (cellSize.y - spriteBounds.size.y) / 2.f
                    });
                    
                    window.draw(sprite);
                    
                    // Quantity text temporarily disabled to fix duplication bug
                    
                    // if (item.quantity > 1) {
                    //     sf::Text quantityText(resources.getFont("main"), 
                    //                         std::to_string(item.quantity),
                    //                         static_cast<unsigned int>(14 * currentScale));
                    //     quantityText.setFillColor(sf::Color::White);
                        
                    //     sf::FloatRect textBounds = quantityText.getGlobalBounds();
                    //     quantityText.setPosition({
                    //         cell.bounds.position.x + cellSize.x - textBounds.size.x - 4.f,
                    //         cell.bounds.position.y + cellSize.y - textBounds.size.y - 4.f
                    //     });
                        
                    //     window.draw(quantityText);
                    // }
                } catch (...) {
                    // Texture not loaded, skip drawing
                }
            }
        }
    }
    
    // Draw tooltip on top of everything
    if (showTooltip) {
        window.draw(tooltipBackground);
        window.draw(tooltipTitle);
        window.draw(tooltipDescription);
    }
}