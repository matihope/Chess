#pragma once

#include <vector>
#include "Chess/Logic/Position.hpp"

namespace Chess {

class Board;

class Square;

enum class PieceType {
  King,
  Queen,
  Bishop,
  Knight,
  Rook,
  Pawn
};

enum class Color {
  White, Black
};

struct PieceInfo {
  PieceType type;
  Color color;
};

class BasePiece {
 private:
  PieceInfo m_info;
  Square *m_my_square;

 protected:
  // returns true if end_pos is free or has a piece of different color than getColor()
  bool _canCapturePos(Board &board, Position end_pos) const;

  // should implement the piece's regular behaviour
  // not king-check and other things, because they are checked in public wouldMoveBePossible
  virtual bool _isMovePossible(Board &board, Position end_pos) = 0;

 public:
  explicit BasePiece(Color color);
  virtual ~BasePiece() = default;
  void setType(PieceType type);
  [[nodiscard]] PieceType getType() const;
  void setColor(Color color);
  [[nodiscard]] Color getColor() const;
  Position getPosition();
  void setSquare(Square *square);
  Square *getSquare();

  // returns all possible moves of the piece
  std::vector<Position> getAvailableMoves(Board &board);
  // returns true if the piece can move to the end_pos
  bool isMovePossible(Board &board, Position end_pos);

  [[nodiscard]] PieceInfo getInfo() const;
};
}  // namespace Chess
