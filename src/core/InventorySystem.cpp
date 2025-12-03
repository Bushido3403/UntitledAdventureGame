#include "InventorySystem.h"
#include "GameStateManager.h"
#include <fstream>
#include <iostream>

InventorySystem::InventorySystem(ResourceManager& resources)
    : resources(resources)
{
    loadItemDefinitions();
}

// Parse items.json and preload textures
bool InventorySystem::loadItemDefinitions() {
    using json = nlohmann::json;
    
    std::ifstream file("assets/items/items.json");
    if (!file.is_open()) {
        std::cerr << "Failed to load item definitions" << std::endl;
        return false;
    }
    
    try {
        json itemsJson;
        file >> itemsJson;
        
        // Parse each item definition
        for (auto& [itemId, itemData] : itemsJson.items()) {
            ItemDefinition def;
            def.id = itemId;
            def.name = itemData.value("name", itemId);
            def.description = itemData.value("description", "");
            def.texturePath = itemData.value("texture", "");
            def.stackable = itemData.value("stackable", true);
            def.maxStackSize = itemData.value("maxStackSize", 99);
            
            itemDefinitions[itemId] = def;
            
            // Preload texture for this item
            if (!def.texturePath.empty()) {
                resources.loadTexture(itemId, def.texturePath);
            }
        }
        
        std::cout << "Loaded " << itemDefinitions.size() << " item definitions" << std::endl;
        return true;
    }
    catch (const json::exception& e) {
        std::cerr << "Failed to parse item definitions: " << e.what() << std::endl;
        return false;
    }
}

const ItemDefinition* InventorySystem::getItemDefinition(const std::string& itemId) const {
    auto it = itemDefinitions.find(itemId);
    if (it != itemDefinitions.end()) {
        return &it->second;
    }
    return nullptr;
}

// Add items with intelligent stacking behavior
bool InventorySystem::addItem(const std::string& itemId, int quantity) {
    const ItemDefinition* def = getItemDefinition(itemId);
    if (!def) {
        std::cerr << "Item not found: " << itemId << std::endl;
        return false;
    }
    
    int remainingQuantity = quantity;
    
    if (def->stackable) {
        // First, try to fill existing stacks
        for (auto& item : items) {
            if (item.id == itemId && item.quantity < def->maxStackSize) {
                int canAdd = std::min(remainingQuantity, def->maxStackSize - item.quantity);
                item.quantity += canAdd;
                remainingQuantity -= canAdd;
                
                if (remainingQuantity <= 0) {
                    return true;
                }
            }
        }
    }
    
    // Create new stacks for remaining quantity
    while (remainingQuantity > 0) {
        int stackSize = def->stackable ? std::min(remainingQuantity, def->maxStackSize) : 1;
        items.emplace_back(itemId, stackSize);
        remainingQuantity -= stackSize;
    }
    
    return true;
}

// Remove items and update game state flags when fully removed
bool InventorySystem::removeItem(const std::string& itemId, int quantity, GameStateManager* gameState) {
    int remainingQuantity = quantity;
    
    // Remove from stacks until quantity is satisfied
    for (auto it = items.begin(); it != items.end();) {
        if (it->id == itemId) {
            if (it->quantity <= remainingQuantity) {
                remainingQuantity -= it->quantity;
                it = items.erase(it);
            } else {
                it->quantity -= remainingQuantity;
                remainingQuantity = 0;
                break;
            }
            
            if (remainingQuantity <= 0) {
                // Update game state when item is completely removed
                if (gameState && !hasItem(itemId)) {
                    if (itemId == "asgard_sword") {
                        gameState->setFlag("has_asgard_sword", false);
                    } else if (itemId == "bronze_key") {
                        gameState->setFlag("has_bronze_key", false);
                    }
                }
                return true;
            }
        } else {
            ++it;
        }
    }
    
    // Final check to update game state
    if (gameState && remainingQuantity == 0 && !hasItem(itemId)) {
        if (itemId == "asgard_sword") {
            gameState->setFlag("has_asgard_sword", false);
        } else if (itemId == "bronze_key") {
            gameState->setFlag("has_bronze_key", false);
        }
    }
    
    return remainingQuantity == 0;
}

// Remove item at specific inventory slot
void InventorySystem::removeItemAtIndex(int index, int quantity, GameStateManager* gameState) {
    if (index < 0 || index >= static_cast<int>(items.size())) {
        return;
    }
    
    std::string itemId = items[index].id;
    
    if (items[index].quantity <= quantity) {
        items.erase(items.begin() + index);
    } else {
        items[index].quantity -= quantity;
    }
    
    // Update game state if item is completely removed
    if (gameState && !hasItem(itemId)) {
        if (itemId == "asgard_sword") {
            gameState->setFlag("has_asgard_sword", false);
        } else if (itemId == "bronze_key") {
            gameState->setFlag("has_bronze_key", false);
        }
    }
}

bool InventorySystem::hasItem(const std::string& itemId) const {
    for (const auto& item : items) {
        if (item.id == itemId) {
            return true;
        }
    }
    return false;
}

// Sum quantities across all stacks of an item
int InventorySystem::getItemCount(const std::string& itemId) const {
    int count = 0;
    for (const auto& item : items) {
        if (item.id == itemId) {
            count += item.quantity;
        }
    }
    return count;
}

// Serialize inventory to JSON for saving
void InventorySystem::saveToJson(nlohmann::json& saveData) const {
    using json = nlohmann::json;
    
    json inventoryJson = json::array();
    for (const auto& item : items) {
        json itemJson;
        itemJson["id"] = item.id;
        itemJson["quantity"] = item.quantity;
        inventoryJson.push_back(itemJson);
    }
    
    saveData["inventory"] = inventoryJson;
}

// Load inventory from JSON save data
void InventorySystem::loadFromJson(const nlohmann::json& saveData) {
    items.clear();
    
    if (!saveData.contains("inventory") || !saveData["inventory"].is_array()) {
        return;
    }
    
    for (const auto& itemJson : saveData["inventory"]) {
        std::string id = itemJson.value("id", "");
        int quantity = itemJson.value("quantity", 1);
        
        // Only load items that have valid definitions
        if (!id.empty() && getItemDefinition(id)) {
            items.emplace_back(id, quantity);
        }
    }
}