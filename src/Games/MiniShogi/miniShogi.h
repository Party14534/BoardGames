#ifndef MINISHOGI_H
#define MINISHOGI_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <optional>
#include <vector>
#include <iostream>

#include "../game.h"

#define PLAYER_1 true
#define PLAYER_2 false
#define SQUARE_SIZE 100.f

class MiniShogiPiece;

typedef std::vector<std::vector<MiniShogiPiece>> miniShogiBoard;

class MiniShogiMove : public Move {
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
    MiniShogiPiece(sf::Vector2u _pos, bool _side);
    void GetMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves);
};

class MiniShogiGame : public Game {
public:
    MiniShogiGame();
    void PlayMove(Move* move) override;
    void Draw(sf::RenderWindow& win) override;
    void MoveCursor(sf::Vector2i dir) override;
    void Confirm() override;
    void Cancel() override;

private:
    miniShogiBoard board;
    std::vector<std::vector<MiniShogiPiece>> capturedPieces;
    std::vector<sf::Vector2i> playerCursorPos;
    std::vector<MiniShogiMove> currentMoves;
    int capturedCursorIndex;
    int currentPlayer;
    bool inCaptured;
    bool choosingMove;

    void SetUpBoard();
    std::optional<MiniShogiMove> PosToMove();
    bool PosInMoves(sf::Vector2i pos);
};

class King : public MiniShogiPiece {
public:
    King(sf::Vector2u _pos, bool _side);
};

// PIECE MOVES
void GetKingMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece);

#endif
