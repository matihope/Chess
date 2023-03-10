//
// Created by mateusz on 3/8/23.
//
#pragma once
#include "BasePiece.hpp"

namespace Chess {

class Pawn : public BasePiece {
 public:
  Pawn(Color color);
  ~Pawn() override;
  bool isMovePossible(Board &board, Position pos) override;
  bool moveIfPossible(Board &board, Position pos) override;
 private:
  bool m_has_moved;
};

}