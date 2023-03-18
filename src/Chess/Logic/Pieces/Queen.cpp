//
// Created by mateusz on 3/15/23.
//

#include "Queen.hpp"
#include "Chess/Logic/Board.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"

Chess::Queen::Queen(Chess::Color color) : BasePiece(color) {
  setType(PieceType::Queen);
}

bool Chess::Queen::_isMovePossible(const Board &board, Position end_pos, const Move *last_move) const {
  Position my_pos = getPosition();
  return Bishop::wouldMoveBePossible(board, my_pos, end_pos) or Rook::wouldMoveBePossible(board,
                                                                                          my_pos,
                                                                                          end_pos,
                                                                                          nullptr);
}
