#include "Board.h"
#include <cctype>
#include <memory>

Board::Board() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            boardMove[i][j] = nullptr;
}

Board::~Board() {}

void Board::loadFromString(const std::string& boardString) {
    if (boardString.size() != 64)
        return;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int index = i * 8 + j;
            char symbol = boardString[index];

            boardMove[i][j] = nullptr;

            char lower = std::tolower(symbol);
            bool isWhite = std::isupper(symbol);

            switch (lower) {
                case 'r':
                    boardMove[i][j] = std::make_unique<Rook>(isWhite, i, j);
                    break;
                case 'k':
                    boardMove[i][j] = std::make_unique<King>(isWhite, i, j);
                    break;
                case 'b':
                    boardMove[i][j] = std::make_unique<Bishop>(isWhite, i, j);
                    break;
                case 'q':
                    boardMove[i][j] = std::make_unique<Queen>(isWhite, i, j);
                    break;
                case 'n':
                    boardMove[i][j] = std::make_unique<Knight>(isWhite, i, j);
                    break;
                case 'p':
                    boardMove[i][j] = std::make_unique<Pawn>(isWhite, i, j);
                    break;
                case '#':
                default:
                    boardMove[i][j] = nullptr;
                    break;
            }
        }
    }
}

std::string Board::getBoardString() const {
    std::string result;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            result += (boardMove[i][j] ? boardMove[i][j]->getPiece() : '#');
    return result;
}

Piece* const* const* Board::getRawBoard() const {
    static Piece* raw[8][8];
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            raw[i][j] = boardMove[i][j].get();
    return (Piece* const* const*)raw;
}
