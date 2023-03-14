//
// Created by mateusz on 3/14/23.
//

#pragma once
#include "WorldEntity/WorldEntity.hpp"

class SpriteBatch : public WorldEntity {
 public:
  SpriteBatch();
  void setSize(std::size_t size);
  void setSprite(unsigned int id, sf::Vector2f position, sf::Vector2f size);
 private:
  sf::VertexArray m_vertex_array;
};
