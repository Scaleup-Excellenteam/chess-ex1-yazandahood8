#include "Board.h"
#include "Chess.h"
#include "GameValidator.h"
#include "Exception.h"
#include <iostream>

using namespace std;

int main() {
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess game(board);

    cout << "Choose mode:\n1. Play Game\n2. Suggest Moves\nChoice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int codeResponse = 0;
        string res = game.getInput();
        bool isWhite = true;
        while (res != "exit") {
            try {
                codeResponse = validateMove(res, board, isWhite);
                if (codeResponse == 42) isWhite = !isWhite;
                game.setCodeResponse(codeResponse);
            } catch (const InvalidMoveException& e) {
                cout << e.what() << endl;
            }
            res = game.getInput();
        }
        cout << "\nExiting Game.\n";
    }
    else if (choice == 2) {
        cout << "Enter depth (0-2): ";
        int depth;
        cin >> depth;
        Board boardObj;
        boardObj.loadFromString(board);

        try {
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
