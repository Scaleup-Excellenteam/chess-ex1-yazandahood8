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
#include <atomic>

using std::cout;
using std::cin; 
using std::endl;
using std::string; 

const int _SIZE = 21;

class Chess {
std::atomic<bool>   m_thresholdReached{false};
  int                 m_scoreThreshold{0};
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

   void computeBestMoves(int depth, bool autoPlay, size_t numThreads, int scoreThreshold);

public:
    Chess(const string& start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
    Chess(const Chess&) = delete;
    Chess& operator=(const Chess&) = delete;

    string getInput();
    void setCodeResponse(int codeResponse);
    
    void run(int depth, bool autoPlay, size_t numThreads, int scoreThreshold);

};
