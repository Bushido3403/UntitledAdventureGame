#pragma once
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

struct Condition;
struct Effects;
class InventorySystem;  // Forward declaration

class GameStateManager {
public:
    GameStateManager();
    
    bool checkCondition(const Condition& condition) const;
    void applyEffects(const Effects& effects, InventorySystem* inventory);
    
    void saveGame(const std::string& scriptId, const std::string& sceneId, 
                  const InventorySystem* inventory = nullptr);
    void loadGame(InventorySystem* inventory = nullptr);
    
    const std::unordered_map<std::string, bool>& getFlags() const { return flags; }
    const std::unordered_map<std::string, int>& getStats() const { return stats; }
    
    // Add these methods
    std::string getCurrentScript() const { return currentScript; }
    std::string getCurrentScene() const { return currentScene; }
    bool hasSaveData() const { return !currentScript.empty(); }
    
    void clearSave();
    void setFlag(const std::string& flag, bool value) { flags[flag] = value; }

private:
    std::unordered_map<std::string, bool> flags;
    std::unordered_map<std::string, int> stats;
    std::string currentScript;
    std::string currentScene;
};