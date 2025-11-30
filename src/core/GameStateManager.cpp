#include "GameStateManager.h"
#include "SceneManager.h"
#include "InventorySystem.h"
#include <fstream>
#include <iostream>

GameStateManager::GameStateManager() {}

bool GameStateManager::checkCondition(const Condition& condition) const {
    if (condition.flag.empty()) {
        return true;
    }
    
    auto it = flags.find(condition.flag);
    if (it == flags.end()) {
        return !condition.requiredValue;
    }
    
    return it->second == condition.requiredValue;
}

void GameStateManager::applyEffects(const Effects& effects, InventorySystem* inventory) {
    if (!effects.addFlag.empty()) {
        flags[effects.addFlag] = true;
    }
    
    if (!effects.removeFlag.empty()) {
        flags[effects.removeFlag] = false;
    }
    
    for (const auto& [statName, modifier] : effects.modifyStats) {
        stats[statName] += modifier;
    }
    
    if (!effects.addItem.empty()) {
        inventory->addItem(effects.addItem, effects.addItemQuantity);
    }
}

void GameStateManager::saveGame(const std::string& scriptId, const std::string& sceneId,
                                const InventorySystem* inventory) {
    using json = nlohmann::json;
    
    json saveData;
    saveData["playerName"] = "";
    saveData["currentScript"] = scriptId;
    saveData["currentScene"] = sceneId;
    
    json flagsJson = json::object();
    for (const auto& [key, value] : flags) {
        flagsJson[key] = value;
    }
    saveData["flags"] = flagsJson;
    
    json statsJson = json::object();
    for (const auto& [key, value] : stats) {
        statsJson[key] = value;
    }
    saveData["stats"] = statsJson;
    
    if (inventory) {
        inventory->saveToJson(saveData);
    }
    
    std::ofstream file("assets/save_data.json");
    if (file.is_open()) {
        file << saveData.dump(2);
        file.close();
        std::cout << "Game saved successfully" << std::endl;
    } else {
        std::cerr << "Failed to save game" << std::endl;
    }
}

void GameStateManager::loadGame(InventorySystem* inventory) {
    using json = nlohmann::json;
    
    std::ifstream file("assets/save_data.json");
    if (!file.is_open()) {
        std::cout << "No save file found, starting fresh" << std::endl;
        return;
    }
    
    try {
        file.seekg(0, std::ios::end);
        if (file.tellg() == 0) {
            std::cout << "Save file is empty, starting fresh" << std::endl;
            return;
        }
        file.seekg(0, std::ios::beg);
        
        json saveData;
        file >> saveData;
        
        if (saveData.contains("flags") && saveData["flags"].is_object()) {
            for (auto& [key, value] : saveData["flags"].items()) {
                flags[key] = value;
            }
        }
        
        if (saveData.contains("stats") && saveData["stats"].is_object()) {
            for (auto& [key, value] : saveData["stats"].items()) {
                stats[key] = value;
            }
        }
        
        if (inventory && saveData.contains("inventory")) {
            inventory->loadFromJson(saveData);
        }
        
        std::cout << "Game loaded successfully" << std::endl;
    } catch (const json::exception& e) {
        std::cerr << "Failed to load save data: " << e.what() << std::endl;
        std::cout << "Starting fresh due to corrupted save" << std::endl;
    }
}