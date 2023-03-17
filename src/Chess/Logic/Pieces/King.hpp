//
// Created by mateusz on 3/15/23.
//

#pragma once
#include "BasePiece.hpp"

namespace Chess {

class King : public BasePiece {
 public:
  explicit King(Color color);
 private:
  bool _isMovePossible(Board &board, Position end_pos, const Move *last_move) override;
};
}
