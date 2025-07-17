#include "game_state.hpp"
#include "../ECS/Core/system_manager.hpp"
#include "../ECS/Components/c_position.hpp"
#include "../ECS/entity_message.hpp"
#include "../direction.hpp"

State_Game::State_Game(StateManager* l_stateManager):BaseState(l_stateManager){}

void State_Game::OnCreate()
{

    EventManager* evMgr = m_stateManager->GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Game,"Key_Escape",&State_Game::MainMenu,this);
    evMgr->AddCallback(StateType::Game,"Key_Pause",&State_Game::MainMenu,this);
    evMgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);

    evMgr->AddCallback(StateType::Game, "Player_MoveLeft",&State_Game::PlayerMove, this);
    evMgr->AddCallback(StateType::Game, "Player_MoveRight",&State_Game::PlayerMove, this);
    evMgr->AddCallback(StateType::Game, "Player_MoveUp",&State_Game::PlayerMove, this);
    evMgr->AddCallback(StateType::Game, "Player_MoveDown",&State_Game::PlayerMove, this);

    sf::Vector2u size = m_stateManager->GetContext()->m_wind->GetWindowSize();
    m_view.setSize(size.x,size.y);
    m_view.setCenter(size.x/2,size.y/2);
    m_view.zoom(0.6f);
    m_stateManager->GetContext()->m_wind->GetRenderWindow()->setView(m_view);

    m_gameMap = new Map(m_stateManager->GetContext(),this);
    m_gameMap->LoadMap("resources/media/Maps/test_map.map");

    //m_playerId = m_gameMap->GetPlayerId();
}

void State_Game::OnDestroy()
{
    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    evmgr->RemoveCallback(StateType::Game,"Key_Escape");
    evmgr->RemoveCallback(StateType::Game,"Key_Pause");
    evmgr->RemoveCallback(StateType::Game,"Key_P");
    
    delete m_gameMap;
    m_gameMap = nullptr;
}

void State_Game::Update(const sf::Time& l_time)
{
 
    // sf::FloatRect viewSpace = context->m_wind->GetViewSpace();
    // if(viewSpace.left <= 0)
    // {
    //     m_view.setCenter(viewSpace.width / 2,m_view.getCenter().y);
    //     context->m_wind->GetRenderWindow()->setView(m_view);
    // }
    // else if (viewSpace.left + viewSpace.width >
    // (m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size)
    // {
    //     m_view.setCenter(((m_gameMap->GetMapSize().x + 1) *
    //     Sheet::Tile_Size) - (viewSpace.width / 2),
    //     m_view.getCenter().y);
    //     context->m_wind->GetRenderWindow()->setView(m_view);
    // }
    // m_gameMap->Update(l_time.asSeconds());
    // m_stateManager->GetContext()->
    // m_entityManager->Update(l_time.asSeconds());

    SharedContext* context = m_stateManager->GetContext();
    //UpdateCamera();
    m_gameMap->Update(l_time.asSeconds());
    context->m_systemManager->Update(l_time.asSeconds());
}

void State_Game::UpdateCamera()
{
    if(m_playerId == -1)
    {
        return;
    }

    SharedContext* context = m_stateManager->GetContext();
    C_Position* c_pos = context->m_entityManager->GetComponent<C_Position>(m_playerId,Component::Position);

    sf::Vector2f viewCenter = c_pos->GetPosition();
    sf::Vector2f viewSize  = m_view.getSize();
    // now we start to set up view
    if(viewCenter.x - viewSize.x/2 <= 0)
    {
        viewCenter.x = viewSize.x/2;
    }
    else if(viewCenter.x + viewSize.x/2 > m_gameMap->GetMapSize().x*Sheet::Tile_Size)
    {
        viewCenter.x = m_gameMap->GetMapSize().x*Sheet::Tile_Size - viewSize.x/2;
    }
    if(viewCenter.y - viewSize.y/2 <= 0)
    {
        viewCenter.y = viewSize.y/2;
    }
    else if(viewCenter.y+ viewSize.y/2 > m_gameMap->GetMapSize().y*Sheet::Tile_Size)
    {
        viewCenter.y = m_gameMap->GetMapSize().y*Sheet::Tile_Size - viewSize.y/2;
    }

    m_view.setCenter(viewCenter);
    context->m_wind->GetRenderWindow()->setView(m_view);
    
}

void State_Game::Draw()
{
    //m_gameMap->Draw();
    //m_stateManager->GetContext()->m_entityManager->Draw();

    // for(unsigned int i = 0;i < Sheet::Num_Layers; ++i)
    // {
    //     m_gameMap->Draw(i);
    //     m_stateManager->GetContext()->m_systemManager->Draw(
    //         m_stateManager->GetContext()->m_wind,i
    //     );
    // }
}

void State_Game::MainMenu(EventDetails* l_details)
{m_stateManager->SwitchTo(StateType::MainMenu);}

void State_Game::Pause(EventDetails* l_details)
{m_stateManager->SwitchTo(StateType::Paused);}

void State_Game::PlayerMove(EventDetails* l_details)
{
    Message msg((MessageType)EntityMessage::Move);

    if(l_details->m_name == "Player_MoveLeft")
    {
        msg.m_int = (int)Direction::Left;
    }
    else if(l_details->m_name == "Player_MoveRight")
    {
        msg.m_int = (int)Direction::Right;
    }
    else if(l_details->m_name == "Player_MoveUp")
    {
        msg.m_int = (int)Direction::Up;
    }   
    else if(l_details->m_name == "Player_MoveDown")
    {
        msg.m_int = (int)Direction::Down;
    }

    msg.m_receiver = m_playerId;
    m_stateManager->GetContext()->m_systemManager->GetMessageHandler()->Dispatch(msg);
}