#pragma once
#include <string>

// Runs the chess engine or simulation loop.
// Parameters:
//   board      - reference to a string representing the current board state (will be modified)
//   isWhite    - true if it's White's turn to move; false for Black
//   Depth      - Depth of move search (e.g., for minimax or AI search)
//   Threadsnum - number of threads to use (for multithreaded search, if supported)
void run(std::string& board, bool isWhite, int Depth, int Threadsnum);

// Validates a proposed chess move.
// Parameters:
//   move      - the move to validate, in string notation
//   board     - reference to the board state (may be modified if Simulate is true)
//   turn      - true if it's White's turn; false for Black
//   Simulate  - if true, the function will simulate the move and update the board;
//               if false, only validation occurs, no state change
// Returns:
//   int - status code (e.g., 0 for legal, nonzero for specific errors)
int validateMove(const std::string& move, std::string& board, bool isTurn, bool Simulate);
