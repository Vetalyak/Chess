#pragma once

#include "chess_logic_API.h"

namespace Chess {
    struct CHESSLOGIC_API Position {
        int row;
        int col;
        Position(int r = 0, int c = 0) : row(r), col(c) {}

        bool operator==(const Position& other) const {
            return row == other.row && col == other.col;
        }

        bool operator!=(const Position& other) const {
            return !(*this == other);
        }
    };
}
