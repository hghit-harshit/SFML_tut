#include "player.hpp"
#include "entity_manager.hpp"
#include "../State_system/state_type.hpp"

Player::Player(EntityManager* l_entityMgr)
:Character(l_entityMgr)
{
    Load("resources/media/Characters/Player.char");
    m_type = EntityType::Player;

    EventManager* events = m_entityManager->GetContext()->m_eventManager;
    events->AddCallback<Player>(StateType::Game,
    "Player_MoveLeft",&Player::React,this); 
    events->AddCallback<Player>(StateType::Game,
    "Player_MoveRight",&Player::React,this);
    events->AddCallback<Player>(StateType::Game,
    "Player_Jump",&Player::React,this);
}

Player::~Player()
{
    EventManager* events = m_entityManager->GetContext()->m_eventManager;
    // events->RemoveCallback(GAME,"Player_MoveLeft");
    // events->RemoveCallback(GAME,"Player_MoveRight");
    // events->RemoveCallback(GAME,"Player_Jump");
}

void Player::React(EventDetails* l_details)
{
    if (l_details->m_name == "Player_MoveLeft")
    {
	    Character::Move(Direction::Left);
    } else if (l_details->m_name == "Player_MoveRight")
    {
	    Character::Move(Direction::Right);
    } else if (l_details->m_name == "Player_Jump")
    {
        Character::Jump();
    } else if (l_details->m_name == "Player_Attack")
    {
        Character::Attack();
    }
}

void Player::OnEntityCollision(EntityBase* l_collider,bool l_attack){}

