//
// Created by mateusz on 3/11/23.
//

#pragma once
#include "BasePiece.hpp"

namespace Chess {
class PieceView {
 public:
  explicit PieceView(BasePiece& piece);
  [[nodiscard]] PieceType getType() const;
  [[nodiscard]] Color getColor() const;
  [[nodiscard]] PieceInfo getInfo() const;
 private:
  BasePiece& m_piece;
};
}
