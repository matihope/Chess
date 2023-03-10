#pragma once
#include <GUI/GUI.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <vector>
#include <Chess/Logic/Board.hpp>
#include <Chess/Logic/BasePiece.hpp>
#include <Chess/BoardEntity.hpp>

class ChessScene : public WorldEntity {
 public:
  ChessScene();
 private:
  void updatePieces();
  Chess::Board m_chess_board;
  BoardEntity *m_board_entity;
  const int BOARD_SIZE = 8;
  const float TILE_SIZE = 100.;

  void onUpdate(float dt) override;
};
