#include "handleEvents.h"

void handleEvents(sf::RenderWindow& win) {
    sf::Event event;
    while(win.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                win.close();
                break;
            default:
                break;
        }
    }
}
