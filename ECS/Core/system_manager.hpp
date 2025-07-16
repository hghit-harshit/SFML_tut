#pragma once
#include "s_base.hpp"
#include "../event_queue.hpp"
#include "../../Observer/message_handler.hpp"
#include "../../Window_System/window.hpp"
#include "entity_manager.hpp"

using SystemContainer = std::unordered_map<System,S_Base*>;
using EntityEventContainer = std::unordered_map<EntityId, EventQueue>;


class SystemManager
{
    public:
        SystemManager();
        ~SystemManager();

        void SetEntityManager(EntityManager* l_entityManager);
        EntityManager* GetEntityManager();
        MessageHandler* GetMessageHandler();

        template<typename T>
        T* GetSystem(const System& l_system)
        {
            auto itr = m_systems.find(l_system);
            if(itr == m_systems.end()) return nullptr;

            return dynamic_cast<T*>itr->second;
        }

        void AddEvent(const EntityId& l_entity, const EventId& l_event);

        void Update(float l_dt);
        void HandleEvents();
        void Draw(Window* l_wind, unsigned int l_elevation);

        void EntityModified(const EntityId& l_entity, const Bitmask& l_bits);
        void RemoveEntity(const EntityId& l_entity);

        void PurgeEntities();
        void PurgeSystems();

    private:
        SystemContainer m_systems;
        EntityManager* m_entityManager;
        EntityEventContainer m_events;
        MessageHandler m_messages;
};