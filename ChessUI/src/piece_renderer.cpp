#include "piece_renderer.h"
#include <iostream>

using namespace ChessUI;

PieceRenderer::PieceRenderer(const Chess::Board& board)
	: m_board(board),
	  m_squareSize(80.0f)
{
	loadPieceTextures();
	std::cout << "PieceRenderer created. Texture loaded" << std::endl;
}

void PieceRenderer::loadPieceTextures() {
	const std::string baseTexturePath = "assets/pieces/";

	for (int colorIdx = 0; colorIdx < 2; ++colorIdx) {
		Chess::Color color = (colorIdx == 0) ? Chess::Color::White : Chess::Color::Black;

		for (int typeIdx = 0; typeIdx < 6; ++typeIdx) {
			Chess::PieceType type;
			switch (typeIdx) {
			case 0: type = Chess::PieceType::Pawn; break;
			case 1: type = Chess::PieceType::Knight; break;
			case 2: type = Chess::PieceType::Bishop; break;
			case 3: type = Chess::PieceType::Rook; break;
			case 4: type = Chess::PieceType::Queen; break;
			case 5: type = Chess::PieceType::King; break;
			default: continue;
			}

			std::string textureKey = getTextureKey(color, type);
			std::string filePath = baseTexturePath + getTexturePath(color, type);

			sf::Texture texture;
			if (!texture.loadFromFile(filePath)) {
				std::cerr << "ERROR: Failed to load piece texture: " << filePath << std::endl;
				// throw exception;
			}
			m_pieceTextures[textureKey] = texture;
		}
	}
}

std::string PieceRenderer::getTexturePath(Chess::Color color, Chess::PieceType type) const {
	std::string colorStr = (color == Chess::Color::White) ? "white-" : "black-";
	std::string typeStr;
	switch (type) {
	case Chess::PieceType::Pawn:   typeStr = "pawn.png"; break;
	case Chess::PieceType::Knight: typeStr = "knight.png"; break;
	case Chess::PieceType::Bishop: typeStr = "bishop.png"; break;
	case Chess::PieceType::Rook:   typeStr = "rook.png"; break;
	case Chess::PieceType::Queen:  typeStr = "queen.png"; break;
	case Chess::PieceType::King:   typeStr = "king.png"; break;
	default:                       typeStr = "unknown.png"; break; // Fallback
	}
	return colorStr + typeStr;
}

std::string ChessUI::PieceRenderer::getTextureKey(Chess::Color color, Chess::PieceType type) const {
	std::string colorStr = (color == Chess::Color::White) ? "white_" : "black_";
	std::string typeStr;
	switch (type) {
	case Chess::PieceType::Pawn:   typeStr = "pawn"; break;
	case Chess::PieceType::Knight: typeStr = "knight"; break;
	case Chess::PieceType::Bishop: typeStr = "bishop"; break;
	case Chess::PieceType::Rook:   typeStr = "rook"; break;
	case Chess::PieceType::Queen:  typeStr = "queen"; break;
	case Chess::PieceType::King:   typeStr = "king"; break;
	default:                       typeStr = "unknown"; break;
	}
	return colorStr + typeStr;
}

void PieceRenderer::draw(sf::RenderWindow& window) const {
	for (int r = 0; r < Chess::Board::BOARD_SIZE; ++r) {
		for (int c = 0; c < Chess::Board::BOARD_SIZE; ++c) {

			Chess::Position currentPos = { r, c };
			const Chess::Piece* piece = m_board.getPieceAt(currentPos);

			if (piece != nullptr) {
				std::string textureKey = getTextureKey(piece->getColor(), piece->getType());

				auto it = m_pieceTextures.find(textureKey);
				if (it != m_pieceTextures.end()) {
					sf::Sprite sprite(it->second);

					sf::Vector2f pixelPos = getPixelPosition(currentPos);
					sprite.setPosition(pixelPos);

					float scaleX = m_squareSize / sprite.getGlobalBounds().size.x;
					float scaleY = m_squareSize / sprite.getGlobalBounds().size.y;

					sprite.setScale({ scaleX, scaleY });

					window.draw(sprite);
				}
			}
		}
	}
}

void ChessUI::PieceRenderer::drawPiece(sf::RenderWindow& window, Chess::Position boardPos, const Chess::Piece* piece) const {
	if (piece == nullptr) return;

	std::string texturekey = getTextureKey(piece->getColor(), piece->getType());
	auto it = m_pieceTextures.find(texturekey);
	if (it != m_pieceTextures.end()) {
		sf::Sprite sprite(it->second);
		sf::Vector2f pixelPos = getPixelPosition(boardPos);
		sprite.setPosition(pixelPos);

		float scaleX = m_squareSize / sprite.getGlobalBounds().size.x;
		float scaleY = m_squareSize / sprite.getGlobalBounds().size.y;
		sprite.setScale({ scaleX, scaleY });

		window.draw(sprite);
	}
}

void ChessUI::PieceRenderer::drawDraggedPiece(sf::RenderWindow& window, sf::Vector2f pixelPos, const Chess::Piece* piece) const {
	if (piece == nullptr) return;

	std::string texturekey = getTextureKey(piece->getColor(), piece->getType());
	auto it = m_pieceTextures.find(texturekey);
	if (it != m_pieceTextures.end()) {
		sf::Sprite sprite(it->second);
		sprite.setPosition(pixelPos);

		float scaleX = m_squareSize / sprite.getGlobalBounds().size.x;
		float scaleY = m_squareSize / sprite.getGlobalBounds().size.y;
		sprite.setScale({ scaleX, scaleY });

		window.draw(sprite);
	}
}

sf::Vector2f PieceRenderer::getPixelPosition(Chess::Position boardPos) const {
	float x = boardPos.col * m_squareSize;
	float y = (Chess::Board::BOARD_SIZE - 1 - boardPos.row) * m_squareSize;
	return { x, y };
}

Chess::Position PieceRenderer::getBoardPosition(sf::Vector2i pixelPos) const {
	int col = static_cast<int>(pixelPos.x / m_squareSize);
	int row = Chess::Board::BOARD_SIZE - 1 - static_cast<int>(pixelPos.y / m_squareSize);

	if (!m_board.isPositionValid({ row, col })) {
		return { -1, -1 };
	}
	return { row, col };
}
