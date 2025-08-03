#include "pawn.h"
#include "core/board.h"

using namespace Chess;

std::vector<Position> Pawn::getPossibleMoves(Position currentPos, const Board& board) const {
    std::vector<Position> possibleMoves;
    int direction = isWhite() ? 1 : -1; // white (+1), black (-1)

    Position oneStepForward = { (uint8_t)(currentPos.row + direction), currentPos.col };
    if (board.isPositionValid(oneStepForward) && board.getPieceAt(oneStepForward) == nullptr) {
        possibleMoves.push_back(oneStepForward);

        Position twoStepsForward = { (uint8_t)(currentPos.row + 2 * direction), currentPos.col };
        if (!m_hasMoved && board.isPositionValid(twoStepsForward) && board.getPieceAt(twoStepsForward) == nullptr) {
            possibleMoves.push_back(twoStepsForward);
        }
    }

    Position diagLeft = { (uint8_t)(currentPos.row + direction), (uint8_t)(currentPos.col - 1) };
    if (board.isPositionValid(diagLeft)) {
        const Piece* targetPiece = board.getPieceAt(diagLeft);
        if (targetPiece != nullptr && targetPiece->getColor() != m_color) {
            possibleMoves.push_back(diagLeft);
        }
    }

    Position diagRight = { (uint8_t)(currentPos.row + direction), (uint8_t)(currentPos.col + 1) };
    if (board.isPositionValid(diagLeft)) {
        const Piece* targetPiece = board.getPieceAt(diagRight);
        if (targetPiece != nullptr && targetPiece->getColor() != m_color) {
            possibleMoves.push_back(diagRight);
        }
    }

    // TODO: En Passant
    // TODO: Promotion

    return possibleMoves;
}
