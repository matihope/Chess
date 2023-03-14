//
// Created by mateusz on 3/12/23.
//

#pragma once

#include "Chess/Logic/Pieces/BasePiece.hpp"
#include "WorldEntity/WorldEntity.hpp"

class FloatingPiece : public WorldEntity {
 public:
  FloatingPiece(float tile_size);
  void setPieceInfo(Chess::PieceInfo piece_info);
  void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
 private:
  Chess::PieceInfo m_piece_info;
  sf::Sprite m_sprite;
  float m_tile_size;
};
