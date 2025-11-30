#include "PlayingStateUI.h"
#include "CustomWindow.h"
#include "SceneManager.h"
#include "ConfirmationDialog.h"

PlayingStateUI::PlayingStateUI(ResourceManager& resources)
    : resources(resources),
      dialogBox(std::make_unique<DialogBox>(resources.getFont("main"))),
      layoutManager(std::make_unique<LayoutManager>(sf::Vector2u(800, 600))),
      inventoryUI(std::make_unique<InventoryUI>(resources)),
      confirmationDialog(std::make_unique<ConfirmationDialog>(resources.getFont("main"))),
      windowSize(800, 600)
{
    background.setFillColor(sf::Color(20, 20, 30));
    
    dialogBoxShape.setFillColor(sf::Color(40, 40, 50, 220));
    dialogBoxShape.setOutlineColor(sf::Color(100, 100, 120));
    dialogBoxShape.setOutlineThickness(2.f);
    
    graphicsBox.setFillColor(sf::Color(30, 30, 40));
    graphicsBox.setOutlineColor(sf::Color(100, 100, 120));
    graphicsBox.setOutlineThickness(2.f);
    
    statsBox.setFillColor(sf::Color(40, 40, 50, 220));
    statsBox.setOutlineColor(sf::Color(100, 100, 120));
    statsBox.setOutlineThickness(2.f);
}

void PlayingStateUI::setInventorySystem(InventorySystem* inventory) {
    inventorySystem = inventory;
}

InventoryInteraction PlayingStateUI::handleInventoryEvent(const sf::Event& event) {
    if (inventorySystem && inventoryUI) {
        return inventoryUI->handleEvent(event, *inventorySystem);
    }
    return InventoryInteraction{};
}

void PlayingStateUI::updateInventory(const sf::Vector2i& mousePos) {
    if (inventorySystem && inventoryUI) {
        inventoryUI->update(mousePos, *inventorySystem);
    }
}

void PlayingStateUI::updatePositions(const sf::Vector2u& newWindowSize, const Scene* currentScene) {
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    windowSize = sf::Vector2u(newWindowSize.x, 
                              newWindowSize.y - static_cast<unsigned int>(TITLEBAR_HEIGHT));
    
    auto metrics = layoutManager->calculate(newWindowSize, TITLEBAR_HEIGHT);
    
    background.setSize(sf::Vector2f(static_cast<float>(newWindowSize.x), 
                                     static_cast<float>(newWindowSize.y) - TITLEBAR_HEIGHT));
    background.setPosition({0.f, TITLEBAR_HEIGHT});
    
    graphicsBox.setSize(metrics.graphicsBoxSize);
    graphicsBox.setPosition(metrics.graphicsBoxPos);
    
    statsBox.setSize(metrics.statsBoxSize);
    statsBox.setPosition(metrics.statsBoxPos);
    
    dialogBoxShape.setSize(metrics.dialogBoxSize);
    dialogBoxShape.setPosition(metrics.dialogBoxPos);
    
    unsigned int dialogSize = layoutManager->getScaledCharacterSize(24, windowSize);
    unsigned int speakerSize = layoutManager->getScaledCharacterSize(28, windowSize);
    
    sf::FloatRect dialogBounds(metrics.dialogBoxPos, metrics.dialogBoxSize);
    dialogBox->updateLayout(dialogBounds, metrics.scale.boxPadding, 
                           metrics.scale.scaleY, dialogSize, speakerSize);
    
    if (currentScene) {
        float maxTextWidth = metrics.dialogBoxSize.x - (metrics.scale.boxPadding * 2);
        std::string wrappedText = DialogBox::wrapText(currentScene->text, 
                                                      static_cast<unsigned int>(maxTextWidth), 
                                                      resources.getFont("main"), 
                                                      dialogSize);
        dialogBox->setText(wrappedText, currentScene->speaker, currentScene->speakerColor);
        dialogBox->updateLayout(dialogBounds, metrics.scale.boxPadding, 
                               metrics.scale.scaleY, dialogSize, speakerSize);
    }
    
    // Update inventory layout
    if (inventoryUI) {
        inventoryUI->updateLayout(
            sf::FloatRect(statsBox.getPosition(), statsBox.getSize()),
            metrics.scale.boxPadding,
            metrics.scale.scaleY
        );
    }

    // Update confirmation dialog position
    confirmationDialog->updatePosition(newWindowSize, TITLEBAR_HEIGHT);
}

void PlayingStateUI::updateChoiceButtons(const std::vector<std::unique_ptr<Button>>& buttons, const Scene* currentScene) {
    if (buttons.empty() || !currentScene) return;
    
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    sf::Vector2u fullWindowSize(windowSize.x, windowSize.y + static_cast<unsigned int>(TITLEBAR_HEIGHT));
    auto metrics = layoutManager->calculate(fullWindowSize, TITLEBAR_HEIGHT);
    
    unsigned int choiceSize = layoutManager->getScaledCharacterSize(22, windowSize);
    for (auto& button : buttons) {
        button->setTextSize(choiceSize);
    }
    
    updateChoicePositions(buttons, currentScene);
}

void PlayingStateUI::updateChoicePositions(const std::vector<std::unique_ptr<Button>>& buttons, const Scene* currentScene) {
    if (buttons.empty() || !currentScene) return;
    
    const float TITLEBAR_HEIGHT = CustomWindow::getTitlebarHeight();
    sf::Vector2u fullWindowSize(windowSize.x, windowSize.y + static_cast<unsigned int>(TITLEBAR_HEIGHT));
    auto metrics = layoutManager->calculate(fullWindowSize, TITLEBAR_HEIGHT);
    
    sf::FloatRect dialogBoxBounds = dialogBoxShape.getGlobalBounds();
    
    float baseChoiceSpacing = 35.f;
    float choiceSpacing = baseChoiceSpacing * metrics.scale.scaleY;
    
    size_t numChoices = buttons.size();
    bool useTwoColumns = numChoices > 2;
    
    float totalChoiceHeight;
    if (useTwoColumns) {
        size_t rows = (numChoices + 1) / 2;
        totalChoiceHeight = (rows - 1) * choiceSpacing;
        if (!buttons.empty()) {
            totalChoiceHeight += buttons[0]->getBounds().size.y;
        }
    } else {
        totalChoiceHeight = (numChoices - 1) * choiceSpacing;
        if (!buttons.empty()) {
            totalChoiceHeight += buttons[0]->getBounds().size.y;
        }
    }
    
    float dialogBoxBottom = dialogBoxBounds.position.y + dialogBoxBounds.size.y;
    float choiceStartY = dialogBoxBottom - totalChoiceHeight - metrics.scale.boxPadding;
    
    if (useTwoColumns) {
        float columnWidth = (metrics.dialogBoxSize.x - (metrics.scale.boxPadding * 3)) / 2.f;
        float leftColumnX = dialogBoxShape.getPosition().x + metrics.scale.boxPadding;
        float rightColumnX = leftColumnX + columnWidth + metrics.scale.boxPadding;
        
        for (size_t i = 0; i < buttons.size(); ++i) {
            size_t row = i / 2;
            bool isLeftColumn = (i % 2 == 0);
            
            float xPos = isLeftColumn ? leftColumnX : rightColumnX;
            float yPos = choiceStartY + row * choiceSpacing;
            buttons[i]->setPosition(sf::Vector2f(xPos, yPos));
        }
    } else {
        float xPos = dialogBoxShape.getPosition().x + metrics.scale.boxPadding;
        for (size_t i = 0; i < buttons.size(); ++i) {
            float yPos = choiceStartY + i * choiceSpacing;
            buttons[i]->setPosition(sf::Vector2f(xPos, yPos));
        }
    }
    
    sf::FloatRect dialogTextBounds = dialogBox->getTextBounds();
    float textBottomY = dialogTextBounds.position.y + dialogTextBounds.size.y;
    float baseTextToChoiceGap = 20.f;
    float textToChoiceGap = baseTextToChoiceGap * metrics.scale.scaleY;
    float requiredTextEndY = choiceStartY - textToChoiceGap;
    
    if (textBottomY > requiredTextEndY) {
        unsigned int currentSize = dialogBox->getDialogText().getCharacterSize();
        unsigned int minSize = static_cast<unsigned int>(12 * metrics.scale.minScale);
        
        while (currentSize > minSize && textBottomY > requiredTextEndY) {
            currentSize -= 1;
            
            float maxTextWidth = metrics.dialogBoxSize.x - (metrics.scale.boxPadding * 2);
            std::string wrappedText = DialogBox::wrapText(currentScene->text, 
                                                         static_cast<unsigned int>(maxTextWidth), 
                                                         resources.getFont("main"), 
                                                         currentSize);
            
            dialogBox->getDialogText().setCharacterSize(currentSize);
            dialogBox->getDialogText().setString(wrappedText);
            
            dialogTextBounds = dialogBox->getTextBounds();
            textBottomY = dialogTextBounds.position.y + dialogTextBounds.size.y;
        }
    }
}

void PlayingStateUI::draw(sf::RenderWindow& window, const std::vector<std::unique_ptr<Button>>& buttons, 
                         sf::Sprite* graphicsSprite) {
    window.draw(background);
    window.draw(graphicsBox);
    
    if (graphicsSprite) {
        sf::FloatRect texBounds = graphicsSprite->getLocalBounds();
        float graphicsWidth = graphicsBox.getSize().x;
        float graphicsHeight = graphicsBox.getSize().y;
        float scaleX = graphicsWidth / texBounds.size.x;
        float scaleY = graphicsHeight / texBounds.size.y;
        float scale = std::min(scaleX, scaleY);
        graphicsSprite->setScale(sf::Vector2f(scale, scale));
        
        sf::Vector2f spriteSize(texBounds.size.x * scale, texBounds.size.y * scale);
        sf::Vector2f boxPos = graphicsBox.getPosition();
        sf::Vector2f boxSize = graphicsBox.getSize();
        sf::Vector2f centeredPos(
            boxPos.x + (boxSize.x - spriteSize.x) / 2.f,
            boxPos.y + (boxSize.y - spriteSize.y) / 2.f
        );
        graphicsSprite->setPosition(centeredPos);
        
        window.draw(*graphicsSprite);
    }
    
    window.draw(statsBox);
    
    if (inventorySystem && inventoryUI) {
        inventoryUI->draw(window, *inventorySystem);
    }
    
    window.draw(dialogBoxShape);
    dialogBox->draw(window);
    
    for (auto& button : buttons) {
        button->draw(window);
    }
    
    // Draw confirmation dialog last (on top of everything)
    confirmationDialog->draw(window);
}