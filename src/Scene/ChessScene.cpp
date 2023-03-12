
#include <ResourceManager/ResourceManager.hpp>
#include <Scene/ChessScene.hpp>
#include <Chess/BoardEntity.hpp>
#include <memory>
#include "Chess/Tile.hpp"
#include "Game/Game.hpp"

ChessScene::ChessScene() : WorldEntity() {
  auto board_ptr = std::make_unique<BoardEntity>(BOARD_SIZE, TILE_SIZE);
  m_board_entity = board_ptr.get();
  addChild(std::move(board_ptr));

  for(int x = 0; x < 8; ++x) {
    for(int y = 0; y < 8; ++y) {
      Chess::Position pos((char)('A' + x), y + 1);
      auto tile_ptr = std::make_unique<Tile>(pos);
      m_tiles[(y * BOARD_SIZE) + x] = tile_ptr.get();
      tile_ptr->setSize(TILE_SIZE);
      tile_ptr->setPosition(sf::Vector2f(TILE_SIZE * x, TILE_SIZE * (7-y)));
      addChild(std::move(tile_ptr));
    }
  }
}

void ChessScene::onUpdate(float dt) {
  updatePieces();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    m_chess_game.makeMove(Chess::Position('A', 2), Chess::Position('A', 3));
  }
  for(auto *tile: m_tiles) {
    if(tile->isPressed()) {
      auto available_moves = m_chess_game.getAvailableMovesAt(tile->getPosition());
      for(Chess::Move pos: available_moves) {
        std::cout << pos.getEnd() << '\n';
      }
    }
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
