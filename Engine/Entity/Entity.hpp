#pragma once
#include <Updatable/Updatable.hpp>
#include <CollisionComponent/CollisionComponent.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <AnimatedSprite/AnimatedSprite.hpp>

class Entity : public WorldEntity {
 protected:
  CollisionComponent *m_collision_shape;
  AnimatedSprite m_animation;
  sf::Sprite m_shadow;

 public:
  void update(float dt) override;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};
