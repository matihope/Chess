//
// Created by mateusz on 3/11/23.
//

#include "Move.hpp"

namespace Chess {

Move::Move(Position start, Position end, PieceInfo info) {
  m_start = start;
  m_end = end;
  m_info = info;
  m_has_captured_piece = false;
  m_captured_piece_info = {PieceType::Pawn, Color::White};
  m_captured_piece_position = Position('A', 1);
  m_captured_piece_move_count = 0;
  m_is_castling = false;
}

PieceInfo Move::getInfo() const {
  return m_info;
}

PieceType Move::getType() const {
  return m_info.type;
}

Color Move::getColor() const {
  return m_info.color;
}

Position Move::getStart() const {
  return m_start;
}

Position Move::getEnd() const {
  return m_end;
}

void Move::setCapturedPiece(PieceInfo piece_info, Position position, unsigned int move_count) {
  m_has_captured_piece = true;
  m_captured_piece_info = piece_info;
  m_captured_piece_position = position;
  m_captured_piece_move_count = move_count;
}

void Move::setCapturedPiece(const BasePiece &piece) {
  setCapturedPiece(piece.getInfo(), piece.getPosition(), piece.getMoveCount());
}

bool Move::hasCapturedPiece() const {
  return m_has_captured_piece;
}

PieceInfo Move::getCapturedPieceInfo() const {
  return m_captured_piece_info;
}

Position Move::getCapturedPiecePosition() const {
  return m_captured_piece_position;
}

unsigned int Move::getCapturedPieceMoveCount() const {
  return m_captured_piece_move_count;
}

bool Move::isCastling() const {
  return m_is_castling;
}

void Move::setCastling() {
  m_is_castling = true;
}

}
