//
// Created by mateusz on 3/15/23.
//

#pragma once
#include "BasePiece.hpp"

namespace Chess {

class Bishop : public BasePiece {
 public:
  explicit Bishop(Color color);
  static bool wouldMoveBePossible(const Board &board, Position start_pos, Position end_pos);
 private:
  bool _isMovePossible(const Board &board, Position end_pos, const Move *last_move) const override;
};
}
