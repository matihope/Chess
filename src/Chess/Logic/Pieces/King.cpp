//
// Created by mateusz on 3/15/23.
//

#include "King.hpp"

Chess::King::King(Chess::Color color) : BasePiece(color) {
  setType(PieceType::King);
}

bool Chess::King::_isMovePossible(Chess::Board &board, Chess::Position end_pos) {
  Position my_pos = getPosition();
  return abs(my_pos.file - end_pos.file) <= 1 and abs(my_pos.rank - end_pos.rank) <= 1;
}
