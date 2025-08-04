#pragma once

#include "piece.h"

namespace Chess {

    class CHESSLOGIC_API Knight : public Piece {
    public:
        Knight(Color color) : Piece(color, PieceType::Knight) {}

        std::vector<Position> getPossibleMoves(Position currentPos, const Board& board) const override;
    };

}
