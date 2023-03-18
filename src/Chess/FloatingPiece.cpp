//
// Created by mateusz on 3/12/23.
//

#include "FloatingPiece.hpp"
#include "ResourceManager/ResourceManager.hpp"

FloatingPiece::FloatingPiece(float tile_size) : WorldEntity() {
  m_tile_size = tile_size;
  m_sprite.setTexture(ResourceManager::get().getTexture("../resources/chess_pieces.png"));
  setPieceInfo({Chess::PieceType::Pawn, Chess::Color::White});
}

void FloatingPiece::setPieceInfo(Chess::PieceInfo piece_info) {
  m_piece_info = piece_info;
  auto [tex_x, tex_y] = m_sprite.getTexture()->getSize();
  float x = (float) piece_info.type * tex_x / 6.f;
  float y = (float) piece_info.color * tex_y / 2.f;
  m_sprite.setTextureRect(sf::IntRect(x, y, tex_x / 6.f, tex_y / 2.f));
  m_sprite.setScale(m_tile_size / tex_x * 6.f, m_tile_size / tex_y * 2.f);
  m_sprite.setOrigin(tex_x / 12.f, tex_y / 4.f);
}

void FloatingPiece::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
  sf::RenderStates new_states;
  new_states.transform *= getTransform();
  target.draw(m_sprite, new_states);
}
