#include "Knight.h"
#include <cmath>

bool Knight::areSquaresLegal(int srcRow, int srcCol, int destRow, int destCol) {
    int rowDiff = std::abs(destRow - srcRow);
    int colDiff = std::abs(destCol - srcCol);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}
