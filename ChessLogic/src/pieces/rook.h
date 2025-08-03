#pragma once

#include "piece.h"

namespace Chess {

    class CHESSLOGIC_API Rook : public Piece {
    public:
        Rook(Color color) : Piece(color, PieceType::Rook) {}

        std::vector<Position> getPossibleMoves(Position currentPos, const Board& board) const override;
    };

}
