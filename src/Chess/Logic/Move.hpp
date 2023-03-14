//
// Created by mateusz on 3/11/23.
//

#pragma once
#include "Position.hpp"
#include "Chess/Logic/Pieces/BasePiece.hpp"

namespace Chess {
class Move {
 private:
  Position m_start, m_end;
  PieceInfo m_info{};
 public:
  Move(Position start, Position end, PieceInfo info);
  [[nodiscard]] PieceType getType() const;
  [[nodiscard]] Color getColor() const;
  [[nodiscard]] PieceInfo getInfo() const;
  [[nodiscard]] Position getStart() const;
  [[nodiscard]] Position getEnd() const;
};
}
