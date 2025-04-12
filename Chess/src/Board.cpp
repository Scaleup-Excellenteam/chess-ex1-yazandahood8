#include "Board.h"
#include "Rook.h"
#include "King.h"

Board::Board(const std::string& initialState) {
    grid.resize(8);
    for (int i = 0; i < 8; ++i)
        grid[i].resize(8); // פשוט לא מכניס שום פוינטר, יוצר nullptr

    for (int i = 0; i < 64; ++i) {
        char c = initialState[i];
        if (c == '#') continue;

        int row = i / 8;
        int col = i % 8;
        bool isWhite = isupper(c);

        switch (tolower(c)) {
            case 'r': grid[row][col] = std::make_unique<Rook>(c, isWhite); break;
            case 'k': grid[row][col] = std::make_unique<King>(c, isWhite); break;
            // תוסיף עוד כלים כאן אם תפתח בהמשך
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
