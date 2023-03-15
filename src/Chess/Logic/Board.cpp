#include "Board.hpp"
#include "Position.hpp"
#include "Chess/Logic/Pieces/Pawn.hpp"
#include "Chess/Logic/Pieces/Rook.hpp"
#include "Chess/Logic/Pieces/Knight.hpp"
#include "Chess/Logic/Pieces/Bishop.hpp"
#include "Chess/Logic/Pieces/Queen.hpp"

namespace Chess {
Board::Board() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Position pos((char) ('A' + i), j + 1);
      getSquareAt(pos)->setPosition(pos);
    }
  }
  reset();
}

void Board::reset() {
  // fill pawns
  for (int i = 0; i < 8; i++) {
    getSquareAt((char) ('A' + i), 2)->setPiece(std::make_unique<Pawn>(Color::White));
    getSquareAt((char) ('A' + i), 7)->setPiece(std::make_unique<Pawn>(Color::Black));
  }

  // rooks
  getSquareAt(Position('A', 1))->setPiece(std::make_unique<Rook>(Color::White));
  getSquareAt(Position('H', 1))->setPiece(std::make_unique<Rook>(Color::White));
  getSquareAt(Position('A', 8))->setPiece(std::make_unique<Rook>(Color::Black));
  getSquareAt(Position('H', 8))->setPiece(std::make_unique<Rook>(Color::Black));

  // knights
  getSquareAt(Position('B', 1))->setPiece(std::make_unique<Knight>(Color::White));
  getSquareAt(Position('G', 1))->setPiece(std::make_unique<Knight>(Color::White));
  getSquareAt(Position('B', 8))->setPiece(std::make_unique<Knight>(Color::Black));
  getSquareAt(Position('G', 8))->setPiece(std::make_unique<Knight>(Color::Black));

  // bishops
  getSquareAt(Position('C', 1))->setPiece(std::make_unique<Bishop>(Color::White));
  getSquareAt(Position('F', 1))->setPiece(std::make_unique<Bishop>(Color::White));
  getSquareAt(Position('C', 8))->setPiece(std::make_unique<Bishop>(Color::Black));
  getSquareAt(Position('F', 8))->setPiece(std::make_unique<Bishop>(Color::Black));

  // queens
  getSquareAt(Position('D', 1))->setPiece(std::make_unique<Queen>(Color::White));
  getSquareAt(Position('D', 8))->setPiece(std::make_unique<Queen>(Color::Black));

}

Square *Board::getSquareAt(Position pos) {
  return getSquareAt(pos.file, pos.rank);
}

Square *Board::getSquareAt(char file, uint rank) {
  return &m_board[8 - rank][(std::size_t) (file - 'A')];
}

BasePiece *Board::getPieceAt(Position pos) {
  return getPieceAt(pos.file, pos.rank);
}

BasePiece *Board::getPieceAt(char file, uint rank) {
  return getSquareAt(file, rank)->getPiece();
}

bool Board::isSquareEmpty(Position pos) {
  return getSquareAt(pos)->getPiece() == nullptr;
}

}  // namespace Chess
