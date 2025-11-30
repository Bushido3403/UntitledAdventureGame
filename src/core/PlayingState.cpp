#include "PlayingState.h"
#include "CustomWindow.h"

PlayingState::PlayingState(ResourceManager& resources, const std::string& scriptPath)
    : resources(resources),
      sceneManager(std::make_unique<SceneManager>(resources)),
      ui(std::make_unique<PlayingStateUI>(resources)),
      gameState(std::make_unique<GameStateManager>())
{
    transitionOverlay.setFillColor(sf::Color(0, 0, 0, 255));
    transitionOverlay.setSize(sf::Vector2f(800.f, 600.f));
    
    if (sceneManager->loadScript(scriptPath)) {
        gameState->loadGame();
        loadScene(sceneManager->getScript().scenes[0].id);
    }
    
    transitionState = TransitionState::FadingIn;
    transitionAlpha = 255.f;
}

void PlayingState::setOnScriptComplete(std::function<void()> callback) {
    onScriptComplete = callback;
    sceneManager->setOnScriptComplete(callback);
}

void PlayingState::loadScene(const std::string& sceneId) {
    if (!sceneManager->loadScene(sceneId)) {
        return;
    }
    
    const Scene* currentScene = sceneManager->getCurrentScene();
    if (!currentScene) return;
    
    if (currentScene->effects.has_value()) {
        gameState->applyEffects(currentScene->effects.value());
        gameState->saveGame(sceneManager->getScript().scriptId, currentScene->id);
    }
    
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    sf::Vector2u fullWindowSize(ui->getWindowSize().x, 
                                ui->getWindowSize().y + static_cast<unsigned int>(TITLEBAR_HEIGHT));
    
    LayoutManager tempLayoutManager(sf::Vector2u(800, 600));
    auto metrics = tempLayoutManager.calculate(fullWindowSize, TITLEBAR_HEIGHT);
    unsigned int dialogSize = tempLayoutManager.getScaledCharacterSize(24, ui->getWindowSize());
    
    float maxTextWidth = metrics.dialogBoxSize.x - (metrics.scale.boxPadding * 2);
    std::string wrappedText = DialogBox::wrapText(currentScene->text, 
                                                  static_cast<unsigned int>(maxTextWidth), 
                                                  resources.getFont("main"), 
                                                  dialogSize);
    
    ui->getDialogBox().setText(wrappedText, currentScene->speaker, currentScene->speakerColor);
    
    createChoiceButtons();
    updatePositions(fullWindowSize);
}

void PlayingState::startTransition(const std::string& sceneId) {
    if (transitionState != TransitionState::None) {
        return;
    }
    
    nextSceneId = sceneId;
    transitionState = TransitionState::FadingOut;
    transitionAlpha = 0.f;
}

void PlayingState::updateTransition(float deltaTime) {
    if (transitionState == TransitionState::None) {
        return;
    }
    
    float alphaSpeed = 255.f / transitionDuration;
    
    if (transitionState == TransitionState::FadingOut) {
        transitionAlpha += alphaSpeed * deltaTime;
        
        if (transitionAlpha >= 255.f) {
            transitionAlpha = 255.f;
            
            std::string sceneToLoad = nextSceneId;
            nextSceneId.clear();
            
            if (sceneToLoad == "END") {
                if (onScriptComplete) {
                    onScriptComplete();
                }
                return;
            }
            
            loadScene(sceneToLoad);
            transitionState = TransitionState::FadingIn;
        }
    }
    else if (transitionState == TransitionState::FadingIn) {
        transitionAlpha -= alphaSpeed * deltaTime;
        
        if (transitionAlpha <= 0.f) {
            transitionAlpha = 0.f;
            transitionState = TransitionState::None;
        }
    }
    
    sf::Color overlayColor = transitionOverlay.getFillColor();
    overlayColor.a = static_cast<std::uint8_t>(std::clamp(transitionAlpha, 0.f, 255.f));
    transitionOverlay.setFillColor(overlayColor);
}

void PlayingState::createChoiceButtons() {
    choiceButtons.clear();
    
    const Scene* currentScene = sceneManager->getCurrentScene();
    if (!currentScene) return;
    
    const char labels[] = {'a', 'b', 'c', 'd'};
    size_t labelIndex = 0;
    
    for (size_t i = 0; i < currentScene->choices.size() && labelIndex < 4; ++i) {
        const auto& choice = currentScene->choices[i];
        
        if (choice.condition.has_value() && !gameState->checkCondition(choice.condition.value())) {
            continue;
        }
        
        auto button = std::make_unique<Button>(resources, nullptr, sf::Vector2f(0, 0));
        button->setText(std::string(1, labels[labelIndex]) + ") " + choice.text, 
                       resources.getFont("main"), 22);
        
        std::string nextScene = choice.nextScene;
        std::string nextScript = choice.nextScript;
        
        button->setOnClick([this, nextScene, nextScript]() {
            if (!nextScript.empty()) {
                sceneManager->loadScript(nextScript);
                if (!sceneManager->getScript().scenes.empty()) {
                    startTransition(sceneManager->getScript().scenes[0].id);
                }
            } else {
                startTransition(nextScene);
            }
        });
        
        choiceButtons.push_back(std::move(button));
        labelIndex++;
    }
}

void PlayingState::updatePositions(const sf::Vector2u& newWindowSize) {
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    
    transitionOverlay.setSize(sf::Vector2f(static_cast<float>(newWindowSize.x), 
                                           static_cast<float>(newWindowSize.y) - TITLEBAR_HEIGHT));
    transitionOverlay.setPosition({0.f, TITLEBAR_HEIGHT});
    
    const Scene* currentScene = sceneManager->getCurrentScene();
    ui->updatePositions(newWindowSize, currentScene);
    ui->updateChoiceButtons(choiceButtons, currentScene);
}

void PlayingState::handleEvent(const sf::Event& event) {
    if (transitionState != TransitionState::None) {
        return;
    }
    
    for (auto& button : choiceButtons) {
        button->handleEvent(event);
    }
    
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        int choiceIndex = -1;
        
        switch (keyPressed->code) {
            case sf::Keyboard::Key::A: choiceIndex = 0; break;
            case sf::Keyboard::Key::B: choiceIndex = 1; break;
            case sf::Keyboard::Key::C: choiceIndex = 2; break;
            case sf::Keyboard::Key::D: choiceIndex = 3; break;
            default: break;
        }
        
        const Scene* currentScene = sceneManager->getCurrentScene();
        if (currentScene && choiceIndex >= 0 && 
            choiceIndex < static_cast<int>(currentScene->choices.size())) {
            const auto& choice = currentScene->choices[choiceIndex];
            if (!choice.nextScript.empty()) {
                sceneManager->loadScript(choice.nextScript);
                if (!sceneManager->getScript().scenes.empty()) {
                    startTransition(sceneManager->getScript().scenes[0].id);
                }
            } else {
                startTransition(choice.nextScene);
            }
        }
    }
}

void PlayingState::update(float deltaTime, sf::RenderWindow& window) {
    updateTransition(deltaTime);
    
    if (transitionState == TransitionState::None) {
        auto mousePos = sf::Mouse::getPosition(window);
        
        for (auto& button : choiceButtons) {
            button->update(mousePos);
        }
    }
}

void PlayingState::draw(sf::RenderWindow& window) {
    auto& graphicsSprite = sceneManager->getGraphicsSprite();
    ui->draw(window, choiceButtons, graphicsSprite.get());
    
    if (transitionState != TransitionState::None) {
        window.draw(transitionOverlay);
    }
}