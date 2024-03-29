//
// Created by mateusz on 3/12/23.
//

#include "Rook.hpp"
#include "Chess/Logic/Board.hpp"

bool Chess::Rook::_isMovePossible(const Board &board, Position end_pos, const Move *last_move) const {
  return wouldMoveBePossible(board, getPosition(), end_pos, nullptr);
}

Chess::Rook::Rook(Chess::Color color) : BasePiece(color) {
  setType(PieceType::Rook);
}

bool Chess::Rook::wouldMoveBePossible(const Board &board, Position start_pos, Position end_pos, const Move *last_move) {
  // horizontal move
  if (start_pos.file == end_pos.file) {
    for (int i = std::min(start_pos.rank, end_pos.rank) + 1; i < std::max(start_pos.rank, end_pos.rank); i++) {
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
