#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
class Move {
    
};

class Game {
public:
    sf::RectangleShape cursor;
    int turn;

    virtual void Draw(sf::RenderWindow& win) = 0;
    virtual void PlayMove(Move* move) = 0;
    virtual void MoveCursor(sf::Vector2i dir) = 0;
    virtual void Confirm() = 0;
    virtual void Cancel() = 0;
};

#endif
