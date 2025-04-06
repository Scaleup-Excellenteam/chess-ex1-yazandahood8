#include "Board.h"
#include "Rook.h"
#include "King.h"

Board::Board(const std::string& initialState) {
    grid.resize(8, std::vector<std::unique_ptr<Piece>>(8, nullptr));
    for (int i = 0; i < 64; ++i) {
        char c = initialState[i];
        if (c == '#') continue;

        int row = i / 8;
        int col = i % 8;
        bool isWhite = isupper(c);

        switch (tolower(c)) {
            case 'r': grid[row][col] = std::make_unique<Rook>(isWhite); break;
            case 'k': grid[row][col] = std::make_unique<King>(isWhite); break;
        }
    }
}

Piece* Board::get(int x, int y) const {
    return grid[x][y].get();
}

void Board::move(int sx, int sy, int dx, int dy) {
    grid[dx][dy] = std::move(grid[sx][sy]);
    grid[sx][sy] = nullptr;
}

bool Board::isPathClear(int sx, int sy, int dx, int dy) const {
    int stepX = (dx - sx) ? (dx - sx) / abs(dx - sx) : 0;
    int stepY = (dy - sy) ? (dy - sy) / abs(dy - sy) : 0;

    int x = sx + stepX, y = sy + stepY;
    while (x != dx || y != dy) {
        if (grid[x][y]) return false;
        x += stepX;
        y += stepY;
    }
    return true;
}
