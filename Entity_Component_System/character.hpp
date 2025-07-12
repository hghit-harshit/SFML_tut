#pragma once

#include "entity_base.hpp"

class Character: public EntityBase
{
    friend EntityManager;

    public:
        Character(EntityManager* l_entityMgr);
        virtual ~Character();
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
        
};
