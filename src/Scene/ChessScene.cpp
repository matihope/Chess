
#include <ResourceManager/ResourceManager.hpp>
#include <Scene/ChessScene.hpp>
#include <Chess/BoardEntity.hpp>
#include <memory>
#include "Chess/Tile.hpp"
#include "Game/Game.hpp"

ChessScene::ChessScene() : WorldEntity() {
  auto board_ptr = std::make_unique<BoardEntity>(BOARD_SIZE, TILE_SIZE);
  m_piece_is_floating = false;
  m_board_entity = board_ptr.get();
  addChild(std::move(board_ptr));

  auto floating_piece_ptr = std::make_unique<FloatingPiece>(TILE_SIZE);
  m_floating_piece = floating_piece_ptr.get();
  m_floating_piece->hide();
  addChild(std::move(floating_piece_ptr));

  for(int x = 0; x < 8; ++x) {
    for(int y = 0; y < 8; ++y) {
      Chess::Position pos((char)('A' + x), y + 1);
      auto tile_ptr = std::make_unique<Tile>(pos);
      m_tiles[(y * BOARD_SIZE) + x] = tile_ptr.get();
      tile_ptr->setSize(TILE_SIZE);
      tile_ptr->setPosition(sf::Vector2f(TILE_SIZE * (float)x, TILE_SIZE * (float)(7-y)));
      addChild(std::move(tile_ptr));
    }
  }
  updatePieces();
}

void ChessScene::onUpdate(float dt) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    m_chess_game.makeMove(Chess::Position('A', 2), Chess::Position('A', 3));
    updatePieces();
  }
  for(auto *tile: m_tiles) {
    if(tile->isPressed()) {
      updatePieces();
      m_board_entity->clearSquare(tile->getPosition());
      m_floating_piece->setPieceInfo(m_chess_game.getPieceAt(tile->getPosition())->getInfo());
      m_piece_is_floating = true;
    }
  }
  if(m_piece_is_floating and not sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    updatePieces();
    m_piece_is_floating = false;
    m_floating_piece->hide();
  }
  if(m_piece_is_floating) {
    m_floating_piece->show();
    m_floating_piece->setPosition(Game::get().getMousePos());
  }
}

void ChessScene::updatePieces() {
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
