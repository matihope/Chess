//
// Created by mateusz on 3/8/23.
//

#include "Square.hpp"

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

}
