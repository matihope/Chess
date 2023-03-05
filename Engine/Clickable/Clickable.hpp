#pragma once
#include <CollisionComponent/CollisionComponent.hpp>
#include <Updatable/Updatable.hpp>
#include <memory>

class Clickable : public Updatable {
    CollisionComponent* m_collision_shape;
    bool m_is_held;
    bool m_is_pressable;
    bool m_was_held_prev;
    bool m_is_pressed;

   protected:
    virtual void selfHovered() {}; // hovering mouse over button
    virtual void selfNotHovered() {};
    virtual void selfHeld() {};  // function called during holding
    virtual void selfReleased() {};

   public:
    Clickable();
    virtual ~Clickable() = 0;
    bool isPressed() const;
    void update(float dt) override;
    void setClickCollisionShape(CollisionComponent* collision_shape);
};
