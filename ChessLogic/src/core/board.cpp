#include "board.h"
#include "utils/piece_factory.h"

#include <iostream>

using namespace Chess;

Board::Board() {
    clear();
    std::cout << "Board object created." << std::endl;
}

void Board::clear() {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            m_squares[r][c] = nullptr;
        }
    }
}

void Board::initializeBoard() {
    clear();
    setPieceAt({ 0, 0 }, PieceFactory::createPiece(PieceType::Rook, Color::White));
    setPieceAt({ 0, 1 }, PieceFactory::createPiece(PieceType::Knight, Color::White));
    setPieceAt({ 0, 2 }, PieceFactory::createPiece(PieceType::Bishop, Color::White));
    setPieceAt({ 0, 3 }, PieceFactory::createPiece(PieceType::Queen, Color::White));
    setPieceAt({ 0, 4 }, PieceFactory::createPiece(PieceType::King, Color::White));
    setPieceAt({ 0, 5 }, PieceFactory::createPiece(PieceType::Bishop, Color::White));
    setPieceAt({ 0, 6 }, PieceFactory::createPiece(PieceType::Knight, Color::White));
    setPieceAt({ 0, 7 }, PieceFactory::createPiece(PieceType::Rook, Color::White));
    for (int c = 0; c < BOARD_SIZE; ++c) {
        setPieceAt({ 1, c }, PieceFactory::createPiece(PieceType::Pawn, Color::White));
    }

    setPieceAt({ 7, 0 }, PieceFactory::createPiece(PieceType::Rook, Color::Black));
    setPieceAt({ 7, 1 }, PieceFactory::createPiece(PieceType::Knight, Color::Black));
    setPieceAt({ 7, 2 }, PieceFactory::createPiece(PieceType::Bishop, Color::Black));
    setPieceAt({ 7, 3 }, PieceFactory::createPiece(PieceType::Queen, Color::Black));
    setPieceAt({ 7, 4 }, PieceFactory::createPiece(PieceType::King, Color::Black));
    setPieceAt({ 7, 5 }, PieceFactory::createPiece(PieceType::Bishop, Color::Black));
    setPieceAt({ 7, 6 }, PieceFactory::createPiece(PieceType::Knight, Color::Black));
    setPieceAt({ 7, 7 }, PieceFactory::createPiece(PieceType::Rook, Color::Black));
    for (int c = 0; c < BOARD_SIZE; ++c) {
        setPieceAt({ 6, c }, PieceFactory::createPiece(PieceType::Pawn, Color::Black));
    }
}

const Piece* Board::getPieceAt(Position pos) const {
    if (!isPositionValid(pos))
        return nullptr;
    return m_squares[pos.row][pos.col].get();
}

void Board::setPieceAt(Position pos, std::unique_ptr<Piece> piece) {
    if (!isPositionValid(pos)) {
        // log error;
        return;
    }
    m_squares[pos.row][pos.col] = std::move(piece);
}

std::unique_ptr<Piece> Board::removePieceAt(Position pos) {
    if (!isPositionValid(pos))
        return nullptr;
    std::unique_ptr<Piece> removedPiece = std::move(m_squares[pos.row][pos.col]);
    m_squares[pos.row][pos.col] = nullptr;
    return removedPiece;
}

void Board::movePiece(Position from, Position to) {
    if (!isPositionValid(from) || !isPositionValid(to)) {
        // Log error
        return;
    }
    if (m_squares[from.row][from.col] == nullptr) {
        // Log error
        return;
    }

    if (from == to) {
        // Log error
        return;
    }

    m_squares[to.row][to.col] = std::move(m_squares[from.row][from.col]);
    m_squares[from.row][from.col] = nullptr;

    if (m_squares[to.row][to.col] != nullptr) {
        m_squares[to.row][to.col]->setHasMoved(true);
    }
}

bool Board::isPositionValid(Position pos) const
{
    return pos.row < BOARD_SIZE && pos.col < BOARD_SIZE && pos.row >= 0 && pos.col >= 0;
}

bool Board::isSquareEmpty(Position pos) const {
    return getPieceAt(pos) == nullptr;
}

void Board::printBoard() const {
    std::cout << "   a b c d e f g h" << std::endl;
    std::cout << " +-----------------" << std::endl;
    for (int r = BOARD_SIZE - 1; r >= 0; --r) {
        std::cout << r + 1 << "|";
        for (int c = 0; c < BOARD_SIZE; ++c) {
            const Piece* piece = getPieceAt({ r, c });
            if (piece == nullptr) {
                std::cout << " *";
            }
            else {
                char symbol;
                switch (piece->getType()) {
                case PieceType::Pawn: symbol = 'p'; break;
                case PieceType::Knight: symbol = 'n'; break;
                case PieceType::Bishop: symbol = 'b'; break;
                case PieceType::Rook: symbol = 'r'; break;
                case PieceType::Queen: symbol = 'q'; break;
                case PieceType::King: symbol = 'k'; break;
                default: symbol = '?'; break;
                }
                if (piece->isWhite()) {
                    symbol = toupper(symbol);
                }
                std::cout << " " << symbol;
            }
        }
        std::cout << std::endl;
    }
    std::cout << " +-----------------" << std::endl;
    std::cout << "   a b c d e f g h" << std::endl;
}
