#include <Chess/GameOfChess.hpp>
#include <iostream>
#include "GameOfChess.hpp"

namespace Chess {
GameOfChess::GameOfChess() { reset(); }

void GameOfChess::reset() {
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

const PieceType& GameOfChess::getPieceAt(char file, int rank) {
    return getPieceAt(Chess::Square(file, rank));
}
const PieceType& GameOfChess::getPieceAt(Chess::Square pos) { return getMutPieceAt(pos); }

PieceType& GameOfChess::getMutPieceAt(char file, int rank) {
    return getMutPieceAt(Chess::Square(file, rank));
}

PieceType& GameOfChess::getMutPieceAt(Chess::Square pos) {
    return m_board[(pos.file - 'A') * 8 + pos.rank - 1];
}

std::vector<Chess::Square> GameOfChess::getAvailableMovesAt(Chess::Square pos) {
    return {Chess::Square('A', 3), Chess::Square('A', 4)};
}
}  // namespace Chess
