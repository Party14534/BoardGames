#include "../miniShogi.h"

void GetRookMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece) {
    // Up
    sf::Vector2i end = piece.pos;
    MiniShogiMove move(piece.pos, end, piece.side);
    while (true) {
        if (end.y == 4) break;
        
        end.y += 1;
        move.end = end;

        if (board[end.x][end.y].type != '\0') {
            if (board[end.x][end.y].side != piece.side) {
                moves.push_back(move);
            }
            break;
        }

        moves.push_back(move);
    }
    end = piece.pos;

    // Down
    while (true) {
        if (end.y == 0) break;
        
        end.y -= 1;
        move.end = end;

        if (board[end.x][end.y].type != '\0') {
            if (board[end.x][end.y].side != piece.side) {
                moves.push_back(move);
            }
            break;
        }

        moves.push_back(move);
    }
    end = piece.pos;

    // Left
    while (true) {
        if (end.x == 0) break;
        
        end.x -= 1;
        move.end = end;

        if (board[end.x][end.y].type != '\0') {
            if (board[end.x][end.y].side != piece.side) {
                moves.push_back(move);
            }
            break;
        }

        moves.push_back(move);
    }
    end = piece.pos;

    // Right
    while (true) {
        if (end.x == 4) break;
        
        end.x += 1;
        move.end = end;

        if (board[end.x][end.y].type != '\0') {
            if (board[end.x][end.y].side != piece.side) {
                moves.push_back(move);
            }
            break;
        }

        moves.push_back(move);
    }
    end = piece.pos;

    if (isupper(piece.type)) {
        GetKingMoves(board, moves, piece);
    }
}
