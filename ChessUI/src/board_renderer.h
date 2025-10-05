#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "core/board.h"

namespace ChessUI {
	class BoardRenderer {
	public:
		BoardRenderer(const Chess::Board& board);

		void draw(sf::RenderWindow& window) const;

		float getSquareSize() const { return m_squareSize; }

	private:
		const Chess::Board& m_board;
		float m_squareSize;
		sf::Color m_lightSquareColor;
		sf::Color m_darkSquareColor;

		void loadResources();
	};
}
