#include "Board.hpp"
#include "Position.hpp"
#include "Chess/Logic/Pieces/Pawn.hpp"
#include "Chess/Logic/Pieces/Rook.hpp"
#include "Chess/Logic/Pieces/Knight.hpp"

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
    auto pawn1 = std::make_unique<Pawn>(Color::White);
    auto pawn2 = std::make_unique<Pawn>(Color::Black);
    getSquareAt((char) ('A' + i), 2)->setPiece(std::move(pawn1));
    getSquareAt((char) ('A' + i), 7)->setPiece(std::move(pawn2));
  }
  auto white_rook1 = std::make_unique<Rook>(Color::White);
  auto white_rook2 = std::make_unique<Rook>(Color::White);
  getSquareAt(Position('A', 1))->setPiece(std::move(white_rook1));
  getSquareAt(Position('H', 1))->setPiece(std::move(white_rook2));

  auto black_rook1 = std::make_unique<Rook>(Color::Black);
  auto black_rook2 = std::make_unique<Rook>(Color::Black);
  getSquareAt(Position('A', 8))->setPiece(std::move(black_rook1));
  getSquareAt(Position('H', 8))->setPiece(std::move(black_rook2));

  auto white_knight1 = std::make_unique<Knight>(Color::White);
  auto white_knight2 = std::make_unique<Knight>(Color::White);
  getSquareAt(Position('B', 1))->setPiece(std::move(white_knight1));
  getSquareAt(Position('G', 1))->setPiece(std::move(white_knight2));

  auto black_knight1 = std::make_unique<Knight>(Color::Black);
  auto black_knight2 = std::make_unique<Knight>(Color::Black);
  getSquareAt(Position('B', 8))->setPiece(std::move(black_knight1));
  getSquareAt(Position('G', 8))->setPiece(std::move(black_knight2));


//  getMutPieceAt('A', 1) = getMutPieceAt('H', 1) = PieceType::WhiteRook;
//  getMutPieceAt('A', 8) = getMutPieceAt('H', 8) = PieceType::BlackRook;
//  getMutPieceAt('B', 1) = getMutPieceAt('G', 1) = PieceType::WhiteKnight;
//  getMutPieceAt('B', 8) = getMutPieceAt('G', 8) = PieceType::BlackKnight;
//  getMutPieceAt('C', 1) = getMutPieceAt('F', 1) = PieceType::WhiteBishop;
//  getMutPieceAt('C', 8) = getMutPieceAt('F', 8) = PieceType::BlackBishop;
//  getMutPieceAt('D', 1) = PieceType::WhiteQueen;
//  getMutPieceAt('D', 8) = PieceType::BlackQueen;
//  getMutPieceAt('E', 1) = PieceType::WhiteKing;
//  getMutPieceAt('E', 8) = PieceType::BlackKing;

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
