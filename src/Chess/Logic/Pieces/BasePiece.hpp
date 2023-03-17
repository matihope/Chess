#pragma once

#include <vector>
#include "Chess/Logic/Position.hpp"

namespace Chess {

class Board;

class Square;

class Move;

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
  unsigned int m_move_counter;

 protected:
  // returns true if end_pos is free or has a piece of different color than getColor()
  bool _canCapturePos(Board &board, Position end_pos) const;

  // should implement the piece's regular behaviour
  // not king-check and other things, because they are checked in public isMovePossible
  virtual bool _isMovePossible(Board &board, Position end_pos, const Move *last_move) = 0;

 public:
  explicit BasePiece(Color color);
  virtual ~BasePiece() = default;
  void setType(PieceType type);
  [[nodiscard]] PieceType getType() const;
  void setColor(Color color);
  [[nodiscard]] Color getColor() const;
  [[nodiscard]] Position getPosition() const;
  void setSquare(Square *square);
  [[nodiscard]] Square *getSquare() const;
  void increaseMoveCounter();
  void decreaseMoveCounter();
  void setMoveCounter(unsigned int new_moves_count);
  [[nodiscard]] unsigned int getMoveCount() const;

  // returns all possible moves of the piece
  // last_move is the last move performed on the board = null if there were none
  std::vector<Position> getAvailableMoves(Board &board, const Move *last_move);
  // returns true if the piece can move to the end_pos
  // last_move is the last move performed on the board = null if there were none
  bool isMovePossible(Board &board, Position end_pos, const Move *last_move);

  [[nodiscard]] PieceInfo getInfo() const;
};
}  // namespace Chess
