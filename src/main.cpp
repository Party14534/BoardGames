#include "main.h"

int main() {
    sf::RenderWindow win(sf::VideoMode::getDesktopMode(), "Board Games", sf::Style::Default);
    
    float deltaT;
    MiniShogiGame game;
        
    while(win.isOpen()) { if(framePassed(deltaT, 60.f, false)) {
        // Handle Events
        handleEvents(win);

        // Handle Input

        // Logic
        
        // Handle Rendering
        handleRendering(win, game);

    }}
}
