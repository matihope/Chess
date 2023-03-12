//
// Created by mateusz on 3/12/23.
//

#include "Rook.hpp"

bool Chess::Rook::isMovePossible(Chess::Board &board, Chess::Position position) {
  return true;
}

Chess::Rook::Rook(Chess::Color color) : BasePiece(color) {
  setType(PieceType::Rook);
}
