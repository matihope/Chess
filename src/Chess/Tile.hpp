//
// Created by mateusz on 3/11/23.
//

#pragma once
#include "WorldEntity/WorldEntity.hpp"
#include "Clickable/Clickable.hpp"
#include "CollisionShape/CollisionShape.hpp"
#include "Chess/Logic/Position.hpp"

class Tile : public WorldEntity, public Clickable {
 public:
  explicit Tile(Chess::Position position);
  void setSize(float size);
  void onUpdate(float dt) override;
  void onRelease() override;
  void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;
  Chess::Position getPosition();
 private:
  Chess::Position m_position;
  RectCollision m_collision_shape;
};
