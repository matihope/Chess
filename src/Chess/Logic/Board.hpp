#pragma once

#include <array>
#include "Square.hpp"
#include "Position.hpp"
#include "Move.hpp"

namespace Chess {
class Board {
 public:
  Board();
  void reset();
  [[nodiscard]] Square *getSquareAt(Position pos);
  [[nodiscard]] Square *getSquareAt(char file, uint rank);
  [[nodiscard]] BasePiece *getPieceAt(Position pos);
  [[nodiscard]] BasePiece *getPieceAt(char file, uint rank);
  bool isSquareEmpty(Position pos);

 private:
  std::array<std::array<Square, 8>, 8> m_board;
};
}  // namespace Chess
