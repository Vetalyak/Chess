#pragma once

#include "piece.h"

namespace Chess {

    class CHESSLOGIC_API Queen : public Piece {
    public:
        Queen(Color color) : Piece(color, PieceType::Queen) {}

        std::vector<Position> getPossibleMoves(Position currentPos, const Board& board) const override;
    };

}
