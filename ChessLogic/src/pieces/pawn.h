#pragma once

#include "piece.h"

namespace Chess {

    class CHESSLOGIC_API Pawn : public Piece {
    public:
        Pawn(Color color) : Piece(color, PieceType::Pawn) {}

        std::vector<Position> getPossibleMoves(Position currentPos, const Board& board) const override;
    };

}