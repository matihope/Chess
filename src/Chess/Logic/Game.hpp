//
// Created by mateusz on 3/11/23.
//

#pragma once

#include "Move.hpp"
#include "Board.hpp"
#include "Chess/Logic/Pieces/PieceView.hpp"

namespace Chess {
class Game {
 public:
  Game();
  void newGame();
  bool makeMove(Position start, Position end);
  std::vector<Move> getAvailableMovesAt(Position position);
  bool isMovePossible(Position start, Position end);
  bool isSquareEmpty(Position position);

  // return nullptr if square at pos doesn't have a piece
  // if square does have a piece, return a PieceView pointer
  std::unique_ptr<PieceView> getPieceAt(Position pos);
 private:
  Board m_board;
  Color m_turn;
  std::vector<Move> m_moves;
};
}
