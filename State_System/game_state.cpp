#include "game_state.hpp"

State_Game::State_Game(StateManager* l_stateManager):BaseState(l_stateManager){}

void State_Game::OnCreate()
{
    m_texture.loadFromFile("resources/logo.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(0,0);
    m_increment= sf::Vector2f(200.0f,200.0f);

    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    evmgr->AddCallback(StateType::Game,"Key_Escape",&State_Game::MainMenu,this);
    evmgr->AddCallback(StateType::Game,"Key_Pause",&State_Game::MainMenu,this);
    evmgr->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
}

void State_Game::OnDestroy()
{
    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    evmgr->RemoveCallback(StateType::Game,"Key_Escape");
    evmgr->RemoveCallback(StateType::Game,"Key_Pause");
}

void State_Game::Update(const sf::Time& l_time)
{
    sf::Vector2u l_windowSize = m_stateManager->GetContext()->m_wind->GetWindowSize();
    sf::Vector2u l_textureSize = m_texture.getSize();

    if((m_sprite.getPosition().x > l_windowSize.x - l_textureSize.x && m_increment.x > 0) ||
    (m_sprite.getPosition().x < 0 && m_increment.x < 0))
    {
        m_increment.x = -m_increment.x;
    }
    if((m_sprite.getPosition().y > l_windowSize.y - l_textureSize.y && m_increment.y > 0) ||
    (m_sprite.getPosition().y < 0 && m_increment.y < 0))
    {
        m_increment.y = -m_increment.y;
    }
    m_sprite.setPosition(m_sprite.getPosition().x + (m_increment.x * l_time.asSeconds()), 
    m_sprite.getPosition().y + (m_increment.y * l_time.asSeconds()));
}

void State_Game::Draw()
{
    m_stateManager->GetContext()->m_wind->GetRenderWindow()->draw(m_sprite);
}

void State_Game::MainMenu(EventDetails* l_details)
{m_stateManager->SwitchTo(StateType::MainMenu);}

void State_Game::Pause(EventDetails* l_details)
{m_stateManager->SwitchTo(StateType::Paused);}

