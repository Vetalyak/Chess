#include "game_window.h"

using namespace ChessUI;

GameWindow::GameWindow(unsigned int width, unsigned int height, const std::string& title)
	: m_window(sf::VideoMode({width, height}), title),
	  m_gameLogic(),
	  m_boardRenderer(m_gameLogic.getBoard()),
	  m_pieceRenderer(m_gameLogic.getBoard()),
	  m_isDragging(false),
	  m_draggedPieceStartPos({-1, -1}),
	  m_draggedPiece(nullptr)
{
	m_window.setFramerateLimit(100);
	m_window.setVerticalSyncEnabled(true);

	m_gameLogic.initializeGame();

	m_gameLogic.printGameState();

	std::cout << "GameWindow created. Ready to run." << std::endl;
}

void GameWindow::run() {
	sf::Clock clock;

	while (m_window.isOpen()) {
		sf::Time deltaTime = clock.restart();

		processEvents();
		update(deltaTime);
		render();
	}
}

void GameWindow::processEvents() {
	while (const std::optional event = m_window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			m_window.close();
		}
		else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (mousePressed->button == sf::Mouse::Button::Left) {
				sf::Vector2i mousePixelPos = { mousePressed->position.x, mousePressed->position.y };
				Chess::Position clickedBoardPos = m_pieceRenderer.getBoardPosition(mousePixelPos);

				const Chess::Piece* piece = m_gameLogic.getBoard().getPieceAt(clickedBoardPos);

				if (piece != nullptr && piece->getColor() == m_gameLogic.getCurrentPlayer()) {
					m_isDragging = true;
					m_draggedPieceStartPos = clickedBoardPos;
					m_draggedPiece = piece;

					sf::Vector2f piecePixelPos = m_pieceRenderer.getPixelPosition(clickedBoardPos);
					m_mouseOffset = sf::Vector2f({ (float)mousePixelPos.x, (float)mousePixelPos.y }) - piecePixelPos;

					std::cout << "Picked up " << (piece->isWhite() ? "White" : "Black") << " "
						<< (int)piece->getType() << " from " << clickedBoardPos.toString() << std::endl;

					// TODO: highlight possible moves
				}
			}
		}
		else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
			if (m_isDragging) {

			}
		}
		else if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
			if (mouseReleased->button == sf::Mouse::Button::Left && m_isDragging) {
				sf::Vector2i mousePixelPos = mouseReleased->position;
				Chess::Position targetBoardPos = m_pieceRenderer.getBoardPosition(mousePixelPos);

				std::cout << "Released piece at " << targetBoardPos.toString() << std::endl;

				if (m_gameLogic.makeMove(m_draggedPieceStartPos, targetBoardPos)) {
					std::cout << "Move successful!" << std::endl;
					m_gameLogic.printGameState();
				}
				else {
					std::cout << "Invalid move or failed to make move. Piece returns." << std::endl;
				}
				

				m_isDragging = false;
				m_draggedPieceStartPos = { -1, -1 };
				m_draggedPiece = nullptr;

				// TODO: clear highlighted moves
				// m_highlightedMoves.clear();

			}
		}
	}
}

void GameWindow::update(sf::Time deltaTime) {
	// TODO: animation or timers
}

void GameWindow::render() {
	m_window.clear(sf::Color(100, 100, 100));
	m_boardRenderer.draw(m_window);

	// Малюємо всі фігури, КРІМ тієї, яку ми перетягуємо
	for (int r = 0; r < Chess::Board::BOARD_SIZE; ++r)
	{
		for (int c = 0; c < Chess::Board::BOARD_SIZE; ++c)
		{
			Chess::Position currentPos = { r, c };
			const Chess::Piece* piece = m_gameLogic.getBoard().getPieceAt(currentPos);

			// Малюємо фігуру, тільки якщо вона не є тією, яку зараз тягнуть
			if (piece != nullptr && !(m_isDragging && currentPos == m_draggedPieceStartPos))
			{
				m_pieceRenderer.drawPiece(m_window, currentPos, piece); // Потрібно додати цей метод до PieceRenderer
			}
		}
	}

	// TODO: Малювання підсвічених можливих ходів (пізніше)
	// for (const auto& pos : m_highlightedMoves) {
	//     // Малюємо квадрат підсвічування
	// }

	// Якщо ми перетягуємо фігуру, малюємо її окремо на позиції курсору
	if (m_isDragging && m_draggedPiece != nullptr)
	{
		sf::Vector2i mousePixelPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f draggedPiecePixelPos = sf::Vector2f((float)mousePixelPos.x, (float)mousePixelPos.y) - m_mouseOffset;
		m_pieceRenderer.drawDraggedPiece(m_window, draggedPiecePixelPos, m_draggedPiece); // Потрібно додати цей метод до PieceRenderer
	}

	m_window.display();
}
