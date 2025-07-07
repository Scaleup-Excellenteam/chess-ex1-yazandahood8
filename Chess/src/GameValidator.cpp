#include "GameValidator.h"
#include "Board.h"
#include "Piece.h"
#include "Helper.h"
#include <iostream>

// Validates a chess move string on the current board.
// Parameters:
//   move      - the move to validate (e.g., "e2e4")
//   board     - reference to the board state string (may be updated)
//   isTurn    - true if it's White's turn, false for Black
//   Simulate  - if true, only simulates the move; if false, may prompt for promotion
// Returns:
//   42 for valid move; other codes for specific error cases
int validateMove(const std::string& move, std::string& board, bool isTurn, bool Simulate) {
    // Convert move notation to board indices
    int ch='a';
    int num='1';
    int RowSource = move[0] - ch;
    int ColSource = move[1] - num;
    int RowDestination = move[2] - ch;
    int ColDestination = move[3] - num;

    Board board2;
    board2.loadFromString(board);

    // Check if source square has a piece
    Piece* srcPiece = board2.boardMove[RowSource][ColSource];
    bool isWhite = srcPiece->getColor();
    if (isWhite != isTurn)
        return 12; // Wrong player's turn
    if (srcPiece == nullptr)
        return 11; // No piece at source


    // Cannot capture own piece
    Piece* destentionP = board2.boardMove[RowDestination][ColDestination];
    // Check piece-specific movement legality
    if (!srcPiece->CheckLegalMove(RowSource, ColSource, RowDestination, ColDestination, board2.boardMove))
        return 21; // Illegal movement pattern
    if (destentionP && destentionP->getColor() == srcPiece->getColor())
        return 13; // Cannot capture own piece

    // Make the move temporarily (simulate)
    Piece* cap = destentionP;
    board2.boardMove[RowDestination][ColDestination] = srcPiece;
    board2.boardMove[RowSource][ColSource] = nullptr;

    // Find king's position for check validation
    int kingRow = -1, kingCol = -1;
    for (int r = 0; r < 8 && kingRow == -1; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece* p = board2.boardMove[r][c];
            if (p && p->getColor() == isWhite && (p->getPiece() == 'K' || p->getPiece() == 'k')) {
                kingRow = r;
                kingCol = c;
                break;
            }
        }
    }

    // Check if the move puts own king in check
    if (kingRow != -1) {
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                Piece* attacker = board2.boardMove[r][c];
                if (attacker && attacker->getColor() != isWhite) {
                    if (attacker->CheckLegalMove(r, c, kingRow, kingCol, board2.boardMove)) {
                        return 31; // King would be in check
                    }
                }
            }
        }
    }

    // Handle pawn promotion, if not just simulating the move
    if (Pawn* p = dynamic_cast<Pawn*>(srcPiece)) {
        if (!Simulate && ((p->getColor() && RowDestination == 0) || (!p->getColor() && RowDestination == 7))) {
            char UpdateTo;
            std::cout << "Promote pawn to (Q/R/B/N): ";
            std::cin >> UpdateTo;
            // Actual promotion logic should follow here
        }
    }
    // Update board string with the result of the move
    board = board2.getBoardString();
    return 42; // Move valid
}

// Runs the chess engine/analysis and prints best move suggestions.
// Parameters:
//   board      - reference to board string
//   isWhite    - true if it's White's turn
//   Depth      - search Depth for move suggestion
//   Threadsnum - number of threads to use (if applicable)
void run(std::string& board, bool isWhite, int Depth, int Threadsnum) {
    auto topMoves = getBestMoves(board, isWhite, Depth, Threadsnum);
    std::cout << "\nTop " << topMoves.size() << " Suggestions:\n" << topMoves << std::endl;
}
// Output operator for displaying top moves (score and move string)
std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<int, std::string>>& v) {
    for (const auto& [sc, mv] : v)
        os << mv << " (" << sc << ")\n";
    return os;
}

