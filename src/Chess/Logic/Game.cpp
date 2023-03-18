//
// Created by mateusz on 3/11/23.
//

#include "Game.hpp"
#include "Chess/Logic/Pieces/Rook.hpp"

Chess::Game::Game() {
  newGame();
}

void Chess::Game::newGame() {
  m_moves.clear();
  m_turn = Color::White;
  m_board.reset();
  m_white_king = m_board.getPieceAt('E', 1);
  m_black_king = m_board.getPieceAt('E', 8);
}

bool Chess::Game::makeMove(Chess::Position start, Chess::Position end) {
  const BasePiece *piece_at_start = m_board.getPieceAt(start);
  const Move *last_move = getLastMove();

  // check if move is possible
  if (piece_at_start == nullptr)
    return false;
  if (piece_at_start->getColor() != m_turn)
    return false;
  if (!piece_at_start->isMovePossible(m_board, end, last_move))
    return false;

  // swap turns
  _flipTurn();

  // for undo and redo
  if (not m_undid_moves.empty()) {
    // checks if a move we're trying to perform is different than would be done on redoMove()
    // if it's true, it clears undid_moves
    if (m_undid_moves.back().getStart() != start or m_undid_moves.back().getEnd() != end)
      m_undid_moves.clear();
  }

  // keep track of the moves
  m_moves.emplace_back(start, end, piece_at_start->getInfo());

  // apply move to the board
  auto captured_piece = _movePiece(start, end);
  m_board.getPieceAt(end)->increaseMoveCounter();

  // check if a piece just has done an en-passant
  if (piece_at_start->getType() == PieceType::Pawn and captured_piece == nullptr) {
    int diff_x = abs(end.file - start.file);
    int diff_y = abs(end.rank - start.rank);
    if (diff_x == 1 and diff_y == 1) {
      captured_piece = m_board.getSquareAt(end.file, start.rank)->popPiece();
    }
  }

  // save captured piece's info
  if (captured_piece != nullptr)
    m_moves.back().setCapturedPiece(*captured_piece);

  // if a pawn reaches the end, it becomes a queen
  PieceInfo piece_info = m_board.getSquareAt(end)->getPiece()->getInfo();
  if (piece_info.type == PieceType::Pawn) {
    if ((end.rank == 8 and piece_info.color == Color::White) or (piece_info.color == Color::Black and end.rank == 1)) {
      // and don't forget to set it's correct move count
      auto prev_move_count = m_board.getSquareAt(end)->popPiece()->getMoveCount();
      m_board.createNewPieceAt(end, {PieceType::Queen, piece_info.color});
      m_board.getPieceAt(end)->setMoveCounter(prev_move_count);
    }
  }

  // if a king has just castled, then move a rook as well
  if (piece_at_start->getType() == PieceType::King) {
    if (abs(start.file - end.file) == 2) {
      // we are performing a castling
      Position rook_start, rook_end;
      if (end.file == 'C') {
        rook_start = {'A', end.rank};
        rook_end = {'D', end.rank};
      } else {
        rook_start = {'H', end.rank};
        rook_end = {'F', end.rank};
      }
      _movePiece(rook_start, rook_end);
      m_board.getPieceAt(rook_end)->increaseMoveCounter();
      m_moves.back().setCastling();
    }
  }

  if (isKingChecked(piece_info.color)) {
    undoLastMove();
    // so that the move is not tracked in the history
    m_undid_moves.pop_back();
    return false;
  }

  return true;
}

const Chess::BasePiece *Chess::Game::getPieceAt(Chess::Position pos) const {
  return m_board.getPieceAt(pos);
}

bool Chess::Game::isMovePossible(Chess::Position start, Chess::Position end) {
  BasePiece *piece = m_board.getPieceAt(start);
  if (piece == nullptr)
    return false;

  return piece->isMovePossible(m_board, end, getLastMove());
}

std::vector<Chess::Move> Chess::Game::getAvailableMovesAt(Chess::Position position) {
  BasePiece *piece = m_board.getPieceAt(position);
  if (piece == nullptr)
    return {};

  if (piece->getColor() != m_turn)
    return {};

  std::vector<Move> possible_moves;
  for (const Position end_pos : piece->getAvailableMoves(m_board, getLastMove())) {
    if (isMoveKingSafe(position, end_pos))
      possible_moves.emplace_back(position, end_pos, piece->getInfo());
  }
  return possible_moves;
}

bool Chess::Game::isSquareEmpty(Chess::Position position) {
  return getPieceAt(position) == nullptr;
}

bool Chess::Game::undoLastMove() {
  if (m_moves.empty())
    return false;
  auto last_move = m_moves.back();
  m_undid_moves.push_back(last_move);
  m_moves.pop_back();

  if (last_move.isCastling()) {
    if (last_move.getEnd().file == 'C' or last_move.getEnd().file == 'G') {
      auto end = last_move.getEnd();
      Position rook_start, rook_end;
      if (end.file == 'C') {
        rook_start = {'D', end.rank};
        rook_end = {'A', end.rank};
      } else {
        rook_start = {'F', end.rank};
        rook_end = {'H', end.rank};
      }
      _movePiece(rook_start, rook_end);
      m_board.getPieceAt(rook_end)->decreaseMoveCounter();
    }
  }

  _movePiece(last_move.getEnd(), last_move.getStart());
  m_board.getPieceAt(last_move.getStart())->decreaseMoveCounter();

  // possibly a pawn turning into a queen
  if (last_move.getType() == PieceType::Pawn) {
    if (last_move.getEnd().rank == 1 or last_move.getEnd().rank == 8) {
      // it did turn into a queen
      auto move_count = m_board.getSquareAt(last_move.getStart())->popPiece()->getMoveCount();
      m_board.createNewPieceAt(last_move.getStart(), last_move.getInfo(), move_count);
    }
  }
  if (last_move.hasCapturedPiece())
    m_board.createNewPieceAt(last_move.getCapturedPiecePosition(),
                             last_move.getCapturedPieceInfo(),
                             last_move.getCapturedPieceMoveCount());

  _flipTurn();
  return true;
}

const Chess::Move *Chess::Game::getLastMove() const {
  if (m_moves.empty())
    return nullptr;
  return &m_moves.back();
}

bool Chess::Game::redoLastMove() {
  if (m_undid_moves.empty())
    return false;
  auto last_undid_move = m_undid_moves.back();
  makeMove(last_undid_move.getStart(), last_undid_move.getEnd());
  m_undid_moves.pop_back();
  return true;
}

void Chess::Game::_flipTurn() {
  if (m_turn == Color::White) {
    m_turn = Color::Black;
  } else {
    m_turn = Color::White;
  }
}

bool Chess::Game::isMoveKingSafe(Chess::Position start, Chess::Position end) {
  // there is a king at end position
  if (not m_board.isSquareEmpty(end))
    if (m_board.getPieceAt(end)->getType() == PieceType::King)
      return false;

  if (!makeMove(start, end))
    return false;

  undoLastMove();
  m_undid_moves.pop_back();

  return true;
}

std::unique_ptr<Chess::BasePiece> Chess::Game::_movePiece(Chess::Position start, Chess::Position end) {
  auto captured_piece = m_board.getSquareAt(end)->popPiece();
  m_board.getSquareAt(end)->setPiece(m_board.getSquareAt(start)->popPiece());
  return captured_piece;
}

bool Chess::Game::isKingChecked(Chess::Color kingsColor) {
  if (kingsColor == Color::White) {
    return m_board.getSquareAt(m_white_king->getPosition())->isSquareAttackedByColor(m_board, Color::Black);
  } else {
    return m_board.getSquareAt(m_black_king->getPosition())->isSquareAttackedByColor(m_board, Color::White);
  }
}
