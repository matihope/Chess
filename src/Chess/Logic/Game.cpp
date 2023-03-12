//
// Created by mateusz on 3/11/23.
//

#include "Game.hpp"

Chess::Game::Game() {
  newGame();
}

void Chess::Game::newGame() {
  m_moves.clear();
  m_turn = Color::White;
  m_board.reset();
}

void Chess::Game::makeMove(Chess::Position start, Chess::Position end) {
  BasePiece* piece_at_start = m_board.getPieceAt(start);

  // check if move is possible
  if(piece_at_start == nullptr)
    return;
  if(piece_at_start->getColor() != m_turn)
    return;
  if(!piece_at_start->isMovePossible(m_board, end))
    return;

  // swap turns
  if(m_turn == Color::White) {
    m_turn = Color::Black;
  } else {
    m_turn = Color::White;
  }

  // keep record of the moves
  m_moves.emplace_back(start, end, piece_at_start->getInfo());

  // apply move to the board
  m_board.getSquareAt(end)->popPiece();
  m_board.getSquareAt(end)->setPiece(m_board.getSquareAt(start)->popPiece());
}

std::unique_ptr<Chess::PieceView> Chess::Game::getPieceAt(Chess::Position pos) {
  BasePiece *piece = m_board.getPieceAt(pos);
  if(piece != nullptr)
    return std::make_unique<PieceView>(*piece);
  return nullptr;
}

bool Chess::Game::isMovePossible(Chess::Position start, Chess::Position end) {
  BasePiece *piece = m_board.getPieceAt(start);
  if(piece == nullptr)
      return false;

  return piece->isMovePossible(m_board, end);
}

std::vector<Chess::Move> Chess::Game::getAvailableMovesAt(Chess::Position position) {
  BasePiece *piece = m_board.getPieceAt(position);
  if(piece == nullptr)
    return {};

  std::vector<Move> possible_moves;
  for (const Position end_pos : piece->getAvailableMoves(m_board)) {
    possible_moves.emplace_back(position, end_pos, piece->getInfo());
  }
  return possible_moves;
}
