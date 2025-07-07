#pragma once

#include <stdexcept>
#include <string>

/*
 * Custom exception types for chess board state and move errors.
 * 
 * Usage:
 *   - Throw IllegalException for illegal chess moves attempted by the user or AI.
 */

// Thrown when an attempted move violates chess rules
class IllegalException : public std::runtime_error {
public:
    // Construct with a custom error message
    explicit IllegalException(const std::string& msg)
        : std::runtime_error("Illegal move: " + msg) {}
};
