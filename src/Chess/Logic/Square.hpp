//
// Created by mateusz on 3/8/23.
//

#pragma once
#include <memory>
#include "BasePiece.hpp"
#include "Position.hpp"

namespace Chess {

class Square {
 public:
  Square();
  void setPosition(Position pos);
  std::unique_ptr<BasePiece> popPiece();
  // sets m_piece to piece
  void setPiece(std::unique_ptr<BasePiece> piece);
  BasePiece *getPiece();

 private:
  std::unique_ptr<BasePiece> m_piece;
  Position m_position;
};
}
