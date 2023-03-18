//
// Created by mateusz on 3/11/23.
//

#pragma once

#include "Move.hpp"
#include "Board.hpp"

namespace Chess {
class Game {
 public:
  Game();
  void newGame();
  std::vector<Chess::Position> getAvailableMovesAt(Position position);
  bool isMovePossible(Position start, Position end);
  bool isSquareEmpty(Position position);
  [[nodiscard]] const Move *getLastMove() const;

  // makes move if possible, then clears m_undid_moves if new move is different than m_undid_moves.back()
  bool makeMove(Position start, Position end);

  // pops top element from m_moves, also undoes the last move
  // and adds it to m_undid_moves for method redoLastMove() to use
  bool undoLastMove();

  // redoes the move from top of m_undid_moves stack
  bool redoLastMove();

  // returns true if after move from start to end start's color king will not be checked
  // does not assume piece's ability to move
  bool isMoveKingSafe(Position start, Position end);

  bool isKingChecked(Color kingsColor);

  // return nullptr if square at pos doesn't have a piece
  // if square does have a piece, return a PieceView pointer
  [[nodiscard]] const BasePiece *getPieceAt(Position pos) const;
 private:
  Board m_board;
  Color m_turn;
  std::vector<Move> m_moves;
  std::vector<Move> m_undid_moves;
  void _flipTurn();

  Chess::BasePiece *m_white_king, *m_black_king;

  // doesn't make any checks, assumes everything is correct and tries to move a piece
  // return a pointer to a to_be_destroyed piece
  std::unique_ptr<Chess::BasePiece> _movePiece(Position start, Position end);
};
}
