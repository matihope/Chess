//
// Created by mateusz on 3/10/23.
//

#pragma once
#include <WorldEntity/WorldEntity.hpp>
#include "Chess/Logic/Pieces/BasePiece.hpp"
#include <GUI/Label.hpp>
#include <array>
#include "SpriteBatch/SpriteBatch.hpp"

enum SquareHighlightMode {
  Default = 0b0,

};

class BoardEntity : public WorldEntity {
 public:
  BoardEntity(int BOARD_SIZE, float TILE_SIZE);
  void setPieceOnSquare(Chess::Position position, Chess::PieceType type, Chess::Color color);
  void clearSquare(Chess::Position position);
  void pressSquare(Chess::Position position, bool press);
  void clearPress();
  void highlightSquare(Chess::Position position);
  void clearHighlight();
  // level=0 - clear, level=1 - regular available move dot, level=2 - circle around (around a piece)
  void markSquare(Chess::Position position, unsigned int level);
  void clearMark();

  // sets square's color and other visuals to default
  void setSquaresDefaultColors();

 private:
  // board - tiles, pieces - pieces, highlight - a square around
  // pressed - color of tile after click or move, mark - available moves
  SpriteBatch *m_board_batch, *m_pieces_batch, *m_highlight_batch, *m_pressed_batch, *m_mark_batch;
  std::array<GUI::Label *, 16> m_labels{};
  const int BOARD_SIZE;
  const float TILE_SIZE;
  QuickSprite getPiecesSpriteAt(Chess::Position position);
  std::pair<unsigned int, unsigned int> getArrayCoords(Chess::Position position);
  unsigned int getArrayIndex(Chess::Position position);
};
