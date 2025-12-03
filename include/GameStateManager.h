#pragma once
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

struct Condition;
struct Effects;
class InventorySystem;  // Forward declaration

// Manages game state: flags, stats, saves
class GameStateManager {
public:
    GameStateManager();
    
    // Check if a condition is met based on current flags
    bool checkCondition(const Condition& condition) const;
    
    // Apply effects to flags, stats, and inventory
    void applyEffects(const Effects& effects, InventorySystem* inventory);
    
    // Save current game state to file
    void saveGame(const std::string& scriptId, const std::string& sceneId, 
                  const InventorySystem* inventory = nullptr);
    
    // Load game state from file
    void loadGame(InventorySystem* inventory = nullptr);
    
    // Get current flags and stats
    const std::unordered_map<std::string, bool>& getFlags() const { return flags; }
    const std::unordered_map<std::string, int>& getStats() const { return stats; }
    
    // Get current script/scene location
    std::string getCurrentScript() const { return currentScript; }
    std::string getCurrentScene() const { return currentScene; }
    bool hasSaveData() const { return !currentScript.empty(); }
    
    // Reset save data to beginning
    void clearSave();
    
    // Manually set a flag
    void setFlag(const std::string& flag, bool value) { flags[flag] = value; }

private:
    std::unordered_map<std::string, bool> flags;     // Story flags (true/false)
    std::unordered_map<std::string, int> stats;      // Numeric stats
    std::string currentScript;                        // Current story script
    std::string currentScene;                         // Current scene within script
};