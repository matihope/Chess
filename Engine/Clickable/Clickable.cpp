#include "Clickable.hpp"

#include <Clickable/Clickable.hpp>
#include <Game/Game.hpp>

Clickable::Clickable() {
  m_is_held = false;
  m_was_held_prev = false;
  m_is_pressable = false;
  m_is_pressed = false;
  m_collision_shape = nullptr;
}

Clickable::~Clickable() = default;

void Clickable::update(float dt) {
  if (!m_collision_shape) return;
  sf::Vector2f mousePos = Game::get().getMousePos();
  m_is_held = false;

  if (m_collision_shape->contains(mousePos)) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (m_is_pressable) {
        m_is_held = true;
        onHold();
      }
    } else {
      m_is_pressable = true;
      if (m_was_held_prev) {
        m_is_pressed = true;
        onRelease();
      } else {
        onHover();
      }
    }
  } else {
    m_is_pressable = false;
    onNotHover();
  }
  m_was_held_prev = m_is_held;
}

void Clickable::setClickCollisionShape(CollisionComponent *collision_shape) {
  m_collision_shape = collision_shape;
}

bool Clickable::isPressed() const { return m_is_pressed; }
