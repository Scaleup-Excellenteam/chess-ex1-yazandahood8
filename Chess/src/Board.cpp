#include "Board.h"
#include <cctype>    
#include <memory>   

Board::Board() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            boardMove[i][j] = std::make_unique<Rook>(true, 0, 0);
}

Board::~Board() {}

void Board::loadFromString(const std::string& boardString) {
    if (boardString.size() != 64)
        return;

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
            int index = i * 8 + j;
            char symbol = boardString[index];

            boardMove[i][j] = nullptr;  

            char lower = std::tolower(symbol);
            bool turn = isupper(symbol); 

            switch (lower) {
                case 'r':
                    boardMove[i][j] = std::make_unique<Rook>(turn);
                    break;
                case 'k':
                    boardMove[i][j] = std::make_unique<King>(turn);
                    break;
                case 'b':
                    boardMove[i][j] = std::make_unique<Bishop>(turn);
                    break;
                case 'q':
                    boardMove[i][j] = std::make_unique<Queen>(turn);
                    break;
                case 'n':
                    boardMove[i][j] = std::make_unique<Knight>(turn);
                    break;
                case 'p':
                    boardMove[i][j] = std::make_unique<Pawn>(turn);
                    break;
                case '#':
                default:
                    boardMove[i][j] = nullptr;
                    break;
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
