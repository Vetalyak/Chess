#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "core/board.h"

namespace ChessUI {

    class PieceRenderer {
    public:
        PieceRenderer(const Chess::Board& board);

        void draw(sf::RenderWindow& window) const;
        void drawPiece(sf::RenderWindow& window, Chess::Position boardPos, const Chess::Piece* piece) const;
        void drawDraggedPiece(sf::RenderWindow& window, sf::Vector2f pixelPos, const Chess::Piece* piece) const;

        sf::Vector2f getPixelPosition(Chess::Position boardPos) const;
        Chess::Position getBoardPosition(sf::Vector2i) const;

    private:
        const Chess::Board& m_board;
        float m_squareSize;

        std::map<std::string, sf::Texture> m_pieceTextures;

        void loadPieceTextures();
        std::string getTexturePath(Chess::Color color, Chess::PieceType type) const;
        std::string getTextureKey(Chess::Color color, Chess::PieceType type) const;
    };
}
