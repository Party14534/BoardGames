#include "../miniShogi.h"

MiniShogiMove MiniShogiGame::MiniMax(int depth) {
    miniShogiBoard b;
    bool side = turn % 2;
    std::vector<MiniShogiMove> finalMoves;
    int bestScore = INT32_MIN;

    for (auto& tuple : allMoves) {
        for (auto& move : tuple.second) {
            b = board;
            PlayMoveOnBoard(move, b);
            int score = ScoreBoard(b, side);
            if (score > bestScore) {
                finalMoves.clear();
                finalMoves.push_back(MiniShogiMove(move.start, move.end, side));
                bestScore = score;
            } else if (score == bestScore) {
                finalMoves.push_back(MiniShogiMove(move.start, move.end, side));
            }
        }
    }

    return finalMoves[rand() % finalMoves.size()];
}
