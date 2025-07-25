#include "s_renderer.hpp"
#include "../Core/system_manager.hpp"
#include "../Components/c_position.hpp"
#include "../Components/c_drawable.hpp"
#include "../Components/c_spritesheet.hpp"

S_Renderer::S_Renderer(SystemManager* l_systemManager)
:S_Base(System::Renderer,l_systemManager)
{
    Bitmask requirements;
    requirements.TurnOnBit((unsigned int)Component::Position);
    requirements.TurnOnBit((unsigned int)Component::SpriteSheet);
    m_requiredComponents.push_back(requirements);
    requirements.Clear();

    // we subscrite to direction changed event
    // meaning well be notified every time there is a direction changed event
    m_systemManager->GetMessageHandler()->Subscribe(EntityMessage::Direction_Changed,this);
}

S_Renderer::~S_Renderer(){}

void S_Renderer::Update(float l_dt)
{
    EntityManager* entities = m_systemManager->GetEntityManager();
    for(auto& entity : m_entities) // m_entities is just a list of entities
    {
        C_Position* position = entities->GetComponent<C_Position>(entity,Component::Position);
        C_Drawable* drawable = nullptr;

        if(entities->HasComponent(entity,Component::SpriteSheet))
        {
            drawable = entities->GetComponent<C_Drawable>(entity,Component::SpriteSheet);
        }else continue;

        drawable->UpdatePosition(position->GetPosition());
    }
}

void S_Renderer::HandleEvent(const EntityId& l_entity,const EntityEvent& l_event)
{
    if(l_event == EntityEvent::Moving_Up ||
    l_event == EntityEvent::Moving_Down ||
    l_event == EntityEvent::Moving_Left ||
    l_event == EntityEvent::Moving_Right)
    {
        SortDrawables();
        // changing their position or 
        // elevation, their drawable representations have to be re-sorted in order to assure the 
        // correct layering. 
    }
}

void S_Renderer::Notify(const Message& l_message)
{
    if(HasEntity(l_message.m_receiver))
    {
        EntityMessage message = (EntityMessage)l_message.m_type;
        switch(message)
        {
            case EntityMessage::Direction_Changed:
            {
                SetSheetDirection(l_message.m_receiver,(Direction)l_message.m_int);
                break;
            }
            // made switch for expandability
        }
    }
}

void S_Renderer::Render(Window* l_wind, unsigned int l_layer)
{
    EntityManager* entities = m_systemManager->GetEntityManager();
    for(auto entity : m_entities)
    {
        C_Position* position = entities->GetComponent<C_Position>(entity,Component::Position);
        if(position->GetElevation() < l_layer)continue;
        if(position->GetElevation() > l_layer) break;

        C_Drawable*  drawable =nullptr;

        if(!entities->HasComponent(entity,Component::SpriteSheet))
        {
            continue; // why are we checking this
        }

        drawable = entities->GetComponent<C_Drawable>(entity,Component::SpriteSheet);
        sf::FloatRect drawableBounds;
        drawableBounds.left  = position->GetPosition().x -(drawable->GetSize().x/2);
        drawableBounds.top   = position->GetPosition().y -(drawable->GetSize().y/2);

        drawableBounds.width = drawable->GetSize().x;
        drawableBounds.height = drawable->GetSize().y;

        if(!l_wind->GetViewSpace().intersects(drawableBounds))
        {
            continue;// out of the viewspace
        }

        drawable->Draw(l_wind->GetRenderWindow());
    }
}

void S_Renderer::SetSheetDirection(const EntityId& l_entity, const Direction& l_dir)
{
    EntityManager* entities = m_systemManager->GetEntityManager();
    if(!entities->HasComponent(l_entity,Component::SpriteSheet))
    {
        return;
    }

    C_SpriteSheet* sheet = entities->GetComponent<C_SpriteSheet>(l_entity,Component::SpriteSheet);
    sheet->GetSpriteSheet()->SetDirection(l_dir);
}

void S_Renderer::SortDrawables()
{
    EntityManager* entities = m_systemManager->GetEntityManager();

    std::sort(m_entities.begin(),m_entities.end(),
    [entities](unsigned int l_1, unsigned int l_2)
    {
        auto pos1 = entities->GetComponent<C_Position>(l_1,Component::Position);
        auto pos2 = entities->GetComponent<C_Position>(l_2,Component::Position);

        if(pos1->GetElevation() == pos2->GetElevation())
        {
            return pos1->GetPosition().y < pos2->GetPosition().y;
        }
        return pos1->GetElevation() < pos2->GetElevation();
    });
}