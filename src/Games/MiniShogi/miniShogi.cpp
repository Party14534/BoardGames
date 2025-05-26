#include "miniShogi.h"
#include <algorithm>

/*
 * GAME LOGIC
 * */

MiniShogiGame::MiniShogiGame() {
    board = std::vector<std::vector<MiniShogiPiece>>(5, std::vector<MiniShogiPiece>(5));
    capturedPieces = std::vector<std::vector<MiniShogiPiece>>(2, std::vector<MiniShogiPiece>());


    playerCursorPos = std::vector<sf::Vector2i>(2);
    playerCursorPos[0] = {0, 0};
    playerCursorPos[1] = {4, 4};
    turn = 1;
    currentPlayer = 0;
    inCaptured = false;

    SetUpBoard();
    GetAllMoves(board, PLAYER_1);

    cursor.setSize({SQUARE_SIZE - 1, SQUARE_SIZE - 1});
    cursor.setOrigin({SQUARE_SIZE / 2 + 2.5f, SQUARE_SIZE / 2 + 2.5f});
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineThickness(10.f);
    cursor.setOutlineColor(sf::Color::Cyan);
}

void MiniShogiGame::SetUpBoard() {
    board[0][0] = King({0, 0}, PLAYER_1);
    board[4][4] = King({4, 4}, PLAYER_2);

    board[1][0] = GoldGeneral({1, 0}, PLAYER_1);
    board[3][4] = GoldGeneral({3, 4}, PLAYER_2);

    board[2][0] = SilverGeneral({2, 0}, PLAYER_1);
    board[2][4] = SilverGeneral({2, 4}, PLAYER_2);

    board[3][0] = Bishop({3, 0}, PLAYER_1);
    board[1][4] = Bishop({1, 4}, PLAYER_2);
    
    board[4][0] = Rook({4, 0}, PLAYER_1);
    board[0][4] = Rook({0, 4}, PLAYER_2);

    board[0][1] = Pawn({0, 1}, PLAYER_1);
    board[4][3] = Pawn({4, 3}, PLAYER_2);
}

void MiniShogiGame::Draw(sf::RenderWindow& win) {
    // Draw board 
    // Speed up by drawing board to texture
    sf::RectangleShape tile; 
    tile.setSize({SQUARE_SIZE, SQUARE_SIZE});
    tile.setOrigin({SQUARE_SIZE / 2, SQUARE_SIZE / 2});
    tile.setOutlineThickness(5.f);
    tile.setOutlineColor(sf::Color::Black);
    sf::Font font;
    if (!font.loadFromFile("./src/res/ARIAL.TTF")) {
        std::cout << "faild to load font\n";
        exit(1);
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(48);
    text.setOrigin(24, 24);

    sf::Vector2f offset = { win.getSize().x / 2 - (SQUARE_SIZE * 2.5f),
                            win.getSize().y / 2 - (SQUARE_SIZE * 2.5f)};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tile.setPosition({ float(i * (SQUARE_SIZE) + SQUARE_SIZE / 2),
                    float(-1.f * j * (SQUARE_SIZE) + SQUARE_SIZE / 2) });
            tile.move(offset);

            if (choosingMove && PosInMoves({i, j})) {
                tile.setFillColor(sf::Color(0xA59657FF));
            } else {
                tile.setFillColor(sf::Color(0xF5C687FF));
            }

            win.draw(tile);

            if (i == playerCursorPos[currentPlayer].x && j == playerCursorPos[currentPlayer].y) {
                cursor.setPosition({tile.getPosition().x, tile.getPosition().y + 5.f});
            }

            if (board[i][j].type == '\0') continue;

            text.setString(board[i][j].type);
            sf::Color pieceColor = (board[i][j].side) ? sf::Color::Blue : sf::Color::Red;
            text.setFillColor(pieceColor);

            sf::FloatRect rect = text.getLocalBounds();
            text.setOrigin(rect.left + rect.width/2.f,
                    rect.top + rect.height / 2.f);
            text.setPosition(tile.getPosition());
            win.draw(text);
        }
    }

    win.draw(cursor);
}

void MiniShogiGame::PlayMove(Move* move) {
    MiniShogiMove* minimove = (MiniShogiMove*)move;

    sf::Vector2u start = minimove->start;
    sf::Vector2u end = minimove->end;
    MiniShogiPiece piece = board[start.x][start.y];
    board[start.x][start.y].type = '\0';
    
    if (board[end.x][end.y].type != '\0') {
        capturedPieces[currentPlayer].push_back(board[end.x][end.y]);
    }

    piece.pos = end;

    // Promote piece
    if (piece.side == PLAYER_1 && end.y == 4) {
        piece.type = toupper(piece.type);
    }
    else if (piece.side == PLAYER_2 && end.y == 0) {
        piece.type = toupper(piece.type);
    }

    board[end.x][end.y] = piece;
    turn++;
    currentPlayer = !currentPlayer;
    choosingMove = false;
    currentMoves.clear();
    allMoves.clear(); 

    int moveCount = GetAllMoves(board, turn % 2);
    if (moveCount == 0) {
        std::string player = (turn % 2) ? "Red" : "Blue";
        std::cout << player << " player wins!\n";
        exit(0);
    }

    if (turn % 2 == 0) {
        MiniShogiMove move = MinOppMoves();
        PlayMove(&move);
    }
}

int MiniShogiGame::GetAllMoves(miniShogiBoard& board, bool side) {
    int moveCount = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j].type == '\0' || board[i][j].side != side) {
                continue;
            }

            std::vector<MiniShogiMove> moves;
            board[i][j].GetMoves(board, moves);
            CullInvalidMoves(moves);
            if (moves.size() == 0) continue;
            allMoves[{i, j}] = moves;
            moveCount += moves.size();
        }
    }

    return moveCount;
}

int MiniShogiGame::GetCountOfMoves(miniShogiBoard& board, bool side) {
    int moveCount = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j].type == '\0' || board[i][j].side != side) {
                continue;
            }

            std::vector<MiniShogiMove> moves;
            board[i][j].GetMoves(board, moves);
            CullInvalidMoves(moves);
            if (moves.size() == 0) continue;
            moveCount += moves.size();
        }
    }

    return moveCount;
}

void MiniShogiGame::MoveCursor(sf::Vector2i dir) {
    sf::Vector2i index = playerCursorPos[currentPlayer];

    if (inCaptured) {
        if (dir.x) { 
            if (!currentPlayer && dir.x == -1) {
                inCaptured = false;
                playerCursorPos[currentPlayer].x = 4;
            }
            else if (currentPlayer && dir.x == 1) {
                inCaptured = false;
                playerCursorPos[currentPlayer].x = 0;
            }
        }

        capturedCursorIndex += dir.y;
        int yMax = (currentPlayer) ? capturedPieces[currentPlayer].size()
            : capturedPieces[currentPlayer].size();
        capturedCursorIndex = std::clamp(capturedCursorIndex, 0, yMax);
        return;
    }
    
    index += dir;
    index.y = std::clamp(index.y, 0, 4);

    if (currentPlayer == 0) {
        index.x = std::clamp(index.x, 0, 5);
        if (index.x == 5) {
            inCaptured = true;    
            capturedCursorIndex = 0;
        }
    } else {
        index.x = std::clamp(index.x, -1, 4);
        if (index.x == -1) {
            inCaptured = true;    
            capturedCursorIndex = 0;
        }
    }
    
    playerCursorPos[currentPlayer] = index;
}

void MiniShogiGame::Confirm() {
    // Not inCaptured for now
    if (!choosingMove && !inCaptured) {
        sf::Vector2i cursorPos = playerCursorPos[currentPlayer];
        MiniShogiPiece currentPiece = board[cursorPos.x][cursorPos.y];
        
        bool currentSide = turn % 2;
        if (currentPiece.side != currentSide && currentPiece.type != '\0') {
            return;
        }

        currentMoves.clear();
        currentMoves = allMoves[cursorPos];
        choosingMove = true;
    } else if (choosingMove) {
        auto move = PosToMove();

        if (!move.has_value()) {
            Cancel();
            return;
        }

        PlayMove(&move.value());
    }
}

void MiniShogiGame::Cancel() {
    if (choosingMove) {
        choosingMove = false;
    }
}

std::optional<MiniShogiMove> MiniShogiGame::PosToMove() {
    for (auto& move : currentMoves) {
        if (move.end.x == playerCursorPos[currentPlayer].x &&
                move.end.y == playerCursorPos[currentPlayer].y) {
            return move;
        }
    }

    return std::nullopt;
}

bool MiniShogiGame::PosInMoves(sf::Vector2i pos) {
    for (auto& move : currentMoves) {
        if (move.end.x == pos.x && move.end.y == pos.y) return true;
    }

    return false;
}

bool MiniShogiGame::PieceIsPromotable(char type) {
    return !isupper(type);
}

void MiniShogiGame::CullInvalidMoves(std::vector<MiniShogiMove>& moves) {
    miniShogiBoard b;

    for (auto& move : moves) {
        b = board;
        PlayMoveOnBoard(move, b);
        move.invalid = IsKingExposed(turn % 2, b);
    }

    moves.erase(std::remove_if(moves.begin(), moves.end(), 
                [](const MiniShogiMove& move) {
                return move.invalid;
                }), moves.end());
}

bool MiniShogiGame::IsKingExposed(bool side, miniShogiBoard& board) {
    std::vector<MiniShogiMove> moves;
    sf::Vector2u kingPos;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j].type == '\0' || board[i][j].side == side) {
                if (board[i][j].type == 'K') { kingPos = board[i][j].pos; }
                continue;
            }
            
            board[i][j].GetMoves(board, moves);
        }
    }

    for (auto& move : moves) {
        if (move.end.x == kingPos.x && move.end.y == kingPos.y) {
            return true;
        }
    }
    return false;
}

void MiniShogiGame::PlayMoveOnBoard(MiniShogiMove& move, miniShogiBoard& board) {
    sf::Vector2u start = move.start;
    sf::Vector2u end = move.end;
    MiniShogiPiece piece = board[start.x][start.y];
    board[start.x][start.y].type = '\0';
    
    piece.pos = end;

    // Promote piece
    if (piece.side == PLAYER_1 && end.y == 4) {
        piece.type = toupper(piece.type);
    }
    else if (piece.side == PLAYER_2 && end.y == 0) {
        piece.type = toupper(piece.type);
    }

    board[end.x][end.y] = piece;
}


/*
 * MINISHOGI PIECE CODE
 * */

MiniShogiPiece::MiniShogiPiece() { side = PLAYER_1; }
MiniShogiPiece::MiniShogiPiece(sf::Vector2u _pos, bool _side) : pos(_pos), side(_side) {}

void MiniShogiPiece::GetMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves) {
    switch (toupper(type)) {
        case 'K':
            GetKingMoves(board, moves, *this);
            break;
        case 'G':
            GetGoldGeneralMoves(board, moves, *this);
            break;
        case 'S':
            GetSilverGeneralMoves(board, moves, *this);
            break;
        case 'B':
            GetBishopMoves(board, moves, *this);
            break;
        case 'R':
            GetRookMoves(board, moves, *this);
            break;
        case 'P':
            GetPawnMoves(board, moves, *this);
            break;
        default:
            break;
    }
}

MiniShogiMove::MiniShogiMove(sf::Vector2u _start, sf::Vector2u _end) : start(_start), end(_end) {}

/*
 * PIECE DEFINITIONS
 */

King::King(sf::Vector2u _pos, bool _side) { 
    type = 'K';
    side = _side; 
    pos = _pos;
}

GoldGeneral::GoldGeneral(sf::Vector2u _pos, bool _side) {
    type = 'G';
    side = _side;
    pos = _pos;
}

SilverGeneral::SilverGeneral(sf::Vector2u _pos, bool _side) {
    type = 's';
    side = _side;
    pos = _pos;
}

Bishop::Bishop(sf::Vector2u _pos, bool _side) { 
    type = 'b';
    side = _side; 
    pos = _pos;
}

Rook::Rook(sf::Vector2u _pos, bool _side) { 

    type = 'r';
    side = _side; 
    pos = _pos;
}

Pawn::Pawn(sf::Vector2u _pos, bool _side) { 
    type = 'p';
    side = _side; 
    pos = _pos;
}

