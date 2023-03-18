//
// Created by mateusz on 3/12/23.
//

#pragma once
#include "BasePiece.hpp"

namespace Chess {

class Rook : public BasePiece {
 public:
  explicit Rook(Color color);

  // last_move is here just to be consistent with piece's function arguments
  static bool wouldMoveBePossible(const Board &board, Position start_pos, Position end_pos, const Move *last_move);
 protected:
  bool _isMovePossible(const Board &board, Position end_pos, const Move *last_move) const override;

};
}
