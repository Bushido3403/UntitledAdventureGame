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

        // Parse metadata if present
        if (j.contains("metadata")) {
            const auto& metaJson = j["metadata"];
            if (metaJson.contains("chapter")) {
                script.metadata.chapter = metaJson["chapter"];
            }
            if (metaJson.contains("unlocks")) {
                for (const auto& unlock : metaJson["unlocks"]) {
                    script.metadata.unlocks.push_back(unlock);
                }
            }
            if (metaJson.contains("estimatedTime")) {
                script.metadata.estimatedTime = metaJson["estimatedTime"];
            }
        }

        for (const auto& sceneJson : j["scenes"]) {
            Scene scene;
            scene.id = sceneJson["id"];
            scene.background = sceneJson["background"];
            scene.text = sceneJson["text"];
            scene.speaker = sceneJson["speaker"];

            // Parse speaker color if present, default to white
            if (sceneJson.contains("speakerColor")) {
                scene.speakerColor = sceneJson["speakerColor"];
            } else {
                scene.speakerColor = "#ffffffff";  // Default white color
            }

            for (const auto& choiceJson : sceneJson["choices"]) {
                Choice choice;
                choice.text = choiceJson["text"];
                choice.nextScene = choiceJson["nextScene"];

                // Check for nextScript (script chaining)
                if (choiceJson.contains("nextScript")) {
                    choice.nextScript = choiceJson["nextScript"];
                }

                // In the choices loop, after parsing nextScript:
                if (choiceJson.contains("condition")) {
                    Condition cond;
                    const auto& condJson = choiceJson["condition"];
                    if (condJson.contains("flag")) {
                        cond.flag = condJson["flag"];
                    }
                    if (condJson.contains("flagsNot")) {
                        cond.flagsNot = condJson["flagsNot"];
                    }
                    choice.condition = cond;
                }

                scene.choices.push_back(choice);
            }

            // After parsing all choices for a scene:
            if (sceneJson.contains("effects")) {
                Effects eff;
                const auto& effJson = sceneJson["effects"];
                
                if (effJson.contains("addFlag")) {
                    eff.addFlag = effJson["addFlag"];
                }
                
                if (effJson.contains("removeFlag")) {
                    eff.removeFlag = effJson["removeFlag"];
                }
                
                if (effJson.contains("modifyStat")) {
                    for (auto& [key, val] : effJson["modifyStat"].items()) {
                        eff.modifyStats[key] = val;
                    }
                }
                
                if (effJson.contains("addItems") && effJson["addItems"].is_array()) {
                    for (const auto& itemJson : effJson["addItems"]) {
                        std::string itemId = itemJson.value("id", "");
                        int quantity = itemJson.value("quantity", 1);
                        if (!itemId.empty()) {
                            eff.addItems.push_back({itemId, quantity});
                        }
                    }
                }
                
                scene.effects = eff;
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