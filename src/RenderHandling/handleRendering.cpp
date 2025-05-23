#include "handleRendering.h"

void handleRendering(sf::RenderWindow& win, Game& game) {
    win.clear(sf::Color(230,255,215));

    // Display objects
    game.Draw(win);

    win.display();
}
