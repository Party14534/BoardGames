#include "handleEvents.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

bool keyDown;
sf::Keyboard::Key keyPressed;

void handleEvents(sf::RenderWindow& win, Game& game) {
    sf::Event event;
    sf::Vector2i dir;
    bool confirm = false;
    bool cancel = false;
    while(win.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                win.close();
                break;

            case sf::Event::KeyPressed:
                if (keyDown) break;
                keyDown = true;
                keyPressed = event.key.code; 
                switch (keyPressed) {
                    case sf::Keyboard::W:
                    case sf::Keyboard::Up:
                        dir.y = 1;
                        break;
                    case sf::Keyboard::S:
                    case sf::Keyboard::Down:
                        dir.y = -1;
                        break;
                    case sf::Keyboard::A:
                    case sf::Keyboard::Left:
                        dir.x = -1;
                        break;
                    case sf::Keyboard::D:
                    case sf::Keyboard::Right:
                        dir.x = 1;
                        break;
                    case sf::Keyboard::Z:
                        confirm = true;
                        break;
                    case sf::Keyboard::X:
                        cancel = true;
                        break;
                    default:
                        break;
                }
                break;

            case sf::Event::KeyReleased:
                if (keyDown && keyPressed == event.key.code) {
                    keyDown = false;
                }
                break;

            default:
                break;
        }
    }
    
    if (confirm) {
        game.Confirm();
        confirm = false;
    }
    else if (cancel) {
        game.Cancel();
        cancel = false;
    }
    else if (dir.x != 0 || dir.y != 0) {
        game.MoveCursor(dir);
    }
}
