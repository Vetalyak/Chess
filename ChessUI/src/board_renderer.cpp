#include "board_renderer.h"

using namespace ChessUI;

BoardRenderer::BoardRenderer(const Chess::Board& board)
    : m_board(board),
    m_squareSize(80.0f),
    m_lightSquareColor(sf::Color(238, 238, 210)),
    m_darkSquareColor(sf::Color(118, 150, 86)) { }

void BoardRenderer::draw(sf::RenderWindow& window) const {
    for (int r = 0; r < Chess::Board::BOARD_SIZE; ++r) {
        for (int c = 0; c < Chess::Board::BOARD_SIZE; ++c) {
            sf::RectangleShape square(sf::Vector2f(m_squareSize, m_squareSize));

            if ((r + c) % 2 == 0) {
                square.setFillColor(m_darkSquareColor);
            }
            else {
                square.setFillColor(m_lightSquareColor);
            }

            square.setPosition({ c * m_squareSize, (Chess::Board::BOARD_SIZE - 1 - r) * m_squareSize });
            window.draw(square);
        }
    }
}

void ChessUI::BoardRenderer::loadResources() {
}
