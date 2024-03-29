//
// Created by mateusz on 3/8/23.
//
#pragma once
#include "BasePiece.hpp"

namespace Chess {

class Pawn : public BasePiece {
 public:
  explicit Pawn(Color color);
 private:
  bool _isMovePossible(const Board &board, Position end_pos, const Move *last_move) const override;
};

}
