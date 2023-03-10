#pragma once

#include <array>
#include "Square.hpp"
#include "Position.hpp"

namespace Chess {
class Board {
  std::array<std::array<Square, 8>, 8> m_board;

 public:
  Board();
  void reset();
  Square *getSquareAt(Position pos);
  Square *getSquareAt(char file, uint rank);
  BasePiece *getPieceAt(Position pos);
  BasePiece *getPieceAt(char file, uint rank);

};
}  // namespace Chess
