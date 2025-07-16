#include "game_state.hpp"

State_Game::State_Game(StateManager* l_stateManager):BaseState(l_stateManager){}

void State_Game::OnCreate()
{

    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    evmgr->AddCallback(StateType::Game,"Key_Escape",&State_Game::MainMenu,this);
    evmgr->AddCallback(StateType::Game,"Key_Pause",&State_Game::MainMenu,this);
    evmgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);

    sf::Vector2u size = m_stateManager->GetContext()->m_wind->GetWindowSize();
    m_view.setSize(size.x,size.y);
    m_view.setCenter(size.x/2,size.y/2);
    m_view.zoom(0.6f);
    m_stateManager->GetContext()->m_wind->GetRenderWindow()->setView(m_view);

    m_gameMap = new Map(m_stateManager->GetContext(),this);
    m_gameMap->LoadMap("resources/media/Maps/test_map.map");
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
    // sf::Vector2u l_windowSize = m_stateManager->GetContext()->m_wind->GetWindowSize();
    // sf::Vector2u l_textureSize = m_texture.getSize();

    // if((m_sprite.getPosition().x > l_windowSize.x - l_textureSize.x && m_increment.x > 0) ||
    // (m_sprite.getPosition().x < 0 && m_increment.x < 0))
    // {
    //     m_increment.x = -m_increment.x;
    // }
    // if((m_sprite.getPosition().y > l_windowSize.y - l_textureSize.y && m_increment.y > 0) ||
    // (m_sprite.getPosition().y < 0 && m_increment.y < 0))
    // {
    //     m_increment.y = -m_increment.y;
    // }
    // m_sprite.setPosition(m_sprite.getPosition().x + (m_increment.x * l_time.asSeconds()), 
    // m_sprite.getPosition().y + (m_increment.y * l_time.asSeconds()));

    SharedContext* context = m_stateManager->GetContext();
    EntityBase* player = context->m_entityManager->Find("Player");
    if(!player)
    {
        std::cout << "Respwaning Player... " << std::endl;
        context->m_entityManager->Add(EntityType::Player,"Player");
        player = context->m_entityManager->Find("Player");
        player->SetPosition(m_gameMap->GetPlayerStart());
    }
    else
    {
        m_view.setCenter(player->GetPosition());
        context->m_wind->GetRenderWindow()->setView(m_view);
    }


    sf::FloatRect viewSpace = context->m_wind->GetViewSpace();
    if(viewSpace.left <= 0)
    {
        m_view.setCenter(viewSpace.width / 2,m_view.getCenter().y);
        context->m_wind->GetRenderWindow()->setView(m_view);
    }
    else if (viewSpace.left + viewSpace.width >
    (m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size)
    {
        m_view.setCenter(((m_gameMap->GetMapSize().x + 1) *
        Sheet::Tile_Size) - (viewSpace.width / 2),
        m_view.getCenter().y);
        context->m_wind->GetRenderWindow()->setView(m_view);
    }
    m_gameMap->Update(l_time.asSeconds());
    m_stateManager->GetContext()->
    m_entityManager->Update(l_time.asSeconds());
}

void State_Game::Draw()
{
    m_gameMap->Draw();
    m_stateManager->GetContext()->m_entityManager->Draw();
    //m_stateManager->GetContext()->m_wind->GetRenderWindow()->draw(m_sprite);
}

void State_Game::MainMenu(EventDetails* l_details)
{m_stateManager->SwitchTo(StateType::MainMenu);}

void State_Game::Pause(EventDetails* l_details)
{m_stateManager->SwitchTo(StateType::Paused);}

