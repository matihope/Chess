
#include <ResourceManager/ResourceManager.hpp>
#include "Scenes/ChessScene.hpp"
#include <Chess/BoardEntity.hpp>
#include <memory>
#include "Chess/Tile.hpp"
#include "Game/Game.hpp"

ChessScene::ChessScene() : WorldEntity() {
  // create board representation
  auto board_ptr = std::make_unique<BoardEntity>(BOARD_SIZE, TILE_SIZE);
  m_piece_is_floating = false;
  m_board_entity = board_ptr.get();
  addChild(std::move(board_ptr));

  // create floating piece
  auto floating_piece_ptr = std::make_unique<FloatingPiece>(TILE_SIZE);
  m_floating_piece = floating_piece_ptr.get();
  m_floating_piece->hide();
  addChild(std::move(floating_piece_ptr));

  // load clicky tiles
  for (int x = 0; x < 8; ++x) {
    for (int y = 0; y < 8; ++y) {
      Chess::Position pos((char) ('A' + x), y + 1);
      auto tile_ptr = std::make_unique<Tile>(pos);
      m_tiles[(y * BOARD_SIZE) + x] = tile_ptr.get();
      tile_ptr->setSize(TILE_SIZE);
      tile_ptr->setPosition(sf::Vector2f(TILE_SIZE * (float) x, TILE_SIZE * (float) (7 - y)));
      addChild(std::move(tile_ptr));
    }
  }
  reloadBoardPieces();
}

void ChessScene::onUpdate(float dt) {

  for (auto *tile : m_tiles) {
    if (tile->isPressed()) {
      Chess::Position position = tile->getPosition();
      bool made_a_move = m_chess_game.makeMove(m_held_piece_position, position);
      if (not made_a_move and not m_chess_game.isSquareEmpty(position)) {
        // mark available moves
        m_board_entity->clearMark();
        for (auto move : m_chess_game.getAvailableMovesAt(position)) {
          m_board_entity->markSquare(move.getEnd(), 1);
          if (not m_chess_game.isSquareEmpty(move.getEnd()))
            m_board_entity->markSquare(move.getEnd(), 2);

        }
        // start dragging a piece
        reloadBoardPieces();
        m_board_entity->clearSquare(position);
        m_floating_piece->setPieceInfo(m_chess_game.getPieceAt(position)->getInfo());
        m_piece_is_floating = true;
        if (not m_chess_game.isSquareEmpty(m_held_piece_position))
          m_board_entity->pressSquare(m_held_piece_position, false);
        m_board_entity->pressSquare(position, true);
        m_held_piece_position = position;
      } else {
        // move to click spot
        if (made_a_move) {
          m_board_entity->clearPress();
          m_board_entity->clearMark();
          m_board_entity->pressSquare(m_held_piece_position, true);
          m_board_entity->pressSquare(tile->getPosition(), true);

          reloadBoardPieces();
        }
      }
    }
  }

  // on piece drop
  if (m_piece_is_floating and not sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    reloadBoardPieces();
    sf::Vector2f mouse_pos = Game::get().getMousePos();
    m_board_entity->clearHighlight();
    m_piece_is_floating = false;
    m_floating_piece->hide();
    // find correct tile
    for (auto tile : m_tiles) {
      if (tile->contains(mouse_pos)) {
        Chess::Position end_pos = tile->getPosition();
        bool made_a_move = m_chess_game.makeMove(m_held_piece_position, end_pos);
        if (made_a_move) {
          m_board_entity->clearPress();
          m_board_entity->clearMark();
          m_board_entity->pressSquare(m_held_piece_position, true);
          m_board_entity->pressSquare(end_pos, true);
          reloadBoardPieces();
        }
        break;
      }
    }
  }

  // update floating piece's position
  if (m_piece_is_floating) {
    m_floating_piece->show();
    m_floating_piece->setPosition(Game::get().getMousePos());
    sf::Vector2f mouse_pos = Game::get().getMousePos();
    // find tile to highlight
    m_board_entity->clearHighlight();
    for (auto tile : m_tiles) {
      if (tile->contains(mouse_pos)) {
        m_board_entity->highlightSquare(tile->getPosition());
      }
    }
  }
}

void ChessScene::reloadBoardPieces() {
  for (unsigned int x = 0; x < 8; x++) {
    for (unsigned int y = 0; y < 8; y++) {
      Chess::Position pos((char) ('A' + x), y + 1);
      std::unique_ptr<Chess::PieceView> piece_view = m_chess_game.getPieceAt(pos);
      if (piece_view == nullptr) {
        m_board_entity->clearSquare(pos);
      } else {
        m_board_entity->setPieceOnSquare(pos, piece_view->getType(), piece_view->getColor());
      }
    }
  }
}
