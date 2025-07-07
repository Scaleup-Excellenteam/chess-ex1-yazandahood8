#pragma once

#include "Board.h"
#include <vector>
#include <string>
using namespace std;

// Evaluates the current board position.
// Returns a positive score if White is favored, negative if Black.
// Parameters:
//   board    - the board state to evaluate
//   isWhite  - true if evaluating from White's perspective
int BoardUpdate(const Board& board, bool isWhite);

// Helper function for recursive search algorithms (like minimax).
// Parameters:
//   board    - current game board (may be modified)
//   Depth    - search Depth remaining
//   isMax    - true if maximizing player's turn, false for minimizing
//   isWhite  - true if maximizing player is White
// Returns:
//   evaluation score for the board
int Helper(Board& board, int Depth, bool isMax, bool isWhite);

// Generates all legal moves for the current player.
// Parameters:
//   board    - current board (may be updated in move generation)
//   isWhite  - true for White's turn, false for Black's
// Returns:
//   vector of legal move strings (e.g., "e2e4")
vector<string> getLegalMoves(Board& board, bool isWhite);

// Returns a vector of best moves with their evaluation scores.
// Parameters:
//   boardStr    - string representing the current board state
//   isWhite     - true if White's turn
//   Depth       - Depth to search for best moves
//   Threadsnum  - number of threads to use for parallel search
// Returns:
//   vector of (score, move) pairs
vector<pair<int, string>> getBestMoves(string boardStr, bool isWhite, int Depth, int Threadsnum);
