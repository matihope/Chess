#pragma once
#include <CollisionComponent/CollisionComponent.hpp>
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <list>
#include <map>
#include <memory>

typedef unsigned long long EntityID;

class WorldEntity : public sf::Drawable, public sf::Transformable, public Updatable {
 private:
  static EntityID id_counter;
  EntityID m_entityId;

  bool m_toKill = false;
  WorldEntity *m_parent;

  bool m_show;

 public:
  WorldEntity();
  ~WorldEntity() override = default;

  EntityID getId() const;

  void queueFree();
  const bool &isDying() const;

  std::map<uint, std::list<std::unique_ptr<WorldEntity>>> m_entity_pool;

  void addParent(WorldEntity *parent);
  WorldEntity *getParent();

  void addChild(std::unique_ptr<WorldEntity> entity, unsigned int drawOrder = 0);
  virtual void cleanEntities();
  void update(float dt) override;
  void physicsUpdate(float dt) override;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  virtual void onUpdate(float dt) {};

  virtual void onPhysicsUpdate(float dt) {};

  virtual void onDraw(sf::RenderTarget &target, sf::RenderStates states) const {};

  virtual void handleEvent(const sf::Event &event) {};

  void show();
  void hide();
};
