#include "game.hpp"
#include <iostream>
#include <exception>
#include <memory>
Game::Game():
m_window("My Game",sf::Vector2u(800,600))
{
    // if(!m_logoTexture.loadFromFile("resources/logo.png")) 
    // {
    //     std::cout << "Could not load the texture\n";
    // }
    // m_size = m_logoTexture.getSize();
    // m_logo.setTexture(m_logoTexture);
    // m_increment = sf::Vector2f(200,200);  
    m_context.m_wind = &m_window;
    //if (m_stateManager.GetContext()->m_wind.GetRenderWindow() == nullptr)std::cout << "Buggg\n";
    m_context.m_eventManager = m_window.GetEventManager();
    m_context.m_textureManager = new TextureManager();
    if (m_context.m_wind == nullptr)std::cout << "bug yhin nikslega!\n";
    m_stateManager = std::make_unique<StateManager>(&m_context);
    m_stateManager->SwitchTo(StateType::Intro);

    /*m_window.GetEventManager()->AddCallback("Move",&Game::MoveLogo,this);
    m_window.GetEventManager()->AddCallback("FullScreen_toggle", &Window::ToggleFullscreen, &m_window);*/
}

Game::~Game(){}

void Game::Update()
{ 
    m_window.Update();
    m_stateManager->Update(m_elapsed);
   //MoveLogo();
} 


// void Game::MoveLogo(EventDetails* l_details)
// {
//     sf::Vector2i mousepos = m_window.GetEventManager()->GetMousePosition(m_window.GetRenderWindow());
//     //m_logo.setPosition(mousepos.x,mousepos.y);
// }


//void Game::MoveLogo()
//{
//    sf::Vector2u l_windSize = m_window.GetWindowSize();
//    sf::Vector2u l_textSize = m_logoTexture.getSize();
//
//    if((m_logo.getPosition().x > l_windSize.x - m_size.x && m_increment.x > 0)
//    ||(m_logo.getPosition().x < 0 && m_increment.x < 0))
//    {
//        m_increment.x  = -m_increment.x;
//    }
//    if((m_logo.getPosition().y > l_windSize.y - m_size.y && m_increment.y > 0)
//    ||(m_logo.getPosition().y < 0 && m_increment.y < 0))
//    {
//        m_increment.y  = -m_increment.y;
//    }
//
//    float secondsElapsed = m_elapsed.asSeconds();
//    m_logo.move(m_increment.x*secondsElapsed,m_increment.y*secondsElapsed);
//
//}

void Game::Render()
{
    m_window.BeginDraw();
    //m_window.Draw(m_logo);
    m_stateManager->Draw();
    m_window.EndDraw();
}

void Game::LastUpdate()
{
    m_stateManager->ProcessRequest();
    RestartClock();
}

Window* Game::GetWindow()
{
    return &m_window;
}

sf::Time Game::GetElapsed(){return m_elapsed;}

void Game::RestartClock(){m_elapsed = m_clock.restart();}
