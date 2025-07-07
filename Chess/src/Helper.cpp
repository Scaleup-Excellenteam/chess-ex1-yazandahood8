#include "Helper.h"
#include "Board.h"
#include "Piece.h"
#include "PriorityQueue.h"
#include "GameValidator.h"
#include "ThreadPool.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <limits>
#include <future>
#include <algorithm>

using namespace std;

// Piece-square tables 
const int queen[8][8] = {
    {-20, -10, -10, -5, -5, -10, -10, -20},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-10, 0, 5, 5, 5, 5, 0, -10},
    {-5, 0, 5, 5, 5, 5, 0, -5},
    {0, 0, 5, 5, 5, 5, 0, -5},
    {-10, 5, 5, 5, 5, 5, 0, -10},
    {-10, 0, 5, 0, 0, 0, 0, -10},
    {-20, -10, -10, -5, -5, -10, -10, -20}};
const int king[8][8] = {
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-30, -40, -40, -50, -50, -40, -40, -30},
    {-20, -30, -30, -40, -40, -30, -30, -20},
    {-10, -20, -20, -20, -20, -20, -20, -10},
    {20, 20, 0, 0, 0, 0, 20, 20},
    {20, 30, 10, 0, 0, 10, 30, 20}};
const int pawn[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {5, 5, 10, 25, 25, 10, 5, 5},
    {0, 0, 0, 20, 20, 0, 0, 0},
    {5, -5, -10, 0, 0, -10, -5, 5},
    {5, 10, 10, -20, -20, 10, 10, 5},
    {0, 0, 0, 0, 0, 0, 0, 0}};
const int knight[8][8] = {
    {-50, -40, -30, -30, -30, -30, -40, -50},
    {-40, -20, 0, 0, 0, 0, -20, -40},
    {-30, 0, 10, 15, 15, 10, 0, -30},
    {-30, 5, 15, 20, 20, 15, 5, -30},
    {-30, 0, 15, 20, 20, 15, 0, -30},
    {-30, 5, 10, 15, 15, 10, 5, -30},
    {-40, -20, 0, 5, 5, 0, -20, -40},
    {-50, -40, -30, -30, -30, -30, -40, -50}};
const int bishop[8][8] = {
    {-20, -10, -10, -10, -10, -10, -10, -20},
    {-10, 0, 0, 0, 0, 0, 0, -10},
    {-10, 0, 5, 10, 10, 5, 0, -10},
    {-10, 5, 5, 10, 10, 5, 5, -10},
    {-10, 0, 10, 10, 10, 10, 0, -10},
    {-10, 10, 10, 10, 10, 10, 10, -10},
    {-10, 5, 0, 0, 0, 0, 5, -10},
    {-20, -10, -10, -10, -10, -10, -10, -20}};
const int rook[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {5, 10, 10, 10, 10, 10, 10, 5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {-5, 0, 0, 0, 0, 0, 0, -5},
    {0, 0, 0, 5, 5, 0, 0, 0}};

// Piece values for evaluation
static map<char, int> piece_value = {
    {'p', 100}, {'n', 320}, {'b', 330}, {'r', 500}, {'q', 900}, {'k', 20000}, {'P', 100}, {'N', 320}, {'B', 330}, {'R', 500}, {'Q', 900}, {'K', 20000}};

const int score1 = 100000;
/**
 * Checks if the king of a given color is in check on the current board.
 * @param board         Reference to the current board object.
 * @param for_white_player  True for white's king, false for black's.
 * @return                  True if king is in check, false otherwise.
 */
bool Check(Board &board, bool for_white_player)
{
    int king_r = -1, king_c = -1;
    char king_char_to_find = for_white_player ? 'K' : 'k';

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Piece *p = board.boardMove[r][c];
            if (p && p->getPiece() == king_char_to_find)
            {
                king_r = r;
                king_c = c;
                break;
            }
        }
        if (king_r != -1)
            break;
    }

    if (king_r == -1)
        return false;

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Piece *p = board.boardMove[r][c];
            if (p && p->getColor() != for_white_player)
            {
                if (p->CheckLegalMove(r, c, king_r, king_c, board.boardMove))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
/**
 * Evaluates the current board position for material, piece placement, pawn structure, etc.
 * Returns positive if White is better, negative if Black is better.
 * @param board     Reference to board object to evaluate.
 */
int BoardUpdate(Board &board)
{
    int score = 0;
    int whitePawnsArr[8] = {0};
    int blackPawnsArr[8] = {0};
    int cntWhite = 0;
    int cntBlack = 0;

    for (int r = 0; r < 8; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Piece *p = board.boardMove[r][c];
            if (!p)
                continue;

            char ch = p->getPiece();
            int material_val = piece_value[ch];
            bool IswhiteP = p->getColor();

            score += IswhiteP ? material_val : -material_val;

            int row = IswhiteP ? r : 7 - r;
            int col = c;

            if (ch == 'P')
            {
                score += pawn[row][col];
                whitePawnsArr[c]++;
            }
            else if (ch == 'b')
            {
                score -= bishop[row][col];
                cntBlack++;
            }
            else if (ch == 'R')
                score += rook[row][col];
            else if (ch == 'r')
                score -= rook[row][col];
            else if (ch == 'Q')
                score += queen[row][col];
            else if (ch == 'p')
            {
                score -= pawn[row][col];
                blackPawnsArr[c]++;
            }
            else if (ch == 'q')
                score -= queen[row][col];
            else if (ch == 'K')
                score += king[row][col];
            else if (ch == 'N')
                score += knight[row][col];
            else if (ch == 'n')
                score -= knight[row][col];
            else if (ch == 'B')
            {
                score += bishop[row][col];
                cntWhite++;
            }

            else if (ch == 'k')
                score -= king[row][col];

            // Rook on open/semi-open file
            if (ch == 'R' || ch == 'r')
            {
                bool flag = false;
                for (int i = 0; i < 8; ++i)
                {
                    Piece *p = board.boardMove[i][c];
                    if (p)
                    {
                        if (IswhiteP && p->getPiece() == 'P')
                            flag = true;
                        else if (!IswhiteP && p->getPiece() == 'p')
                            flag = true;
                    }
                }
                if (!flag)
                {
                    score += IswhiteP ? 10 : -10;

                    score += IswhiteP ? 15 : -15;
                }
            }
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        if (whitePawnsArr[i] > 1)
            score -= (whitePawnsArr[i] - 1) * 20;
        if (blackPawnsArr[i] > 1)
            score += (blackPawnsArr[i] - 1) * 20;
    }

    if (cntWhite >= 2)
        score += 50;
    if (cntBlack >= 2)
        score -= 50;

    return score;
}
/**
 * Gets the top moves (up to PriorityQueue max_e) for the current position,
 * using parallel threads if requested.
 * @param board    Board state as a string.
 * @param is_white      True if white to move.
 * @param Depth                Search depth.
 * @param num_threads          Number of threads to use (1 = single-threaded).
 * @return                     Vector of (score, move) pairs (sorted by priority).
 */
vector<pair<int, string>> getBestMoves(string board, bool is_white, int Depth, int num_threads)
{
    Board board1;
    board1.loadFromString(board);
    vector<string> LegalMovesVector = getLegalMoves(board1, is_white);

    PriorityQueue<pair<int, string>> priorityQueue;

    auto updateMove =[&priorityQueue, board, is_white, Depth](const string &move)
    {
        string board2 = board;

        int validation_result = validateMove(move, board2, is_white, true);

        if (validation_result >= 41)
        {
            Board board3;
            board3.loadFromString(board2);
            int s=100;
            bool f=!is_white;
            int score = Helper(board3, Depth, -score1 - s,score1 + s,f);

            int updateScore;
            if (is_white)
            {
                updateScore = score;
            }
            else
            {
                updateScore = -score;
            }
            priorityQueue.push({updateScore, move});
        }
    };

    if (num_threads > 1 && LegalMovesVector.size() > 1)
    {
        vector<future<void>> res;
        ThreadPool threadpool(num_threads);
        for (const auto &legalmove : LegalMovesVector)
        {
            res.emplace_back(threadpool.enqueue(updateMove, legalmove));
        }
        for (auto &&result : res)
        {
            try
            {
                result.get();
            }
            catch (const std::exception &e)
            {
                cerr << "Exception thread: " << e.what() ;
                cerr << std::endl;
            }
        }
    }
    else
    {
        for (const auto &legalmove : LegalMovesVector)
        {
            updateMove(legalmove);
        }
    }
    std::vector<std::pair<int, std::string>> BestMovesVector = priorityQueue.QueueToVector();
    return BestMovesVector;
}
/**
 * Generates all legal moves for the player whose turn it is.
 * Each move is checked by validateMove (including self-check).
 * @param board            Reference to board object (will not be modified)
 * @param for_white_player     True for white's moves, false for black's.
 * @return                     Vector of all legal moves as strings.
 */
vector<string> getLegalMoves(Board &board, bool for_white_player)
{
    vector<string> moves;
    string BeginBoard = board.getBoardString();

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Piece *piece = board.boardMove[i][j];
            if (piece && piece->getColor() == for_white_player)
            {
                for (int k = 0; k < 8; ++k)
                {
                    for (int t = 0; t < 8; ++t)
                    {
                        if (i == k && j == t)
                            continue;
                        char ch='a';
                        char num='1';
                        string str = string(1, ch + i) + string(1, num + j) +string(1, ch + k) + string(1, num + t);

                        string tmp = BeginBoard;

                        int result = validateMove(str, tmp, for_white_player, true);

                        if (result >= 41)
                        {
                            moves.push_back(str);
                        }
                    }
                }
            }
        }
    }
    return moves;
}

/**
 * Evaluates the board to a given depth for best/worst possible outcome.
 * @param board                  Reference to board object.
 * @param Depth                        Remaining search depth.
 * @param a, b                  a-b bounds.
 * @param maximizing   Whose turn to move.
 * @return                             Evaluation score.
 */
int Helper(Board &board, int Depth, int a, int b, bool maximizing)
{
    if (Depth == 0)
    {
        return BoardUpdate(board);
    }

    vector<string> LegalMovesVector = getLegalMoves(board, maximizing);

    if (LegalMovesVector.empty())
    {
        if (Check(board, maximizing))
        {
            if (maximizing)
            {
                return -score1; // Checkmate for maximizing player
            }
            else
            {
                return score1; // Checkmate for minimizing player
            }
        }
        else
        {
            return 0;
        }
    }

    if (maximizing)
    {
        int max_e = -score1 - 1;
        for (const string &move : LegalMovesVector)
        {
            string board1 = board.getBoardString();
            string board2 = board1;

            int validation_code = validateMove(move, board2, true, true);
            if (validation_code < 41)
                continue;

            Board newBoard;
            newBoard.loadFromString(board2);

            int eval = Helper(newBoard, Depth - 1, a, b, false);
            max_e = max(max_e, eval);
            a = max(a, eval);
            if (b <= a)
            {
               return max_e; 
            }
        }
        return max_e;
    }
    else
    {
        int min_e = score1 + 1;
        for (const string &move : LegalMovesVector)
        {
            string board1 = board.getBoardString();
            string board2 = board1;

            int validation_code = validateMove(move, board2, false, true);
            if (validation_code < 41)
                continue;

            Board newBoard;
            newBoard.loadFromString(board2);

            int eval = Helper(newBoard, Depth - 1, a, b, true);
            min_e = min(min_e, eval);
            b = min(b, eval);
            if (b <= a)
            {
                break;
            }
        }
        return min_e;
    }
}

