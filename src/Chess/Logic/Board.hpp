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
  void createNewPieceAt(Position position, PieceInfo piece_info, unsigned int move_count = 0);
  [[nodiscard]] const Square *getSquareAt(Position position) const;
  [[nodiscard]] const Square *getSquareAt(char file, uint rank) const;
  [[nodiscard]] const BasePiece *getPieceAt(Position position) const;
  [[nodiscard]] const BasePiece *getPieceAt(char file, uint rank) const;
  [[nodiscard]] Square *getSquareAt(Position position);
  [[nodiscard]] Square *getSquareAt(char file, uint rank);
  [[nodiscard]] BasePiece *getPieceAt(Position position);
  [[nodiscard]] BasePiece *getPieceAt(char file, uint rank);
  bool isSquareEmpty(Position position);

 private:
  std::array<std::array<Square, 8>, 8> m_board;
};
}  // namespace Chess
