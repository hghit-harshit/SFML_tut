#include"state_manager.hpp"
#include "intro_state.hpp"
#include "main_menu_state.hpp"
#include "game_state.hpp"
#include "paused_state.hpp"
#include <iostream>

StateManager::StateManager(SharedContext* l_shared):m_shared(l_shared)
{
    RegisterState<State_Intro>(StateType::Intro);
    CreateState(StateType::Intro);
    RegisterState<State_MainMenu>(StateType::MainMenu);
    CreateState(StateType::MainMenu);
    RegisterState<State_Game>(StateType::Game);
    RegisterState<State_Paused>(StateType::Paused);
    //CreateState(StateType::Game);
}

StateManager::~StateManager()
{
    for(auto &itr : m_states)
    {
       itr.second->OnDestroy();
       delete itr.second; 
    }
}

void StateManager::Draw()
{
    if(m_states.empty()){return;}
    if(m_states.back().second->IsTransparent() && m_states.size() > 1)
    {
        // now we see from back how deep the transparency runs and get itr upto that
        auto itr = m_states.end() - 1;
        while(itr != m_states.begin()) //i have changed code in this part to agar hage to ye check kr
        {
            if(!itr->second->IsTransparent())
            {break;}
            --itr;
        }
        for(;itr != m_states.end();++itr)
        {
            m_shared->m_wind->GetRenderWindow()->setView(itr->second->GetView());
            itr->second->Draw();
        }
    }
    else
    {
        m_states.back().second->Draw();
    }
}

void StateManager::Update (const sf::Time& l_time)
{
    if(m_states.empty()){return;/*std::cout << "Its empty\n";*/}
    if(m_states.back().second->IsTranscendent() && m_states.size()>1)
    {
        // now we do same digging as draw function
        auto itr = m_states.end()-1;
        while(itr != m_states.begin())
        {
            if(!itr->second->IsTranscendent()){break;}
            --itr;
        }
        for(;itr != m_states.end(); ++itr)
        {
            itr->second->Update(l_time);
        }
    }
    else
    {m_states.back().second->Update(l_time);}
}

SharedContext* StateManager::GetContext(){return m_shared;}

bool StateManager::HasState(const StateType& l_type)
{
    for(auto itr = m_states.begin(); itr != m_states.end(); ++itr)
    {
        if(itr->first == l_type)
        {
            // chekcing if the l_state is about to be removed
            auto removed = std::find(m_toRemove.begin(), m_toRemove.end(),l_type);
            if(removed == m_toRemove.end()){return true;}
            return false;
        }
    }
    return false;
}

void StateManager::Remove(const StateType& l_type)
{
    m_toRemove.push_back(l_type);
}
// now the removal is processed by the following function

void StateManager::ProcessRequest()
{
    while(m_toRemove.begin() != m_toRemove.end()) // maybe we can do !m_toRemove.empty()
    {
        RemoveState(*m_toRemove.begin());
        m_toRemove.erase(m_toRemove.begin());
    }
}

void StateManager::SwitchTo(const StateType& l_type)
{
    //std::cout << "It gets inside switch to!!!!\n";
    if(l_type == StateType::MainMenu)std::cout << "its main menu my mann\n";
    m_shared->m_eventManager->SetCurrentState(l_type);
    for(auto itr = m_states.begin(); itr != m_states.end(); ++itr)
    {
        if(itr->first == l_type)
        {
            m_states.back().second->Deactivate();
            StateType tmp_type = itr->first;
            BaseState* tmp_state = itr->second;
            m_states.erase(itr);
            m_states.emplace_back(tmp_type,tmp_state);
            tmp_state->Activate();
            m_shared->m_wind->GetRenderWindow()->setView(tmp_state->GetView());
            return;
        }
    }
    // but if we dont find the state
    if(!m_states.empty()){m_states.back().second->Deactivate();}
    CreateState(l_type);
    if (m_states.empty()) { return; }
    m_states.back().second->Activate(); // maybe this is the one causing trouble
    m_shared->m_wind->GetRenderWindow()->setView(m_states.back().second->GetView());
}

void StateManager::CreateState(const StateType& l_type)
{
    auto newState = m_stateFactory.find(l_type);
    //std::cout << "This is not creating any states\n";
    if(newState == m_stateFactory.end()){return;}
    //std::cout << "Its getting inside state create\n";
    BaseState* state = newState->second();
    state->m_view = m_shared->m_wind->GetRenderWindow()->getDefaultView();
    m_states.emplace_back(l_type,state);
    state->OnCreate();
}

void StateManager::RemoveState(const StateType& l_type)
{
    for(auto itr = m_states.end(); itr != m_states.end(); ++itr)
    {
        if(itr->first == l_type)
        {
            itr->second->OnDestroy();
            delete itr->second;
            m_states.erase(itr);
            return;
        }
    }
}


