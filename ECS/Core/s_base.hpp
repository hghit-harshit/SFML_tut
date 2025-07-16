#pragma once
#include "entity_manager.hpp"
#include "../event_types.hpp"
#include "../../Observer/observer.hpp"
using EntityList = std::vector<EntityId>;
using Requirements = std::vector<Bitmask>;


class SystemManager;
class S_Base : public Observer
{
    public:
        S_Base(const System& l_id,SystemManager* l_systemManager);
        virtual ~S_Base();

        bool AddEntity(const EntityId& l_entity);
        bool HasEntity(const EntityId& l_entity);
        bool RemoveEntity(const EntityId& l_entity);

        System GetId();

        bool FitsRequirements(const Bitmask& l_bits);
        void Purge();

        virtual void Update(float l_dt) = 0;
        virtual void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) = 0;

    protected:
        System m_id;
        Requirements m_requiredComponents;
        EntityList m_entities;

        SystemManager* m_systemManager;
};
