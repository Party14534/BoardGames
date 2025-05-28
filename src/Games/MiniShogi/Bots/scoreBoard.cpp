#include "../miniShogi.h"

int MiniShogiGame::ScoreBoard(miniShogiBoard& board, bool side) {
    int pieceScores = 0;
    int enemyPieceScores = 0;
    int capturedScores = 0;
    int numEnemyMoves = GetCountOfMoves(board, !side);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j].type == '\0') {
                continue;
            } else if (board[i][j].side != side) {
                enemyPieceScores += GetPieceScore(board[i][j].type);
                continue;
            }
            pieceScores += GetPieceScore(board[i][j].type);
        }
    }
    for (auto& piece : capturedPieces[!side]) {
        capturedScores += GetPieceScore(piece.type);
    }

    int finalScore = pieceScores * 10;
    finalScore += capturedScores * 6;
    finalScore -= numEnemyMoves * 5;
    finalScore -= enemyPieceScores * 7;

    return finalScore;
}

int MiniShogiGame::GetPieceScore(char type) {
    switch (type) {
        case 'G':
        case 'S':
            return 6;
            break;
        case 'R':
            return 11;
            break;
        case 'B':
            return 10;
            break;
        case 'P':
            return 7;
            break;
        case 's':
            return 5;
            break;
        case 'r':
            return 9;
            break;
        case 'b':
            return 8;
            break;
        case 'p':
            return 1;
            break;
        default:
            return 0;
    }
}
