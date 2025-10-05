#include "king.h"
#include "core/board.h"

using namespace Chess;

std::vector<Position> King::getPossibleMoves(Position currentPos, const Board& board) const {
	std::vector<Position> possibleMoves;

	int dr[] = { 1, -1, 0, 0, 1, 1, -1, -1 };
	int dc[] = { 0, 0, 1, -1, 1, -1, 1, -1 };

	for (int i = 0; i < 8; ++i) {
		Position nextPos = {
			currentPos.row + dr[i],
			currentPos.col + dc[i]
		};

		if (board.isPositionValid(nextPos)) {
			const Piece* targetPiece = board.getPieceAt(nextPos);

			if (targetPiece == nullptr || targetPiece->getColor() != m_color) {
				possibleMoves.push_back(nextPos);
			}
		}
	}

	// TODO: logic for Castling
	// It's not simply a "piece move", but rather a "game move"

	return possibleMoves;
}
