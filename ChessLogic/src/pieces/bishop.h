#pragma once

#include "piece.h"

namespace Chess {

    class CHESSLOGIC_API Bishop : public Piece {
    public:
        Bishop(Color color) : Piece(color, PieceType::Bishop) {}

        std::vector<Position> getPossibleMoves(Position currentPos, const Board& board) const override;
    };

}
