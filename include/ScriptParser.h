// SFML 3.x

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>

struct Choice {
    std::string text;
    std::string nextScene;
    std::string nextScript;  // Add this for script chaining
};

struct Scene {
    std::string id;
    std::string background;
    std::string text;
    std::string speaker;
    std::vector<Choice> choices;
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