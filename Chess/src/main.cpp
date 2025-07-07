#include "Chess.h"
#include "GameValidator.h"
#include "Exceptions.h"
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include "Helper.h"
using namespace std;

// Forward declaration
void run(string& board, bool isWhite, int Depth, int Threadsnum);

void runAutomaticGame(int Depth, int Threadsnum) {
    cout << "\n--- Running Automatic Game ---" << endl;
    cout << "Depth: " << Depth << ", Threads: " << Threadsnum << endl;

    string board = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR";
    bool isWhite = true;
    const int totalMoves = 8; // 4 moves per side

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < totalMoves; ++i) {
        auto best_moves = getBestMoves(board, isWhite, Depth, Threadsnum);
        if (best_moves.empty()) {
            cout << "No legal moves. Game over." << endl;
            break;
        }
        string best_move = best_moves.front().second;
        cout << "Move " << i + 1 << ": " << best_move << endl;

        int codeResponse = validateMove(best_move, board, isWhite, false);
        if (codeResponse >= 41) {
            isWhite = !isWhite;
        } else {
            cout << "Error: Invalid move generated: " << best_move << " with code " << codeResponse << endl;
            break;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "Automatic game finished in " << diff.count() << " seconds." << endl;
}

void runManualGame(int Depth, int Threadsnum) {
    string board = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR";
    Chess a(board);
    int codeResponse = 0;
    string res;
    bool isWhite = true;

    while (true) {

        run(board, isWhite, Depth, Threadsnum);

        res = a.getInput();
        if (res == "exit") break;

        try {
            codeResponse = validateMove(res, board, isWhite, false);

            if (codeResponse >= 41) {
                isWhite = !isWhite;
            }

            a.setCodeResponse(codeResponse);
        } catch (const std::exception& e) {
            cout << "An error occurred: " << e.what() << endl;
        }
    }
}

int main() {
    int Depth = 3;
    string mode;

    cout << "Enter search Depth for move suggestions (e.g., 3): ";
    cin >> Depth;

    cout << "Enter 'auto' for benchmark or 'manual' for interactive play: ";
    cin >> mode;

    if (mode == "auto") {
        runAutomaticGame(Depth, 1);
        runAutomaticGame(Depth, 2);
        runAutomaticGame(Depth, 4);
        runAutomaticGame(Depth, 8);
    } else {
        int Threadsnum = 4;
        cout << "Enter number of threads for suggestions (e.g., 4): ";
        cin >> Threadsnum;
        runManualGame(Depth, Threadsnum);
    }

    cout << endl << "Exiting." << endl;
    return 0;
}