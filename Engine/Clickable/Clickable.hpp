#pragma once
#include <WorldEntity/WorldEntity.hpp>
#include <CollisionComponent/CollisionComponent.hpp>
#include <memory>

class Clickable : public WorldEntity {
    std::unique_ptr<CollisionComponent> m_collision_shape;

   public:
    Clickable();
    virtual ~Clickable() = 0;
};
