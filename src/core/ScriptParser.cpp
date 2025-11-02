// SFML 3.x

#include "ScriptParser.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::optional<GameScript> ScriptParser::loadScript(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open script file: " << path << std::endl;
        return std::nullopt;
    }

    try {
        json j;
        file >> j;

        GameScript script;
        script.scriptId = j["scriptId"];
        script.title = j["title"];

        for (const auto& sceneJson : j["scenes"]) {
            Scene scene;
            scene.id = sceneJson["id"];
            scene.background = sceneJson["background"];
            scene.text = sceneJson["text"];
            scene.speaker = sceneJson["speaker"];

            for (const auto& choiceJson : sceneJson["choices"]) {
                Choice choice;
                choice.text = choiceJson["text"];
                choice.nextScene = choiceJson["nextScene"];
                scene.choices.push_back(choice);
            }

            script.scenes.push_back(scene);
        }

        return script;
    } catch (const json::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return std::nullopt;
    }
}

const Scene* ScriptParser::findScene(const GameScript& script, const std::string& sceneId) {
    for (const auto& scene : script.scenes) {
        if (scene.id == sceneId) {
            return &scene;
        }
    }
    return nullptr;
}