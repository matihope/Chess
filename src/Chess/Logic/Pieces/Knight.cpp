//
// Created by mateusz on 3/13/23.
//

#include "Knight.hpp"

Chess::Knight::Knight(Chess::Color color) : BasePiece(color) {
  setType(PieceType::Knight);
}

bool Chess::Knight::_isMovePossible(Board &board, Position end_pos, const Move *last_move) {
  Position my_pos = getPosition();
  int x_diff = abs(my_pos.file - end_pos.file);
  int y_diff = abs(my_pos.rank - end_pos.rank);
  if ((x_diff == 1 and y_diff == 2) or (x_diff == 2 and y_diff == 1)) return true;
  return false;
}

Chess::Knight::~Knight() = default;
