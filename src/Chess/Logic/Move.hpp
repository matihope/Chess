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
  bool m_has_captured_piece;
  PieceInfo m_captured_piece_info;
  Position m_captured_piece_position;
  unsigned int m_captured_piece_move_count;
 public:
  Move(Position start, Position end, PieceInfo info);
  [[nodiscard]] PieceType getType() const;
  [[nodiscard]] Color getColor() const;
  [[nodiscard]] PieceInfo getInfo() const;
  [[nodiscard]] Position getStart() const;
  [[nodiscard]] Position getEnd() const;
  // move_count is the number of moves a captured piece has done before being captured
  void setCapturedPiece(PieceInfo piece_info, Position position, unsigned int move_count);
  void setCapturedPiece(const BasePiece &piece);
  [[nodiscard]] PieceInfo getCapturedPieceInfo() const;
  [[nodiscard]] Position getCapturedPiecePosition() const;
  [[nodiscard]] bool hasCapturedPiece() const;
  [[nodiscard]] unsigned int getCapturedPieceMoveCount() const;
};
}
