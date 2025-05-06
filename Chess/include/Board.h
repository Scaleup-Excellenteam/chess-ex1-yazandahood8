#pragma once

#include <memory>
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

#include <string>

class Board {
public:
    Board();
    ~Board();

    void loadFromString(const std::string& boardString);
    std::string getBoardString() const;

    Piece* const* const* getRawBoard() const;

    std::unique_ptr<Piece> boardMove[8][8];

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};
