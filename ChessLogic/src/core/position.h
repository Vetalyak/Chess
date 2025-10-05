#pragma once

#include "chess_logic_API.h"
#include <string>

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

		std::string toString() const {
			if (col >= 0 && col <= 7 && row >= 0 && row <= 7) {
				char colChar = (char)('a' + col); 
				return colChar + std::to_string(row + 1);
			}
			return std::string("NULL");
		}
	};
}
