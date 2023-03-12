//
// Created by mateusz on 3/12/23.
//

#pragma once
#include "BasePiece.hpp"

namespace Chess {

  class Rook : public BasePiece {
   public:
    Rook(Color color);
    bool isMovePossible(Board &board, Position position) override;

  };
}
