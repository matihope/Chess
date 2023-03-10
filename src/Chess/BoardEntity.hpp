//
// Created by mateusz on 3/10/23.
//

#pragma once
#include <WorldEntity/WorldEntity.hpp>
#include <Chess/Logic/BasePiece.hpp>
#include <GUI/Label.hpp>
#include <array>

class BoardEntity : public WorldEntity {
 public:
  BoardEntity(int BOARD_SIZE, float TILE_SIZE);
  void setPieceOnSquare(Chess::Position position, Chess::PieceType type, Chess::Color color);
  void clearSquare(Chess::Position position);
  void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  std::array<GUI::Label, 16> m_labels;
  const int BOARD_SIZE;
  const float TILE_SIZE;
  const sf::Texture *m_board_texture;
  const sf::Texture *m_pieces_texture;
  sf::VertexArray m_board_vertices;
  sf::VertexArray m_pieces_vertices;
  void setQuadPieceTexCoords(sf::Vertex *quad, Chess::PieceType type, Chess::Color color);
  sf::Vertex *getPiecesQuadAt(Chess::Position position);
};
