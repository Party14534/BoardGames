#include "../miniShogi.h"

MiniShogiMove MiniShogiGame::MinOppMoves() {
    miniShogiBoard b;
    MiniShogiMove finalMove({0,0}, {0,0});
    int moveCount = INT32_MAX;
    bool side = turn % 2;

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
