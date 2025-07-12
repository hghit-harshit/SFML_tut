#pragma once
#include <SFML/Graphics.hpp>
#include "entity_types.hpp"
#include "../Map_System/tile.hpp"
#include "../Map_System/map.hpp"
#include "entity_manager.hpp"
#include "../shared_context.hpp"

class EntityManager;

struct CollisionElement
{
    CollisionElement(float l_area, TileInfo* l_info,
    const sf::FloatRect& l_bounds):m_area(l_area),
    m_tile(l_info),m_tileBounds(l_bounds)
    {}

    float m_area;
    TileInfo* m_tile;
    sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionElement>;
bool SortCollisions(const CollisionElement& l_1, const CollisionElement& l_2);


class EntityBase
{
    friend class EntityManager;
    public:
        EntityBase(EntityManager* l_entityMgr);
        virtual ~EntityBase();

        void SetPosition(const float& l_x, const float& l_y);
        void SetPosition(const sf::Vector2f& l_pos);
        void SetSize(const float& l_x, const float& l_y);
        void SetState(const EntityState& l_state);
        
        std::string GetName();
        unsigned int GetId();
        EntityType GetType();
        
        void Move(float l_x, float l_y);
        void AddVelocity(float l_x, float l_y);
        void Accelerate(float l_x, float l_y);
        void SetAcceleration(float l_x, float l_y);
        void ApplyFriction(float l_x, float l_y);
        virtual void Update(float l_dt);
        virtual void Draw(sf::RenderWindow* l_wind) = 0;
    
    protected:
        void UpdateAABB();
        void CheckCollisions();
        void ResolveCollision();

        virtual void OnEntityCollision(EntityBase* l_collider, bool l_attack) = 0;

        // Data members
        std::string m_name;
        EntityType m_type;
        unsigned int m_id; // Entity in the entity manager
        sf::Vector2f m_position;
        sf::Vector2f m_positionOld; // position before entity moved
        sf::Vector2f m_velocity;
        sf::Vector2f m_maxVelocity;
        sf::Vector2f m_speed; //(?) value of acceleration
        sf::Vector2f m_acceleration;
        sf::Vector2f m_friction;
        TileInfo* m_referenceTile; // tile underneath entity
        sf::Vector2f m_size; // size of collision box
        sf::FloatRect m_AABB;// the collision bounding box
        EntityState m_state;

        //flag for remembering collisions
        bool m_collidingOnX;
        bool m_collidingOnY;

        Collisions m_collisions;
        EntityManager* m_entityManager;
};
