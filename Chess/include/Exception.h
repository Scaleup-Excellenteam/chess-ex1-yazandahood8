#pragma once
#include <stdexcept>
#include <string>

class InvalidMoveException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid Move: The move is not allowed by the rules of chess.";
    }
};

class NoLegalMovesException : public std::exception {
public:
    const char* what() const noexcept override {
        return "No Legal Moves: No valid moves available for the player.";
    }
};
