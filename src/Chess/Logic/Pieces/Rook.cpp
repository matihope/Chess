//
// Created by mateusz on 3/12/23.
//

#include "Rook.hpp"
#include "Chess/Logic/Board.hpp"

bool Chess::Rook::_isMovePossible(Chess::Board &board, Chess::Position end_pos) {
  Position my_pos = getPosition();

  // horizontal move
  if (my_pos.file == end_pos.file) {
    for (int i = std::min(my_pos.rank, end_pos.rank) + 1; i < std::max(my_pos.rank, end_pos.rank); i++) {
      Position test_pos(end_pos.file, i);
      if (not board.isSquareEmpty(test_pos))
        return false;
    }
  }
  if (my_pos.rank == end_pos.rank) {
    for (int i = std::min(my_pos.file, end_pos.file) + 1; i < std::max(my_pos.file, end_pos.file); i++) {
      Position test_pos(i, end_pos.rank);
      if (not board.isSquareEmpty(test_pos))
        return false;
    }
  }

  if (my_pos.rank != end_pos.rank and my_pos.file != end_pos.file)
    return false;
  return true;
}

Chess::Rook::Rook(Chess::Color color) : BasePiece(color) {
  setType(PieceType::Rook);
}
