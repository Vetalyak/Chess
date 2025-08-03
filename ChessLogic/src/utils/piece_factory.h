#pragma once

#include "chess_logic_API.h"
#include "pieces/piece.h"
#include "pieces/pawn.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/rook.h"
#include "pieces/queen.h"
#include "pieces/king.h"

#include <memory>

namespace Chess {

    class CHESSLOGIC_API PieceFactory {
    public:
        static std::unique_ptr<Piece> createPiece(PieceType type, Color color);
    };

}