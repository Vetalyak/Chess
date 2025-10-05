#include "fen.h"
#include "utils/piece_factory.h"

#include <sstream>
#include <stdexcept>
#include <cctype>

namespace Chess{
namespace FEN{


void applyPosition(Game& game, const std::string& fen) {
	std::istringstream iss(fen);
	std::string boardPart, activeColor, castling, enPassant;
	int halfmoveClock, fullMoveNumber;

	if (!(iss >> boardPart >> activeColor >> castling >> enPassant >> halfmoveClock >> fullMoveNumber)) {
		throw std::invalid_argument("Invalid FEN string");
	}

	Board& board = game.getBoard();
	board.clear();

	int rank = 7, file = 0;
	for (char c : boardPart) {
		if (c == '/') {
			rank--;
			file = 0;
		} 
		else if (std::isdigit(c)) {
			file += c - '0';
		}
		else {
			Color color = std::isupper(c) ? Color::White : Color::Black;
			PieceType type;
			switch (std::tolower(c)) {
				case 'p': type = PieceType::Pawn; break;
				case 'n': type = PieceType::Knight; break;
				case 'b': type = PieceType::Bishop; break;
				case 'r': type = PieceType::Rook; break;
				case 'q': type = PieceType::Queen; break;
				case 'k': type = PieceType::King; break;
				default: throw std::invalid_argument("Unknown piece");
			}
			board.setPieceAt({rank, file}, PieceFactory::createPiece(type, color));
			++file;
		}

		game.setCurrentTurn(activeColor == "w" ? Color::White : Color::Black);
		
	}
	


}


} // namespace FEN
} // namespace Chess
