#include "knight.h"
#include "core/board.h"

using namespace Chess;

std::vector<Position> Knight::getPossibleMoves(Position currentPos, const Board& board) const {
    std::vector<Position> possibleMoves;
    
    int dr[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
    int dc[] = { 1, -1, 1, -1, 2, -2, 2, -2 };
    
    for (int i = 0; i < 8; ++i) {
        Position nextPos = {
            currentPos.row + dr[i],
            currentPos.col + dc[i]
        };

        if (isValidDestination(nextPos, board)) {
            possibleMoves.push_back(nextPos);
        }
    }
    return possibleMoves;
}