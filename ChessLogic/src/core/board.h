#pragma once

#include "chess_logic_API.h"
#include "pieces/piece.h"

#include <array>
#include <memory>

namespace Chess {
    class CHESSLOGIC_API Board {
    public:
        static const int BOARD_SIZE = 8;
        Board();

        void clear();

        void initializeBoard();

        const Piece* getPieceAt(Position pos) const;
        void setPieceAt(Position pos, std::unique_ptr<Piece> piece);

        std::unique_ptr<Piece> removePieceAt(Position pos);

        void movePiece(Position from, Position to);

        bool isPositionValid(Position pos) const;

        bool isSquareEmpty(Position pos) const;

        void printBoard() const;

    private:
        using BoardArray = std::array<std::array<std::unique_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE>;
        BoardArray m_squares;
    };
}
