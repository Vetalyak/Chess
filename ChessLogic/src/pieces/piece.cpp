#include "piece.h"
#include "core/board.h"

using namespace Chess;

bool Piece::isValidDestination(Position pos, const Board& board) const {
	if (pos.row < 0 || pos.row >= 8 || pos.col < 0 || pos.col >= 8)
		return false;

	const Piece* targetPiece = board.getPieceAt(pos);

	if (targetPiece == nullptr) {
		return true;
	}
	else {
		return targetPiece->getColor() != m_color;
	}
}
