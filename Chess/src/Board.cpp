#include "Board.h"
#include <cctype>
#include <memory>
#include <limits>

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
                case 'r': boardMove[i][j] = std::make_unique<Rook>(isWhite, i, j); break;
                case 'k': boardMove[i][j] = std::make_unique<King>(isWhite, i, j); break;
                case 'b': boardMove[i][j] = std::make_unique<Bishop>(isWhite, i, j); break;
                case 'q': boardMove[i][j] = std::make_unique<Queen>(isWhite, i, j); break;
                case 'n': boardMove[i][j] = std::make_unique<Knight>(isWhite, i, j); break;
                case 'p': boardMove[i][j] = std::make_unique<Pawn>(isWhite, i, j); break;
                case '#':
                default: boardMove[i][j] = nullptr; break;
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

void Board::suggestBestMove(bool isWhiteTurn, int depth) {
    PriorityQueue<Move, MoveComparator> pq;

    for (int fr = 0; fr < 8; ++fr) {
        for (int fc = 0; fc < 8; ++fc) {
            Piece* piece = boardMove[fr][fc].get();
            if (!piece || piece->getColor() != isWhiteTurn) continue;

            for (int tr = 0; tr < 8; ++tr) {
                for (int tc = 0; tc < 8; ++tc) {
                    if (piece->isLegalMove(tr, tc, getRawBoard())) {
                        int score = 0;

                        Piece* target = boardMove[tr][tc].get();
                        if (target && target->getColor() != isWhiteTurn) {
                            score += 10;
                        }

                        if ((tr == 3 || tr == 4) && (tc == 3 || tc == 4))
                            score += 3;

                        int coverage = 0;
                        for (int nr = 0; nr < 8; ++nr) {
                            for (int nc = 0; nc < 8; ++nc) {
                                if (piece->isLegalMove(nr, nc, getRawBoard())) {
                                    coverage++;
                                }
                            }
                        }
                        score += coverage;

                        if ((piece->getPiece() == 'P' && tr == 7) || (piece->getPiece() == 'p' && tr == 0)) {
                            score += 20;  // Large bonus for pawn promotion
                        }

                        pq.push(Move(fr, fc, tr, tc, score));
                    }
                }
            }
        }
    }

    if (pq.isEmpty()) {
        throw NoLegalMovesException();
    }

    std::cout << "Top Suggested Moves:\n" << pq << std::endl;
}
