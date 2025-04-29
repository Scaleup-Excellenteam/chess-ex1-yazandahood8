#ifndef MY_EXCEPTIONS_H
#define MY_EXCEPTIONS_H

#include <stdexcept>

class InvalidMoveException : public std::exception {
    const char* what() const noexcept override {
        return "Invalid move attempted!";
    }
};

class EmptyQueueException : public std::exception {
    const char* what() const noexcept override {
        return "Polling from an empty priority queue!";
    }
};

#endif
