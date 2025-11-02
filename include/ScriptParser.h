// SFML 3.x

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>

struct Choice {
    std::string text;
    std::string nextScene;
};

struct Scene {
    std::string id;
    std::string background;
    std::string text;
    std::string speaker;
    std::vector<Choice> choices;
};

struct GameScript {
    std::string scriptId;
    std::string title;
    std::vector<Scene> scenes;
};

class ScriptParser {
public:
    static std::optional<GameScript> loadScript(const std::string& path);
    static const Scene* findScene(const GameScript& script, const std::string& sceneId);
};