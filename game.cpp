#include "game.hpp"
#include <iostream>
#include <exception>
#include <memory>
Game::Game():
m_window("My Game",sf::Vector2u(1200,600)),m_stateManager(&m_context),
m_entityManager(&m_context,100)
{
    std::cout << "Gets here\n";
    m_context.m_wind = &m_window;
    m_context.m_eventManager = m_window.GetEventManager();
    m_context.m_textureManager = new TextureManager();
    m_context.m_entityManager = &m_entityManager;
    m_stateManager.SwitchTo(StateType::Intro);
    
}

Game::~Game(){}

void Game::Update()
{ 
    m_window.Update();
    m_stateManager.Update(m_elapsed);
} 

void Game::Render()
{
    m_window.BeginDraw();
    //m_window.Draw(m_logo);
    m_stateManager.Draw();
    m_window.EndDraw();
}

void Game::LastUpdate()
{
    m_stateManager.ProcessRequest();
    RestartClock();
}

Window* Game::GetWindow()
{
    return &m_window;
}

sf::Time Game::GetElapsed(){return m_elapsed;}

void Game::RestartClock(){m_elapsed = m_clock.restart();}
