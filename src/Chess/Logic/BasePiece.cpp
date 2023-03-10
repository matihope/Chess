#include "BasePiece.hpp"
#include "Board.hpp"

namespace Chess {

BasePiece::BasePiece(Color color) {
  m_color = color;
}

void BasePiece::setType(PieceType type) {
  m_type = type;
}

PieceType BasePiece::getType() const {
  return m_type;
}

void BasePiece::setColor(Color color) {
  m_color = color;
}

Color BasePiece::getColor() const {
  return m_color;
}

Position BasePiece::getPosition() {
  return m_position;
}

bool BasePiece::moveIfPossible(Board &board, Position position) {
  if (isMovePossible(board, position)) {
    m_position = position;
    Square *my_square = board.getSquareAt(getPosition());
    Square *future_square = board.getSquareAt(position);
    std::unique_ptr<BasePiece> self_pointer = my_square->popPiece();
    future_square->setPiece(std::move(self_pointer));
    return true;
  }
  return false;
}

std::vector<Position> BasePiece::getAvailableMoves(Board &board) {
  std::vector<Position> possible_moves;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Position pos((char) (i + 'A'), j);
      if (isMovePossible(board, pos)) {
        possible_moves.push_back(pos);
      }
    }
  }
  return possible_moves;
}

}  // namespace Chess
