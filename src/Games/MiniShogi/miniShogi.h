#ifndef MINISHOGI_H
#define MINISHOGI_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../game.h"

#define PLAYER_1 true
#define PLAYER_2 false
#define SQUARE_SIZE 100.f

class MiniShogiPiece;

typedef std::vector<std::vector<MiniShogiPiece>> miniShogiBoard;

class MiniShogiMove : Move {
public:
    sf::Vector2u start;
    sf::Vector2u end;

    MiniShogiMove(sf::Vector2u _start, sf::Vector2u _end);
};

class MiniShogiPiece {
public:
    char type = '\0';
    bool side;
    sf::Vector2u pos;

    MiniShogiPiece();
    MiniShogiPiece(bool _side);
    virtual void GetMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves);
};

class MiniShogiGame : public Game {
public:
    MiniShogiGame();
    void PlayMove(Move move) override;
    void Draw(sf::RenderWindow& win) override;

private:
    miniShogiBoard board;
    std::vector<MiniShogiPiece> p1_captured;
    std::vector<MiniShogiPiece> p2_captured;
    void SetUpBoard();
};

class King : public MiniShogiPiece {
public:
    King(bool _side);
    void GetMoves(miniShogiBoard& move, std::vector<MiniShogiMove>& moves) override;
};

#endif
