#include "Board.hpp"
#include "Position.hpp"
#include "Chess/Logic/Pieces/Pawn.hpp"
#include "Chess/Logic/Pieces/Rook.hpp"
#include "Chess/Logic/Pieces/Knight.hpp"
#include "Chess/Logic/Pieces/Bishop.hpp"
#include "Chess/Logic/Pieces/Queen.hpp"
#include "Chess/Logic/Pieces/King.hpp"

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
    createNewPieceAt({(char) ('A' + i), 2}, {PieceType::Pawn, Color::White});
    createNewPieceAt({(char) ('A' + i), 7}, {PieceType::Pawn, Color::Black});
  }

  // rooks
  createNewPieceAt({'A', 1}, {PieceType::Rook, Color::White});
  createNewPieceAt({'H', 1}, {PieceType::Rook, Color::White});
  createNewPieceAt({'A', 8}, {PieceType::Rook, Color::Black});
  createNewPieceAt({'H', 8}, {PieceType::Rook, Color::Black});

  // knights
  createNewPieceAt({'B', 1}, {PieceType::Knight, Color::White});
  createNewPieceAt({'G', 1}, {PieceType::Knight, Color::White});
  createNewPieceAt({'B', 8}, {PieceType::Knight, Color::Black});
  createNewPieceAt({'G', 8}, {PieceType::Knight, Color::Black});

  // bishops
  createNewPieceAt({'C', 1}, {PieceType::Bishop, Color::White});
  createNewPieceAt({'F', 1}, {PieceType::Bishop, Color::White});
  createNewPieceAt({'C', 8}, {PieceType::Bishop, Color::Black});
  createNewPieceAt({'F', 8}, {PieceType::Bishop, Color::Black});

  // queens
  createNewPieceAt({'D', 1}, {PieceType::Queen, Color::White});
  createNewPieceAt({'D', 8}, {PieceType::Queen, Color::Black});

  // kings
  createNewPieceAt({'E', 1}, {PieceType::King, Color::White});
  createNewPieceAt({'E', 8}, {PieceType::King, Color::Black});
}

const Square *Board::getSquareAt(Position position) const {
  return getSquareAt(position.file, position.rank);
}

const Square *Board::getSquareAt(char file, uint rank) const {
  return &m_board[8 - rank][(std::size_t) (file - 'A')];
}

const BasePiece *Board::getPieceAt(Position position) const {
  return getPieceAt(position.file, position.rank);
}

const BasePiece *Board::getPieceAt(char file, uint rank) const {
  return getSquareAt(file, rank)->getPiece();
}

Square *Board::getSquareAt(char file, uint rank) {
  return &m_board[8 - rank][(std::size_t) (file - 'A')];
}

BasePiece *Board::getPieceAt(Position position) {
  return getSquareAt(position)->getPiece();
}

BasePiece *Board::getPieceAt(char file, uint rank) {
  return getSquareAt(file, rank)->getPiece();
}

Square *Board::getSquareAt(Position position) {
  return getSquareAt(position.file, position.rank);
}

bool Board::isSquareEmpty(Position position) const {
  return getSquareAt(position)->getPiece() == nullptr;
}

void Board::createNewPieceAt(Position position, PieceInfo piece_info, unsigned int move_count) {
  auto [type, color] = piece_info;
  switch (type) {
    case PieceType::King: getSquareAt(position)->setPiece(std::make_unique<King>(color));
      break;
    case PieceType::Queen: getSquareAt(position)->setPiece(std::make_unique<Queen>(color));
      break;
    case PieceType::Bishop: getSquareAt(position)->setPiece(std::make_unique<Bishop>(color));
      break;
    case PieceType::Knight: getSquareAt(position)->setPiece(std::make_unique<Knight>(color));
      break;
    case PieceType::Rook: getSquareAt(position)->setPiece(std::make_unique<Rook>(color));
      break;
    case PieceType::Pawn: getSquareAt(position)->setPiece(std::make_unique<Pawn>(color));
      break;
  }
  getPieceAt(position)->setMoveCounter(move_count);
}

}  // namespace Chess
