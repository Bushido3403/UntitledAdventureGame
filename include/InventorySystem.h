#pragma once
#include <string>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>
#include "ResourceManager.h"

class GameStateManager;  // Add forward declaration

struct ItemDefinition {
    std::string id;
    std::string name;
    std::string description;
    std::string texturePath;
    bool stackable = true;
    int maxStackSize = 99;
};

struct InventoryItem {
    std::string id;
    int quantity = 1;
    
    InventoryItem(const std::string& id, int quantity = 1) 
        : id(id), quantity(quantity) {}
};

class InventorySystem {
public:
    InventorySystem(ResourceManager& resources);
    
    bool addItem(const std::string& itemId, int quantity = 1);
    bool removeItem(const std::string& itemId, int quantity = 1, GameStateManager* gameState = nullptr);
    bool hasItem(const std::string& itemId) const;
    int getItemCount(const std::string& itemId) const;
    
    const std::vector<InventoryItem>& getItems() const { return items; }
    const ItemDefinition* getItemDefinition(const std::string& itemId) const;
    
    void removeItemAtIndex(int index, int quantity = 1, GameStateManager* gameState = nullptr);
    
    void saveToJson(nlohmann::json& saveData) const;
    void loadFromJson(const nlohmann::json& saveData);
    
private:
    bool loadItemDefinitions();
    
    ResourceManager& resources;
    std::vector<InventoryItem> items;
    std::unordered_map<std::string, ItemDefinition> itemDefinitions;
};