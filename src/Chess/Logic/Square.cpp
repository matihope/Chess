//
// Created by mateusz on 3/8/23.
//

#include "Square.hpp"
#include "Board.hpp"

namespace Chess {

Square::Square() {
  m_piece = nullptr;
}

void Square::setPiece(std::unique_ptr<BasePiece> piece) {
  m_piece = std::move(piece);
  m_piece->setSquare(this);
}

BasePiece *Chess::Square::getPiece() const {
  if (m_piece)
    return m_piece.get();
  return nullptr;
}

void Square::setPosition(Chess::Position pos) {
  m_position = pos;
}

std::unique_ptr<BasePiece> Square::popPiece() {
  return std::move(m_piece);
}

Position Square::getPosition() const {
  return m_position;
}

bool Square::isSquareAttackedByColor(const Board &board, Color color) const {
  Position my_pos = getPosition();
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      const BasePiece *piece = board.getPieceAt((char) (x + 'A'), y + 1);
      if (piece == nullptr or piece->getColor() != color)
        continue;
      if (piece->isMovePossible(board, my_pos, nullptr))
        return true;
    }
  }
  return false;
}

}
