#include "entity_manager.hpp"
#include "../Components/c_position.hpp"
//#include "../Components/c_drawable.hpp"
#include "../Components/c_spritesheet.hpp"
#include "bitmask.hpp"
#include <fstream>
EntityManager::EntityManager(SystemManager* l_systemManager, TextureManager* l_textureManager)
:m_textureManager(l_textureManager),m_systems(l_systemManager),m_idCounter(0)
{
    AddComponentType<C_Position>(Component::Position);
    AddComponentType<C_SpriteSheet>(Component::SpriteSheet);
}


EntityManager::~EntityManager(){Purge();}

int EntityManager::AddEntity(const Bitmask& l_mask)
{
    unsigned int entity = m_idCounter;
    if(!m_entities.emplace(entity,EntityData(0,ComponentContainer())).second)
    { return -1 ;}

    ++m_idCounter;

    for(unsigned int i = 0; i < N_COMPOENT_TYPES; ++i)
    {
        if(l_mask.GetBit(i))
        {
            AddCompenent(entity,(Component)i);
        }
    }

    // we notify the system manager that we modifiend an entity
    // m_systems->EntityModified(entity,l_mask);
    // m_systems->AddEvent(entity,(EventId)EntitEvent::Spawned);

    return entity;
}

bool EntityManager::RemoveEntity(const EntityId& l_id)
{
    auto itr = m_entities.find(l_id);
    if(itr == m_entities.end()) return false;

    while(itr->second.second.begin() != itr->second.second.end())
    {
        delete itr->second.second.back();
        itr->second.second.pop_back();
    }

    m_entities.erase(itr);
    //m_systems->RemoveEntity(l_id);
    return true;
}


bool EntityManager::AddCompenent(const EntityId& l_entity, const Component& l_component)
{
    auto itr = m_entities.find(l_entity);
    if(itr == m_entities.end()) return false;

    if(itr->second.first.GetBit((unsigned int)l_component)) return false;
    // ^^^component is already present

    //component doesnt exists

    auto itr2 = m_cFactory.find(l_component);
    if(itr2 == m_cFactory.end()) return false;
    // component types does exist

    C_Base* component = itr2->second();
    itr->second.second.emplace_back(component);
    itr->second.first.TurnOnBit((unsigned int)l_component);

    // notifying the system manager
    //m_systems->EntityModified(l_entity,itr->second->first);

    return true;
}

bool EntityManager::RemoveComponent(const EntityId& l_entity, const Component& l_component)
{
    auto itr = m_entities.find(l_entity);
    if(itr == m_entities.end()) return false;

    if(!itr->second.first.GetBit((unsigned int)l_component)) return false;
    // entity doesnt have the component

    auto& container = itr->second.second;
    auto component = std::find_if(container.begin(),container.end(),
    [&l_component](C_Base* C)
    {
        return C->GetType() == l_component;
    });

    if(component == container.end())return false;

    delete (*component);
    container.erase(component);

    itr->second.first.ClearBit((unsigned int)l_component);

    //m_systems->EntityModified(l_entity,itr->second.first);

    return true;
}

bool EntityManager::HasComponent(const EntityId& l_entity,const Component& l_component)
{
    auto itr = m_entities.find(l_entity);
    if(itr == m_entities.end()) return false;

    return (itr->second.first.GetBit((unsigned)l_component));
}

void EntityManager::Purge()
{
    //m_systems->PurgeEntities();

    for(auto& entity : m_entities)
    {
        for(auto& component : entity.second.second) delete component;
        entity.second.second.clear();
        entity.second.first.Clear();
    }
    m_entities.clear();
    m_idCounter = 0;
}


int EntityManager::AddEntity(const std::string& l_entityFile)
{
    int entityId = -1;

    std::ifstream file;
    file.open(l_entityFile);

    if(!file.is_open())
    {
        std::cout << "Cannot open: " << l_entityFile << std::endl; 
        return -1;
    }

    std::string line;
    while(getline(file,line))
    {
        if(line[0] == '|')continue;

        std::stringstream keystream(line);
        std::string type;

        if(type == "NAME")
        {}
        else if(type == "ATTRIBUTES")
        {
            if(entityId != -1) continue;
            Bitset set = 0;
            Bitmask mask;

            keystream >> set;
            mask.SetMask(set);
            entityId = AddEntity(mask);
            if(entityId == -1)return -1;
        }
        else if( type == "COMPONENT")
        {
            if(entityId == -1) continue;
            
            unsigned int c_id = 0;
            keystream >> c_id;
            
            C_Base* component = GetComponent<C_Base>(entityId,(Component)c_id);

            if(!component) continue;

            keystream >> *component;

            if(component->GetType() == Component::SpriteSheet)
            {
                //C_SpriteSheet* sheet = (C_SpriteSheet*)component;
                //sheet->Create(m_textureManager);
            }
        }
    }

    file.close();
    return entityId;
}