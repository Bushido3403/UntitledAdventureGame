// SFML 3.x, 2.x is retarded so dont use it and

#include "GameEngine.h"

int main() {
    GameEngine engine;
    
    // Start with main menu - callbacks handled by engine
    engine.pushState(engine.createMainMenuState());
    
    engine.run();
    
    return 0;
}