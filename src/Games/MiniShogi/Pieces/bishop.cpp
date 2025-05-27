#include "../miniShogi.h"

void GetBishopMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves, MiniShogiPiece& piece) {
    // Up-Left
    sf::Vector2i end = piece.pos;
    MiniShogiMove move(piece.pos, end, piece.side);
    while (true) {
        if (end.x == 0 || end.y == 4) break;
        
        end.x -= 1;
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

    // Up-Right
    while (true) {
        if (end.x == 4 || end.y == 4) break;
        
        end.x += 1;
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
    
    // Down-Left
    while (true) {
        if (end.x == 0 || end.y == 0) break;
        
        end.x -= 1;
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

    // Down-Right
    while (true) {
        if (end.x == 4 || end.y == 0) break;
        
        end.x += 1;
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

    if (isupper(piece.type)) {
        GetKingMoves(board, moves, piece);
    }
}
