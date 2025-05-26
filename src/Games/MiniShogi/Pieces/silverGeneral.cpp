#include "../miniShogi.h"

void GetSilverGeneralMoves(miniShogiBoard& board,
        std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece) {
    if (isupper(piece.type)) {
        GetGoldGeneralMoves(board, moves, piece);
        return;
    }

    auto pos = piece.pos;
    bool side = piece.side;

    bool onLeft = pos.x == 0;
    bool onRight = pos.x == 4;
    bool onTop = pos.y == 4;
    bool onBottom = pos.y == 0;

    // Moves below
    if (!onBottom && piece.side == PLAYER_2) {
        if (board[pos.x][pos.y - 1].type == '\0' || board[pos.x][pos.y - 1].side != side) {
            moves.push_back(MiniShogiMove(pos, { pos.x, pos.y - 1 }));
        }

        if (!onLeft && (board[pos.x - 1][pos.y - 1].type == '\0' || board[pos.x - 1][pos.y - 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x - 1, pos.y - 1 }));
        }
        if (!onRight && (board[pos.x + 1][pos.y - 1].type == '\0' || board[pos.x + 1][pos.y - 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x + 1, pos.y - 1 }));
        }
    } else if (!onBottom) {
        if (!onLeft && (board[pos.x - 1][pos.y - 1].type == '\0' || board[pos.x - 1][pos.y - 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x - 1, pos.y - 1 }));
        }
        if (!onRight && (board[pos.x + 1][pos.y - 1].type == '\0' || board[pos.x + 1][pos.y - 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x + 1, pos.y - 1 }));
        }
    }

    // Moves above
    if (!onTop && piece.side == PLAYER_1) {
        if (board[pos.x][pos.y + 1].type == '\0' || board[pos.x][pos.y + 1].side != side) {
            moves.push_back(MiniShogiMove(pos, { pos.x, pos.y + 1 }));
        }
        if (!onLeft && (board[pos.x - 1][pos.y + 1].type == '\0' || board[pos.x - 1][pos.y + 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x - 1, pos.y + 1 }));
        }
        if (!onRight && (board[pos.x + 1][pos.y + 1].type == '\0' || board[pos.x + 1][pos.y + 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x + 1, pos.y + 1 }));
        }
    } else if (!onTop) {
        if (!onLeft && (board[pos.x - 1][pos.y + 1].type == '\0' || board[pos.x - 1][pos.y + 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x - 1, pos.y + 1 }));
        }
        if (!onRight && (board[pos.x + 1][pos.y + 1].type == '\0' || board[pos.x + 1][pos.y + 1].side != side)) {
            moves.push_back(MiniShogiMove(pos, { pos.x + 1, pos.y + 1 }));
        }
    }
}
