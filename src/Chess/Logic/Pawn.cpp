//
// Created by mateusz on 3/8/23.
//

#include "Pawn.hpp"

namespace Chess {

Pawn::Pawn(Color color) : BasePiece(color) {
  m_has_moved = false;
  setType(PieceType::Pawn);
}

Pawn::~Pawn() = default;

bool Pawn::isMovePossible(Board &board, Position pos) {
  Position my_pos = getPosition();
  if (my_pos.rank - 1 == pos.rank)
    return true;
  return false;
}

bool Pawn::moveIfPossible(Board &board, Position pos) {
  m_has_moved = true;
  return BasePiece::moveIfPossible(board, pos);
}

}
