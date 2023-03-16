#include "BasePiece.hpp"
#include "Chess/Logic/Board.hpp"
#include "Chess/Logic/Square.hpp"

namespace Chess {

BasePiece::BasePiece(Color color) {
  setColor(color);
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

Position BasePiece::getPosition() {
  return getSquare()->getPosition();
}

std::vector<Position> BasePiece::getAvailableMoves(Board &board) {
  std::vector<Position> possible_moves;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      Position end_pos((char) (x + 'A'), y + 1);
      if (isMovePossible(board, end_pos)) {
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

Square *BasePiece::getSquare() {
  return m_my_square;
}

bool BasePiece::_canCapturePos(Board &board, Position end_pos) const {
  if (board.isSquareEmpty(end_pos)) return true;
//  if(board.getPieceAt(end_pos)->getType() == PieceType::King) return false;
  return getColor() != board.getPieceAt(end_pos)->getColor();
}

bool BasePiece::isMovePossible(Board &board, Position end_pos) {
  if (!_canCapturePos(board, end_pos))
    return false;
  return _isMovePossible(board, end_pos);
}

}  // namespace Chess
