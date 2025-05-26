#include "../miniShogi.h"

void GetKingMoves(miniShogiBoard& board, 
        std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece) {
    auto pos = piece.pos;
    bool side = piece.side;

    bool onLeft = pos.x == 0;
    bool onRight = pos.x == 4;
    bool onTop = pos.y == 0;
    bool onBottom = pos.y == 4;

    if (!onLeft && (board[pos.x - 1][pos.y].type == '\0' || board[pos.x - 1][pos.y].side != side)) {
        moves.push_back(MiniShogiMove(pos, { pos.x - 1, pos.y }));
    }
    if (!onRight && (board[pos.x + 1][pos.y].type == '\0' || board[pos.x + 1][pos.y].side != side)) {
        moves.push_back(MiniShogiMove(pos, { pos.x + 1, pos.y }));
    }

    // Moves above
    if (!onTop) {
        if (board[pos.x][pos.y - 1].type == '\0' || board[pos.x][pos.y - 1].side != side) {
            moves.push_back(MiniShogiMove(pos, { pos.x, pos.y - 1 }));
        }
        if (!onLeft && (board[pos.x - 1][pos.y - 1].type == '\0' || board[pos.x - 1][pos.y - 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x - 1, pos.y - 1 }));
        }
        if (!onRight && (board[pos.x + 1][pos.y - 1].type == '\0' || board[pos.x + 1][pos.y - 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x + 1, pos.y - 1 }));
        }
    }

    // Moves below
    if (!onBottom) {
        if (board[pos.x][pos.y + 1].type == '\0' || board[pos.x][pos.y + 1].side != side) {
            moves.push_back(MiniShogiMove(pos, { pos.x, pos.y + 1 }));
        }
        if (!onLeft && (board[pos.x - 1][pos.y + 1].type == '\0' || board[pos.x - 1][pos.y + 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x - 1, pos.y + 1 }));
        }
        if (!onRight && (board[pos.x + 1][pos.y + 1].type == '\0' || board[pos.x + 1][pos.y + 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x + 1, pos.y + 1 }));
        }
    }
}
