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
        WorldEntity* m_parent;

       public:
        WorldEntity();
        virtual ~WorldEntity();

        EntityID getId() const;

        void queueFree();
        const bool& isDying() const;

        std::map<uint, std::list<std::unique_ptr<WorldEntity>>> m_entity_pool;

       public:
        void addParent(WorldEntity* parent);
        WorldEntity* getParent();
        virtual void cleanEntities();
        virtual void update(const float dt);
        virtual void physicsUpdate(const float dt);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void addChild(std::unique_ptr<WorldEntity> entity, unsigned int drawOrder = 0);
        virtual void handleEvent(const sf::Event& event){};
};
