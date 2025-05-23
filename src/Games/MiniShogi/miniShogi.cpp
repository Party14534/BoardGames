#include "miniShogi.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

/*
 * GAME LOGIC
 * */

MiniShogiGame::MiniShogiGame() {
    board = std::vector<std::vector<MiniShogiPiece>>(5, std::vector<MiniShogiPiece>(5));

    board[0][0] = King(PLAYER_1);
    board[4][4] = King(PLAYER_2);
}

void MiniShogiGame::Draw(sf::RenderWindow& win) {
    // Draw board
    sf::RectangleShape tile; 
    tile.setSize({SQUARE_SIZE, SQUARE_SIZE});
    tile.setOrigin({SQUARE_SIZE / 2, SQUARE_SIZE / 2});
    tile.setFillColor(sf::Color(0xF5C687FF));
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
            win.draw(tile);

            if (board[i][j].type == '\0') continue;

            text.setString(board[i][j].type);
            text.setPosition(tile.getPosition());
            sf::Color pieceColor = (board[i][j].side) ? sf::Color::Blue : sf::Color::Red;
            text.setFillColor(pieceColor);
            win.draw(text);
        }
    }
}

void MiniShogiGame::PlayMove(Move move) {
    
}

MiniShogiPiece::MiniShogiPiece() { side = PLAYER_1; }
MiniShogiPiece::MiniShogiPiece(bool _side) : side(_side) {}

void MiniShogiPiece::GetMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves) {}

MiniShogiMove::MiniShogiMove(sf::Vector2u _start, sf::Vector2u _end) : start(_start), end(_end) {}

/*
 * PIECE DEFINITIONS
 */

King::King(bool _side) { 
    type = 'K';
    side = _side; 
}

void King::GetMoves(miniShogiBoard& board, std::vector<MiniShogiMove>& moves) {
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
