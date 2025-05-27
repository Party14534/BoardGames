#ifndef MINISHOGI_H
#define MINISHOGI_H
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>
#include <optional>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstdint>

#include "../game.h"
#include "../../Internal/hashFunction.h"

#define PLAYER_1 true
#define PLAYER_2 false
#define SQUARE_SIZE 100.f

class MiniShogiPiece;

typedef std::vector<std::vector<MiniShogiPiece>> miniShogiBoard;

class MiniShogiMove : public Move {
public:
    sf::Vector2i start;
    sf::Vector2i end;
    bool side;
    bool invalid = false;

    MiniShogiMove(sf::Vector2i _start, sf::Vector2i _end, bool _side);
};

class MiniShogiPiece {
public:
    char type = '\0';
    bool side;
    sf::Vector2i pos;

    MiniShogiPiece();
    MiniShogiPiece(sf::Vector2i _pos, bool _side);
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
    std::unordered_map<sf::Vector2i, std::vector<MiniShogiMove>, Vector2iHash> allMoves;
    int capturedCursorIndex;
    int currentPlayer;
    bool inCaptured;
    bool choosingMove;

    void SetUpBoard();
    int GetAllMoves(miniShogiBoard& board, bool side);
    int GetCountOfMoves(miniShogiBoard& board, bool side);
    std::optional<MiniShogiMove> PosToMove();
    bool PosInMoves(sf::Vector2i pos);
    bool PieceIsPromotable(char type);
    void CullInvalidMoves(std::vector<MiniShogiMove>& moves);
    bool IsKingExposed(bool side, miniShogiBoard& board);
    std::vector<std::vector<bool>> GetAttackingBitmask(bool side);
    void copyMiniShogiBoard(miniShogiBoard& board, miniShogiBoard& src);
    void PlayMoveOnBoard(MiniShogiMove& move, miniShogiBoard& board);

    // AIs
    MiniShogiMove MinOppMoves();
};

class King : public MiniShogiPiece {
public:
    King(sf::Vector2i _pos, bool _side);
};

class GoldGeneral : public MiniShogiPiece {
public:
    GoldGeneral(sf::Vector2i _pos, bool _side);
};

class SilverGeneral : public MiniShogiPiece {
public:
    SilverGeneral(sf::Vector2i _pos, bool _side);
};

class Bishop : public MiniShogiPiece {
public:
    Bishop(sf::Vector2i _pos, bool _side);
};

class Rook : public MiniShogiPiece {
public:
    Rook(sf::Vector2i _pos, bool _side);
};

class Pawn : public MiniShogiPiece {
public:
    Pawn(sf::Vector2i _pos, bool _side);
};

// PIECE MOVES
void GetKingMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece);

void GetGoldGeneralMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece);

void GetSilverGeneralMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece);

void GetBishopMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece);

void GetRookMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece);

void GetPawnMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece);

#endif
