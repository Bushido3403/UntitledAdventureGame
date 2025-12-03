#pragma once
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "ResourceManager.h"

class GameStateManager;

// Template/blueprint for items - defines properties shared by all instances of an item type
struct ItemDefinition {
    std::string id;
    std::string name;
    std::string description;
    std::string texturePath;
    bool stackable = true;
    int maxStackSize = 99;
};

// Actual item instance in inventory - references a definition and has a quantity
struct InventoryItem {
    std::string id;
    int quantity = 1;
    
    InventoryItem(const std::string& id, int quantity = 1) 
        : id(id), quantity(quantity) {}
};

// Manages inventory: loading item definitions, adding/removing items, and save/load
class InventorySystem {
public:
    InventorySystem(ResourceManager& resources);
    
    // Add items to inventory (stacks if possible)
    bool addItem(const std::string& itemId, int quantity = 1);
    
    // Remove items from inventory and optionally update game state flags
    bool removeItem(const std::string& itemId, int quantity = 1, GameStateManager* gameState = nullptr);
    
    // Check if inventory contains at least one of an item
    bool hasItem(const std::string& itemId) const;
    
    // Get total quantity of an item across all stacks
    int getItemCount(const std::string& itemId) const;
    
    const std::vector<InventoryItem>& getItems() const { return items; }
    const ItemDefinition* getItemDefinition(const std::string& itemId) const;
    
    // Remove item at specific grid position
    void removeItemAtIndex(int index, int quantity = 1, GameStateManager* gameState = nullptr);
    
    // Serialize/deserialize inventory for save system
    void saveToJson(nlohmann::json& saveData) const;
    void loadFromJson(const nlohmann::json& saveData);
    
private:
    // Load item definitions from JSON file
    bool loadItemDefinitions();
    
    ResourceManager& resources;
    std::vector<InventoryItem> items;  // Actual inventory contents
    std::unordered_map<std::string, ItemDefinition> itemDefinitions;  // Item templates
};