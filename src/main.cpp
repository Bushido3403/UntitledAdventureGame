// SFML 3.x

#include "GameEngine.h"

int main() {
    GameEngine engine;
    
    // Start with main menu - callbacks handled by engine
    engine.pushState(engine.createMainMenuState());
    
    engine.run();
    
    return 0;
}