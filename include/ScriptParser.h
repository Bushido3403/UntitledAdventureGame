// SFML 3.x

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

// Add these structs before the Choice struct
struct Condition {
    std::string flag;  // Flag name to check
    bool requiredValue = true;  // Default: flag must be true
};

struct Effects {
    std::string addFlag;  // Flag to set to true
    std::string removeFlag;  // Flag to set to false
    std::unordered_map<std::string, int> modifyStats;  // Stats to modify
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