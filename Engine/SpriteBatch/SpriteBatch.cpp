//
// Created by mateusz on 3/14/23.
//

#include "SpriteBatch.hpp"

SpriteBatch::SpriteBatch() : WorldEntity() {
  m_vertex_array.setPrimitiveType(sf::Quads);
}

void SpriteBatch::setSize(std::size_t size) {
  m_vertex_array.resize(size * 4);
}

void SpriteBatch::setSprite(unsigned int id, sf::Vector2f position, sf::Vector2f size) {
  
}
