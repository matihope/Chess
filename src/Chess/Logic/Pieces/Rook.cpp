//
// Created by mateusz on 3/12/23.
//

#include "Rook.hpp"
#include "Chess/Logic/Board.hpp"

bool Chess::Rook::_isMovePossible(Chess::Board &board, Chess::Position end_pos) {
  return wouldMoveBePossible(board, getPosition(), end_pos);
}

Chess::Rook::Rook(Chess::Color color) : BasePiece(color) {
  setType(PieceType::Rook);
}

bool Chess::Rook::wouldMoveBePossible(Chess::Board &board, Chess::Position start_pos, Chess::Position end_pos) {
  // horizontal move
  if (start_pos.file == end_pos.file) {
    for (unsigned int i = std::min(start_pos.rank, end_pos.rank) + 1; i < std::max(start_pos.rank, end_pos.rank); i++) {
      Position test_pos(end_pos.file, i);
      if (not board.isSquareEmpty(test_pos))
        return false;
    }
  }
  // vertical move
  if (start_pos.rank == end_pos.rank) {
    for (int i = std::min(start_pos.file, end_pos.file) + 1; i < std::max(start_pos.file, end_pos.file); i++) {
      Position test_pos(i, end_pos.rank);
      if (not board.isSquareEmpty(test_pos))
        return false;
    }
  }

  if (start_pos.rank != end_pos.rank and start_pos.file != end_pos.file)
    return false;
  return true;
}
