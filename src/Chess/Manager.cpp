#include <Chess/Manager.hpp>
#include <iostream>

namespace Chess {
Manager::Manager() { reset(); }

void Manager::reset() {
    // empty the board
    m_board.fill(PieceType::Empty);

    // fill pawns
    for (int i = 0; i < 8; i++) {
        getMutPieceAt('A' + i, 2) = PieceType::WhitePawn;
        getMutPieceAt('A' + i, 7) = PieceType::BlackPawn;
    }

    getMutPieceAt('A', 1) = getMutPieceAt('H', 1) = PieceType::WhiteRook;
    getMutPieceAt('A', 8) = getMutPieceAt('H', 8) = PieceType::BlackRook;
    getMutPieceAt('B', 1) = getMutPieceAt('G', 1) = PieceType::WhiteKnight;
    getMutPieceAt('B', 8) = getMutPieceAt('G', 8) = PieceType::BlackKnight;
    getMutPieceAt('C', 1) = getMutPieceAt('F', 1) = PieceType::WhiteBishop;
    getMutPieceAt('C', 8) = getMutPieceAt('F', 8) = PieceType::BlackBishop;
    getMutPieceAt('D', 1) = PieceType::WhiteQueen;
    getMutPieceAt('D', 8) = PieceType::BlackQueen;
    getMutPieceAt('E', 1) = PieceType::WhiteKing;
    getMutPieceAt('E', 8) = PieceType::BlackKing;
}

const PieceType& Manager::getPieceAt(char file, int rank) { return getMutPieceAt(file, rank); }
PieceType& Manager::getMutPieceAt(char file, int rank) {
    return m_board[(file - 'A') * 8 + rank - 1];
}

}  // namespace Chess
