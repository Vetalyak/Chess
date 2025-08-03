#include "queen.h"
#include "core/board.h"

using namespace Chess;

std::vector<Position> Queen::getPossibleMoves(Position currentPos, const Board& board) const {
    std::vector<Position> possibleMoves;

    int dr[] = { 1, -1, 0, 0, 1, 1, -1, -1 };
    int dc[] = { 0, 0, 1, -1, 1, -1, 1, -1 };

    for (int i = 0; i < 8; ++i) {
        for (int step = 1; ; ++step) {
            Position nextPos = {
                currentPos.row + dr[i] * step,
                currentPos.col + dc[i] * step
            };

            if (!board.isPositionValid(nextPos)) {
                break;
            }
            const Piece* targetPiece = board.getPieceAt(nextPos);

            if (targetPiece == nullptr) {
                possibleMoves.push_back(nextPos);
            }
            else {
                if (targetPiece->getColor() != m_color) {
                    possibleMoves.push_back(nextPos);
                }
                break;
            }
        }
    }
    return possibleMoves;
}
