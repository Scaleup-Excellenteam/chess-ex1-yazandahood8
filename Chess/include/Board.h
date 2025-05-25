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
#include "PriorityQueue.h"
#include "Exception.h"
#include <vector>
struct Move {
    int fromRow, fromCol, toRow, toCol, score;
    Move(int fr, int fc, int tr, int tc, int s)
        : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc), score(s) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Move& m) {
        os << static_cast<char>('a' + m.fromRow) << (m.fromCol + 1)
           << " -> " << static_cast<char>('a' + m.toRow) << (m.toCol + 1)
           << " [Score: " << m.score << "]";
        return os;
    }
};

struct MoveComparator {
    int operator()(const Move& a, const Move& b) const {
        return a.score - b.score;
    }
};
class Board {
public:
    Board();
    ~Board();
    void suggestBestMove(bool isWhiteTurn, int depth);

    void loadFromString(const std::string& boardString);
    std::string getBoardString() const;

    Piece* const* const* getRawBoard() const;

    std::unique_ptr<Piece> boardMove[8][8];

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
};
