
#include <ResourceManager/ResourceManager.hpp>
#include <Scene/ChessScene.hpp>
#include <Chess/BoardEntity.hpp>
#include <memory>

ChessScene::ChessScene() : WorldEntity() {
  auto board_ptr = std::make_unique<BoardEntity>(BOARD_SIZE, TILE_SIZE);
  m_board_entity = board_ptr.get();
  addChild(std::move(board_ptr));
}

void ChessScene::onUpdate(float dt) {
  updatePieces();
}

void ChessScene::updatePieces() {
  for (unsigned int x = 0; x < 8; x++) {
    for (unsigned int y = 0; y < 8; y++) {
      Chess::Position pos((char) ('A' + x), y + 1);
      Chess::BasePiece *piece = m_chess_board.getPieceAt(pos);
      if (piece == nullptr) {
        m_board_entity->clearSquare(pos);
      } else {
        m_board_entity->setPieceOnSquare(pos, piece->getType(), piece->getColor());
      }
    }
  }
}
