//
// Created by mateusz on 3/12/23.
//

#pragma once
#include "BasePiece.hpp"

namespace Chess {

class Rook : public BasePiece {
 public:
  explicit Rook(Color color);
 private:
  bool _isMovePossible(Board &board, Position end_pos) override;

};
}
