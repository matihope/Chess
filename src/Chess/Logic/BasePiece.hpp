#pragma once

#include <vector>
#include "Position.hpp"

namespace Chess {

class Board;

enum class PieceType {
  King,
  Queen,
  Bishop,
  Knight,
  Rook,
  Pawn
};

enum class Color {
  Black, White
};

class BasePiece {
 private:
  PieceType m_type;
  Color m_color;
  Position m_position;

 public:
  BasePiece(Color color);
  virtual ~BasePiece() = default;
  void setType(PieceType type);
  PieceType getType() const;
  void setColor(Color color);
  Color getColor() const;

  Position getPosition();

  // returns all possible moves of the piece
  std::vector<Position> getAvailableMoves(Board &board);
  // returns true if the piece can move to the position
  virtual bool isMovePossible(Board &board, Position position) = 0;
  // returns true if the piece has successfully moved to the position
  virtual bool moveIfPossible(Board &board, Position position);

};
}  // namespace Chess
