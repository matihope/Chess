//
// Created by mateusz on 3/15/23.
//

#pragma once
#include "BasePiece.hpp"

namespace Chess{

class Queen : public BasePiece {
 public:
  explicit Queen(Color color);
  ~Queen() override = default;
 private:
  bool _isMovePossible(Board &board, Position end_pos) override;
};
}
