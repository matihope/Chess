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

bool Pawn::isMovePossible(Board &board, Position end_pos) {
  Position my_pos = getPosition();
  if(getColor() == Color::White)
    if (my_pos.file == end_pos.file && my_pos.rank + 1 == end_pos.rank)
      return true;

  return false;
}

}
