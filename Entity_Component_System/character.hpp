#pragma once

#include "entity_base.hpp"
#include "../Sprite_System/direction.hpp"
#include "../Sprite_System/sprite_sheet.hpp"
#include "entity_types.hpp"
class Character: public EntityBase
{
    friend EntityManager;

    public:
        Character(EntityManager* l_entityMgr);
        virtual ~Character(){};
        void Move(const Direction& l_dir);
        void Jump();
        void Attack();
        void GetHurt(const int& l_damage);
        void Load(const std::string& l_path);
        virtual void OnEntityCollision(EntityBase* l_collider, bool l_attack) = 0;
        virtual void Update(float l_dt);
        void Draw(sf::RenderWindow* l_window);

    protected:
        void UpdateAttackAABB();
        void Animate();
        SpriteSheet m_spriteSheet;
        float m_jumpVelocity;
        int m_hitpoints;
        sf::FloatRect m_attackAABB;
        sf::Vector2f m_attackAABBoffSet;
        
};
