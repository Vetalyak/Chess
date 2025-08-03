#pragma once

#include "piece.h"

namespace Chess {

    class CHESSLOGIC_API King : public Piece {
    public:
        King(Color color) : Piece(color, PieceType::King) {}

        std::vector<Position> getPossibleMoves(Position currentPos, const Board& board) const override;
    };

}