#pragma once

#include "chess_logic_API.h"

#include "core/game.h"

namespace Chess {
namespace FEN {
	CHESSLOGIC_API void applyPosition(Game& game, const std::string& fen);
}
}
