#include "GameStateManager.h"
#include "SceneManager.h"
#include "InventorySystem.h"
#include <fstream>
#include <iostream>

GameStateManager::GameStateManager() {}

bool GameStateManager::checkCondition(const Condition& condition) const {
    std::cout << "Checking condition - flag: '" << condition.flag 
              << "', flagsNot: '" << condition.flagsNot << "'" << std::endl;
    
    // Check 'flag' field (must be true/present)
    if (!condition.flag.empty()) {
        auto it = flags.find(condition.flag);
        bool flagExists = (it != flags.end());
        bool flagValue = flagExists ? it->second : false;
        std::cout << "  Flag '" << condition.flag << "' exists: " << flagExists 
                  << ", value: " << flagValue << ", required: " << condition.requiredValue << std::endl;
        
        if (it == flags.end()) {
            return !condition.requiredValue;
        }
        if (it->second != condition.requiredValue) {
            return false;
        }
    }
    
    // Check 'flagsNot' field (must be false/absent)
    if (!condition.flagsNot.empty()) {
        auto it = flags.find(condition.flagsNot);
        bool flagExists = (it != flags.end());
        bool flagValue = flagExists ? it->second : false;
        std::cout << "  FlagsNot '" << condition.flagsNot << "' exists: " << flagExists 
                  << ", value: " << flagValue << std::endl;
        
        if (it != flags.end() && it->second == true) {
            std::cout << "  -> Condition FAILED (flagsNot is true)" << std::endl;
            return false;
        }
    }
    
    std::cout << "  -> Condition PASSED" << std::endl;
    return true;
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
    
    for (const auto& [itemId, quantity] : effects.addItems) {
        if (inventory) {
            inventory->addItem(itemId, quantity);
        }
    }

    for (const auto& [itemId, quantity] : effects.removeItems) {
        if (inventory) {
            inventory->removeItem(itemId, quantity, this);
        }
    }
}

void GameStateManager::saveGame(const std::string& scriptId, const std::string& sceneId,
                                const InventorySystem* inventory) {
    using json = nlohmann::json;
    
    // Update current script/scene
    currentScript = scriptId;
    currentScene = sceneId;
    
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
        std::cout << "Game saved: " << scriptId << " - " << sceneId << std::endl;
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
        
        // Load current script/scene
        if (saveData.contains("currentScript")) {
            currentScript = saveData["currentScript"];
        }
        if (saveData.contains("currentScene")) {
            currentScene = saveData["currentScene"];
        }
        
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
        
        std::cout << "Game loaded: " << currentScript << " - " << currentScene << std::endl;
    } catch (const json::exception& e) {
        std::cerr << "Failed to load save data: " << e.what() << std::endl;
        std::cout << "Starting fresh due to corrupted save" << std::endl;
    }
}

void GameStateManager::clearSave() {
    // Preserve intro_complete flag
    bool preservedIntroComplete = false;
    auto it = flags.find("intro_complete");
    if (it != flags.end()) {
        preservedIntroComplete = it->second;
    }

    // Reset in-memory state
    flags.clear();
    stats.clear();
    currentScript.clear();
    currentScene.clear();

    // Restore intro_complete flag if it existed
    if (preservedIntroComplete) {
        flags["intro_complete"] = true;
    }

    // Save with reset scene
    using json = nlohmann::json;
    json saveData;
    saveData["playerName"] = "";
    saveData["currentScript"] = "";
    saveData["currentScene"] = "a1_s01_mythic_void";
    
    json flagsJson = json::object();
    for (const auto& [key, value] : flags) {
        flagsJson[key] = value;
    }
    saveData["flags"] = flagsJson;
    saveData["stats"] = json::object();
    saveData["inventory"] = json::array();

    std::ofstream file("assets/save_data.json", std::ios::trunc);
    if (file.is_open()) {
        file << saveData.dump(2);
        file.close();
        std::cout << "Save data reset to beginning (intro_complete preserved)" << std::endl;
    } else {
        std::cerr << "Failed to reset save data file" << std::endl;
    }
}