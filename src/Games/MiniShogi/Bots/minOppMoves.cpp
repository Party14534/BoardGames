#include "../miniShogi.h"

MiniShogiMove MiniShogiGame::MinOppMoves() {
    miniShogiBoard b;
    bool side = turn % 2;
    MiniShogiMove finalMove({0,0}, {0,0}, side);
    int moveCount = INT32_MAX;

    for (auto& tuple : allMoves) {
        for (auto& move : tuple.second) {
            b = board;
            PlayMoveOnBoard(move, b);
            int count = GetCountOfMoves(b, !side);
            if (count < moveCount) {
                moveCount = count;
                finalMove.start = move.start;
                finalMove.end = move.end;
            }
        }
    }

    return finalMove;
}
