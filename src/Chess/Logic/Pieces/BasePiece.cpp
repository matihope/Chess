#include <iostream>
#include "BasePiece.hpp"
#include "Chess/Logic/Board.hpp"
#include "Chess/Logic/Square.hpp"

namespace Chess {

BasePiece::BasePiece(Color color) {
  setColor(color);
  m_move_counter = 0;
}

void BasePiece::setType(PieceType type) {
  m_info.type = type;
}

PieceType BasePiece::getType() const {
  return m_info.type;
}

void BasePiece::setColor(Color color) {
  m_info.color = color;
}

Color BasePiece::getColor() const {
  return m_info.color;
}

Position BasePiece::getPosition() const {
  return getSquare()->getPosition();
}

std::vector<Position> BasePiece::getAvailableMoves(Board &board, const Move *last_move) {
  std::vector<Position> possible_moves;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      Position end_pos((char) (x + 'A'), y + 1);
      if (isMovePossible(board, end_pos, last_move)) {
        possible_moves.push_back(end_pos);
      }
    }
  }
  return possible_moves;
}

PieceInfo BasePiece::getInfo() const {
  return m_info;
}

void BasePiece::setSquare(Square *square) {
  m_my_square = square;
}

Square *BasePiece::getSquare() const {
  return m_my_square;
}

bool BasePiece::_canCapturePos(Board &board, Position end_pos) const {
  if (board.isSquareEmpty(end_pos)) return true;
  return getColor() != board.getPieceAt(end_pos)->getColor();
}

bool BasePiece::isMovePossible(Board &board, Position end_pos, const Move *last_move) {
  if (!_canCapturePos(board, end_pos))
    return false;
  return _isMovePossible(board, end_pos, last_move);
}

unsigned int BasePiece::getMoveCount() const {
  return m_move_counter;
}

void BasePiece::increaseMoveCounter() {
  m_move_counter++;
}

void BasePiece::decreaseMoveCounter() {
  if (m_move_counter)
    m_move_counter--;
}

void BasePiece::setMoveCounter(unsigned int new_moves_count) {
  m_move_counter = new_moves_count;
}

}  // namespace Chess
