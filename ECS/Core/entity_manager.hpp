#pragma once
#include "c_base.hpp"
#include "../bitmask.hpp"
#include "../../Resource_System/texture_manager.hpp"
#include <unordered_map>
#include <functional>
#include <vector>

using EntityId = unsigned int;

using ComponentContainer = std::vector<C_Base*>;
using EntityData = std::pair<Bitmask,ComponentContainer>;
using EntityContainer = std::unordered_map<EntityId,EntityData>;
using ComponentFactory = std::unordered_map<Component,std::function<C_Base*(void)>>;

class SystemManager;
class EntityManager
{
    public:
        EntityManager(SystemManager* l_systemManager,TextureManager* l_textureManager);
        ~EntityManager();

        int AddEntity(const Bitmask& l_mask);// l_mask will tell what kind of component it has
        int AddEntity(const std::string& l_entityFile);
        bool RemoveEntity(const EntityId& l_id);

        bool AddCompenent(const EntityId& l_entity,const Component& l_component);

        template<typename T>
        T* GetComponent(const EntityId& l_entity, const Component& l_component)
        {
            auto itr = m_entities.find(l_entity);
            if(itr == m_entities.end()) return nullptr;
            //Entity found
            // now checking if it has the bit set for the compenent
            if(!itr->second.first.GetBit((unsigned int)l_component)) return nullptr;
            //component exists
            auto& container = itr->second.second;
            auto component = std::find_if(container.begin,container.end(),
            [&l_component](C_Base* C)
            {
                return C->GetType() == l_component;
            });

            return (component != conainer.end() ? dynamic_cast<T*>(*component) : nullptr);
            
        }

        bool RemoveComponent(const EntityId& l_entity, const Component& l_component);
        bool HasComponent(const EntityId& l_entity, const Component& l_component);

        void Purge();


    private:
        template<typename T>
        void AddComponentType(const Component& l_id)
        {
            m_cFactory[l_id] = []()->C_Base*
            { return new T();};
        }

        unsigned int m_idCounter;
        EntityContainer m_entities;
        ComponentFactory m_cFactory;

        SystemManager* m_systems;
        TextureManager* m_textureManager;
};