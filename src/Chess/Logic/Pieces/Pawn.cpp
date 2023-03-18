//
// Created by mateusz on 3/8/23.
//

#include "Pawn.hpp"
#include "Chess/Logic/Board.hpp"

namespace Chess {

Pawn::Pawn(Color color) : BasePiece(color) {
  setType(PieceType::Pawn);
}

bool Pawn::_isMovePossible(const Board &board, Position end_pos, const Move *last_move) const {
  Position my_pos = getPosition();
  Color color = getColor();

  int diff_x = abs(end_pos.file - my_pos.file);
  int diff_y = abs(end_pos.rank - my_pos.rank);

  // direction of move
  int walk_dir;
  if (color == Color::White)
    walk_dir = 1;
  else
    walk_dir = -1;

  // double move
  if (getMoveCount() == 0 and diff_x == 0 and diff_y == 2) {
    if (board.isSquareEmpty(end_pos) and my_pos.rank + 2 * walk_dir == end_pos.rank)
      return true;
  }

  // anything passed this comment is some kind of a move forward
  if (my_pos.rank + walk_dir != end_pos.rank)
    return false;

  // capturing
  if (not board.isSquareEmpty(end_pos) and diff_x == 1)
    return true;

  // en-passant
  if (last_move != nullptr) {
    if (last_move->getType() == PieceType::Pawn) {
      if (abs(last_move->getStart().rank - last_move->getEnd().rank) == 2) {
        int en_passant_y = (last_move->getStart().rank + last_move->getEnd().rank) / 2;
        if (end_pos.rank == en_passant_y and end_pos.file == last_move->getEnd().file)
          return true;
      }
    }
  }

  // regular forward move
  if (not board.isSquareEmpty(end_pos))
    return false;
  if (diff_x == 0)
    return true;
  return false;
}

}
