#pragma once

#include "chess_logic_API.h"
#include "board.h"

#include <vector>
#include <map>

namespace Chess {

	struct CHESSLOGIC_API LastMoveInfo {
		Position from;
		Position to;
		PieceType movedPieceType;
		Color movedPieceColor;
		bool isPawnDoubleStep;
		Position enPassantTargetSquare;

		LastMoveInfo() :
			from(0, 0), to(0, 0), movedPieceType(PieceType::None),
			movedPieceColor(Color::None), isPawnDoubleStep(false),
			enPassantTargetSquare(-1, -1) {}
	};


	class CHESSLOGIC_API Game {
	public:
		Game();

		void initializeGame();

		const Board& getBoard() const { return m_board; }

		Board& getBoard() { return m_board; }

		Color getCurrentPlayer() const { return m_currentPlayer; }

		void setCurrentTurn(Color color);

		void setCastlingRights(bool wk, bool wq, bool bk, bool bq);

		std::vector<Position> getValidMoves(Position from) const;

		bool makeMove(Position from, Position to);

		bool isKingInCheck(Color kingColor) const;

		bool isGameOver() const;

		void printGameState() const;

	private:
		Board m_board;
		Color m_currentPlayer;
		LastMoveInfo m_lastMoveInfo;

		bool wk, wq, bk, bq;
		bool m_whiteKingMoved;
		bool m_blackKingMoved;
		std::array<bool, 2> m_whiteRookMoved;
		std::array<bool, 2> m_blackRookMoved;

		void switchPlayer();

		bool willMovePutKingInCheck(Position from, Position to) const;
		
		std::vector<Position> getAttackedSquares(Color attackerColor) const;

		bool handleCastling(Position from, Position to);

		bool handleEnPassant(Position from, Position to);

		bool handlePawnPromotion(Position pawnPos);
	};
}
