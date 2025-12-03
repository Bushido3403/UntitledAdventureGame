// SFML 3.x

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

// Condition for showing/hiding choices
struct Condition {
    std::string flag;  // Flag name to check (must be true)
    std::string flagsNot;  // Flag name to check (must be false/absent)
    bool requiredValue = true;  // For 'flag' field only
};

// Effects applied when a scene is displayed
struct Effects {
    std::string addFlag;
    std::string removeFlag;
    std::unordered_map<std::string, int> modifyStats;
    std::vector<std::pair<std::string, int>> addItems;
    std::vector<std::pair<std::string, int>> removeItems;
};

// Player choice in a scene
struct Choice {
    std::string text;
    std::string nextScene;
    std::string nextScript;
    std::optional<Condition> condition;
};

// Individual scene with text, choices, and effects
struct Scene {
    std::string id;
    std::string background;
    std::string text;
    std::string speaker;
    std::string speakerColor;
    std::vector<Choice> choices;
    std::optional<Effects> effects;
};

// Script metadata (chapter info, unlocks, etc.)
struct ScriptMetadata {
    int chapter = 1;
    std::vector<std::string> unlocks;
    std::string estimatedTime;
};

// Complete game script with metadata and scenes
struct GameScript {
    std::string scriptId;
    std::string title;
    ScriptMetadata metadata;
    std::vector<Scene> scenes;
};

// Parses JSON script files
class ScriptParser {
public:
    // Load script from JSON file
    static std::optional<GameScript> loadScript(const std::string& path);
    
    // Find a scene by ID in the script
    static const Scene* findScene(const GameScript& script, const std::string& sceneId);
};