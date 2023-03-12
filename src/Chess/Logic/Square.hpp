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
  Position getPosition();
  // sets m_piece to nullptr and returns last piece
  std::unique_ptr<BasePiece> popPiece();
  void setPiece(std::unique_ptr<BasePiece> piece);
  BasePiece *getPiece();

 private:
  std::unique_ptr<BasePiece> m_piece;
  Position m_position;
};
}
