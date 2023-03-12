//
// Created by mateusz on 3/11/23.
//

#include <iostream>
#include "Tile.hpp"

Tile::Tile(Chess::Position position) : m_collision_shape(RectCollision(this)) {
  m_position = position;
  setClickCollisionShape(&m_collision_shape);
}

void Tile::setSize(float size) {
  m_collision_shape.setSize(size, size);
}

void Tile::onUpdate(float dt) {
  Clickable::update(dt);
}

void Tile::onRelease() {
//  std::cout << m_position << '\n';
}

void Tile::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();
  target.draw(m_collision_shape, states);
}

Chess::Position Tile::getPosition() {
  return m_position;
}
