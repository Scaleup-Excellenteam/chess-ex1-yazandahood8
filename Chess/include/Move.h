#ifndef MOVE_H
#define MOVE_H

#include <string>

struct Move {
    std::string from;
    std::string to;
    int score;

    Move(std::string f, std::string t, int s)
        : from(std::move(f)), to(std::move(t)), score(s) {}
};

struct MoveComparator {
    int operator()(const Move& a, const Move& b) const {
        return b.score - a.score; // העדפה לציונים גבוהים
    }
};

#endif
