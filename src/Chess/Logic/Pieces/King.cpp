//
// Created by mateusz on 3/15/23.
//

#include "King.hpp"
#include "Chess/Logic/Board.hpp"

Chess::King::King(Chess::Color color) : BasePiece(color) {
  setType(PieceType::King);
}

bool Chess::King::_isMovePossible(const Board &board, Position end_pos, const Move *last_move) const {
  Position my_pos = getPosition();

  // regular move
  if (abs(my_pos.file - end_pos.file) <= 1 and abs(my_pos.rank - end_pos.rank) <= 1)
    return true;

  // possibly a castling
  if (getMoveCount() != 0 or end_pos.rank != my_pos.rank)
    return false;

  // check for attacks
  const BasePiece *rook1 = board.getPieceAt('A', my_pos.rank);
  const BasePiece *rook2 = board.getPieceAt('H', my_pos.rank);
  if (end_pos.file == 'C' and rook1->getMoveCount() != 0)
    return false;
  if (end_pos.file == 'G' and rook2->getMoveCount() != 0)
    return false;
  if (end_pos.file != 'C' and end_pos.file != 'G')
    return false;

  // check if any square along the route is attacked or not
  int dir_x = (my_pos.file < end_pos.file ? 1 : -1);
  Color enemy_color = (getColor() == Color::White ? Color::Black : Color::White);
  for (char x = my_pos.file; x != end_pos.file; x += dir_x) {
    Position pos = Position(x, my_pos.rank);
    if (board.getSquareAt(pos)->isSquareAttackedByColor(board, enemy_color)) {
      return false;
    }
  }

  return true;

}
