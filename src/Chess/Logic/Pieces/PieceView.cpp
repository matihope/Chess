//
// Created by mateusz on 3/11/23.
//

#include "PieceView.hpp"

Chess::PieceView::PieceView(Chess::BasePiece &piece) : m_piece(piece) {

}

Chess::PieceType Chess::PieceView::getType() const {
  return m_piece.getType();
}

Chess::Color Chess::PieceView::getColor() const {
  return m_piece.getColor();
}

Chess::PieceInfo Chess::PieceView::getInfo() const {
  return m_piece.getInfo();
}
