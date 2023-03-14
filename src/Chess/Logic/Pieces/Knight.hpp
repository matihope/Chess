//
// Created by mateusz on 3/13/23.
//

#pragma once
#include "BasePiece.hpp"

namespace Chess {
class Knight : public BasePiece {
 public:
  explicit Knight(Color color);
  ~Knight() override;
 private:
  bool _isMovePossible(Board &board, Position end_pos) override;
};
}
