#include "Board.h"
#include "Chess.h"
#include "GameValidator.h"
#include "Exception.h"
#include <iostream>

using namespace std;

// Function to suggest the best moves (not used in this main version but kept for modularity)
void BestMove(Board& boardObj, int Color, int depth) {
    PriorityQueue<Move> bestMoves = boardObj.BestMove(Color, depth, 8);
    cout << bestMoves;
}

int main() {
    // Standard starting board setup (White pieces on top)
    string boardStr = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess game(boardStr);

    cout << "Choose mode:\n1. Play Game\n2. Suggest Moves\nChoice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        // Game play mode
        int codeResponse = 0;
        string inputMove = game.getInput();
        bool isWhiteTurn = true;

        while (inputMove != "exit") {
            try {
                codeResponse = validateMove(inputMove, boardStr, isWhiteTurn);
                if (codeResponse == 42) {
                    isWhiteTurn = !isWhiteTurn; // Switch turns
                }
                game.setCodeResponse(codeResponse);
            } catch (const InvalidMoveException& e) {
                cout << e.what() << endl;
            }

            inputMove = game.getInput();
        }

        cout << "\nExiting Game.\n";
    }
    else if (choice == 2) {
        // Best move suggestion mode
        cout << "Enter depth (1-2): ";
        int depth;
        cin >> depth;

        if (depth < 1 || depth > 2) {
            cout << "Invalid depth. Please enter a value between 1 and 2.\n";
            return 1;
        }

        Board boardObj;
        boardObj.loadFromString(boardStr);

        try {
            cout << "Suggested best moves:\n";
            boardObj.suggestBestMove(true, depth);
        } catch (const NoLegalMovesException& e) {
            cout << e.what() << endl;
        } catch (const exception& e) {
            cout << "An error occurred: " << e.what() << endl;
        }
    }
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
