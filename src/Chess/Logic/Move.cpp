//
// Created by mateusz on 3/11/23.
//

#include "Move.hpp"

namespace Chess {

Move::Move(Position start, Position end, PieceInfo info) {
  m_start = start;
  m_end = end;
  m_info = info;
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

}
