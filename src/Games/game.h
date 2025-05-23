#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
class Move {
    
};

class Game {
public:
    virtual void Draw(sf::RenderWindow& win) = 0;
    virtual void PlayMove(Move move) = 0;
};

#endif
