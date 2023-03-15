//
// Created by mateusz on 3/15/23.
//

#include "Bishop.hpp"
#include "Chess/Logic/Board.hpp"

Chess::Bishop::Bishop(Chess::Color color) : BasePiece(color) {
  setType(PieceType::Bishop);
}

bool Chess::Bishop::_isMovePossible(Chess::Board &board, Chess::Position end_pos) {
  return wouldMoveBePossible(board, getPosition(), end_pos);
}

bool Chess::Bishop::wouldMoveBePossible(Chess::Board &board, Chess::Position start_pos, Chess::Position end_pos) {
  int diff_x = abs(end_pos.file - start_pos.file);
  int diff_y = abs(end_pos.rank - start_pos.rank);
  if(diff_x != diff_y)
    return false;

  int curr_x = start_pos.file;
  int curr_y = start_pos.rank;
  int dir_x = (start_pos.file < end_pos.file ? 1 : -1);
  int dir_y = (start_pos.rank < end_pos.rank ? 1 : -1);
  curr_x += dir_x;
  curr_y += dir_y;
  int end_x = end_pos.file;
  for(; abs(curr_x - end_x) > 0; curr_x += dir_x, curr_y += dir_y) {
    if(not board.isSquareEmpty(Position((char)curr_x, curr_y))) {
      return false;
    }
  }

  return true;
}
