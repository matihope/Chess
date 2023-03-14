#pragma once
#include <GUI/GUI.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <vector>
#include <Chess/Logic/Board.hpp>
#include "Chess/Logic/Pieces/BasePiece.hpp"
#include <Chess/BoardEntity.hpp>
#include <Chess/Logic/Game.hpp>
#include "Chess/Tile.hpp"
#include "Chess/FloatingPiece.hpp"

class ChessScene : public WorldEntity {
 public:
  ChessScene();
 private:
  void updatePieces();
  Chess::Game m_chess_game;
  BoardEntity *m_board_entity;
  const int BOARD_SIZE = 8;
  const float TILE_SIZE = 100.;
  void onUpdate(float dt) override;
  std::array<Tile *, 64> m_tiles;
  bool m_piece_is_floating;
  FloatingPiece *m_floating_piece;
  Chess::Position m_held_piece_position;
};
