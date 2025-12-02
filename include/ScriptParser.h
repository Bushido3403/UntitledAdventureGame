// SFML 3.x

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

// Add these structs before the Choice struct
struct Condition {
    std::string flag;  // Flag name to check (must be true)
    std::string flagsNot;  // Flag name to check (must be false/absent)
    bool requiredValue = true;  // For 'flag' field only
};

struct Effects {
    std::string addFlag;
    std::string removeFlag;
    std::unordered_map<std::string, int> modifyStats;
    std::vector<std::pair<std::string, int>> addItems;
    std::vector<std::pair<std::string, int>> removeItems;  // NEW
};

struct Choice {
    std::string text;
    std::string nextScene;
    std::string nextScript;  // Add this for script chaining
    std::optional<Condition> condition;  // Add condition support
};

struct Scene {
    std::string id;
    std::string background;
    std::string text;
    std::string speaker;
    std::string speakerColor;  // Add this field
    std::vector<Choice> choices;
    std::optional<Effects> effects;  // Add effects support
};

struct ScriptMetadata {
    int chapter = 1;
    std::vector<std::string> unlocks;
    std::string estimatedTime;
};

struct GameScript {
    std::string scriptId;
    std::string title;
    ScriptMetadata metadata;  // Add metadata
    std::vector<Scene> scenes;
};

class ScriptParser {
public:
    static std::optional<GameScript> loadScript(const std::string& path);
    static const Scene* findScene(const GameScript& script, const std::string& sceneId);
};