#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "core/game.h"
#include "board_renderer.h"
#include "piece_renderer.h"

namespace ChessUI {

    class GameWindow {
    public:
        // Init SFML and other components
        GameWindow(unsigned int width = 640, unsigned int height = 640, const std::string& title = "Chess");

        // Main loop
        void run();

    private:
        // SFML window
        sf::RenderWindow m_window;
        Chess::Game m_gameLogic;
        BoardRenderer m_boardRenderer;
        PieceRenderer m_pieceRenderer;

        // InputHandler m_inputHandler

        bool m_isDragging;
        Chess::Position m_draggedPieceStartPos;
        const Chess::Piece* m_draggedPiece;
        sf::Vector2f m_mouseOffset;

        void processEvents();
        void update(sf::Time deltaTime);
        void render();
    };
}
