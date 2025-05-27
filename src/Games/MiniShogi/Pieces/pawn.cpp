#include "../miniShogi.h"

void GetPawnMoves(miniShogiBoard& board,
        std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece) {

    if (isupper(piece.type)) {
        GetGoldGeneralMoves(board, moves, piece);
        return;
    }

    bool onTop = false;
    int dir = 1;
    if (piece.side == PLAYER_1) {
        onTop = piece.pos.y == 4;
    } else {
        onTop = piece.pos.y == 0;
        dir = -1;
    }

    if (!onTop) {
        sf::Vector2i end = piece.pos;
        end.y += dir;

        if (board[end.x][end.y].type != '\0' &&
                board[end.x][end.y].side == piece.side) {
            return;
        }

        MiniShogiMove move(piece.pos, end, piece.side);
        moves.push_back(move);
    }
}
