#pragma once

#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif

#include <string>
#include "ThreadPool.h"
#include "PriorityQueue.h"
#include "Move.h"        // define your Move struct/class
#include "MoveComparator.h" // comparator for Move priority

using std::cout;
using std::cin; 
using std::endl;
using std::string; 

const int _SIZE = 21;

class Chess {
    unsigned char m_board[_SIZE][_SIZE] = { 0 };
    bool m_turn = true;
    string m_boardString;
    string m_input;
    string m_msg = "\n";
    string m_errorMsg = "\n";
    int m_codeResponse;

    // Thread-safe queue holding best moves from each piece
    PriorityQueue<Move, MoveComparator> m_sharedQueue;

    void clear() const;
    void setFrames();
    void setPieces();
    void show() const;
    void displayBoard() const;
    void showAskInput() const;
    bool isSame() const;
    bool isValid() const;
    bool isExit() const;
    void execute();
    void doTurn();

    // Internal: compute best moves using thread pool
    void computeBestMoves(int depth, bool autoPlay, size_t numThreads);

public:
    Chess(const string& start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
    Chess(const Chess&) = delete;
    Chess& operator=(const Chess&) = delete;

    string getInput();
    void setCodeResponse(int codeResponse);
    
    // Public API to start a game loop, with optional auto-play
    void run(int depth, bool autoPlay, size_t numThreads);
};
