//
// Created by mateusz on 3/8/23.
//

#include "Pawn.hpp"
#include "Board.hpp"

namespace Chess {

Pawn::Pawn(Color color) : BasePiece(color) {
  setType(PieceType::Pawn);
}

Pawn::~Pawn() = default;

bool Pawn::isMovePossible(Board &board, Position end_pos) {
  Position my_pos = getPosition();

  // double move
  if (getColor() == Color::White and my_pos.rank == 2) {
    if (end_pos.rank == 4 and board.isSquareEmpty(end_pos)) {
      return true;
    }
  }
  if (getColor() == Color::Black and my_pos.rank == 7) {
    if (end_pos.rank == 5 and board.isSquareEmpty(end_pos)) {
      return true;
    }
  }
  if (getColor() == Color::White)
    if (my_pos.file == end_pos.file && my_pos.rank + 1 == end_pos.rank)
      return true;
  if (getColor() == Color::Black)
    if (my_pos.file == end_pos.file && my_pos.rank - 1 == end_pos.rank)
      return true;
  return false;
}

}
