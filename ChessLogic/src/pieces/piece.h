#pragma once

#include "chess_logic_API.h"
#include "core/color.h"
#include "core/piece_type.h"
#include "core/position.h"
#include <vector>

namespace Chess { class Board; }

namespace Chess {

	class CHESSLOGIC_API Piece {
	protected:
		const Color m_color;
		const PieceType m_type;
		bool m_hasMoved = false;
	public:
		Piece(Color color, PieceType type) : m_color(color), m_type(type) {}

		virtual ~Piece() = default;

		virtual std::vector<Position> getPossibleMoves(Position currentPos, const Board& board) const = 0;

		// Getters
		Color getColor() const { return m_color; }
		PieceType getType() const { return m_type; }
		bool hasMoved() const { return m_hasMoved; }

		void setHasMoved(bool moved) { m_hasMoved = moved; }

		bool isValidDestination(Position pos, const Board& board) const;
		bool isWhite() const { return m_color == Color::White; }
	};

}
