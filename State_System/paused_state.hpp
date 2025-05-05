#pragma once
#include "state_manager.hpp"

class State_Paused : public BaseState
{   
    public:
        State_Paused(StateManager* l_stateManager);
        void OnCreate() override;
        void OnDestroy() override;
        
        void Activate() override {};
        void Deactivate() override{};

        void Update(const sf::Time& l_time) override {};
        void Draw() override;

        void Unpuase(EventDetails* l_details);
    private:
        sf::Font m_font;
        sf::Text m_text;
        sf::RectangleShape m_rect;


};

////////////////////////////////////////////////////////////////////////////////////////

State_Paused::State_Paused(StateManager* l_stateManager) : BaseState(l_stateManager) {}

void State_Paused::OnCreate()
{
    SetTransparent(true);
    m_font.loadFromFile("tuffy.ttf");
    m_text.setFont(m_font);
    m_text.setString(sf::String("Paused"));
    m_text.setCharacterSize(14);
    m_text.setStyle(sf::Text::Bold);

    sf::Vector2u windSize = m_stateManager->GetContext()->m_wind->GetRenderWindow()->getSize();
    
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, 
      textRect.top + textRect.height / 2.0f);
    m_text.setPosition(windSize.x / 2.0f, windSize.y / 2.0f);

    m_rect.setSize(sf::Vector2f(windSize));
    m_rect.setPosition(0,0);
    m_rect.setFillColor(sf::Color(0,0,0,150));

    m_stateManager->GetContext()->m_eventManager->
    AddCallback(StateType::Paused,"Key_P",&State_Paused::Unpuase,this);
}

void State_Paused::Unpuase(EventDetails* l_details)
{
    m_stateManager->SwitchTo(StateType::Game);
}

void State_Paused::OnDestroy()
{
    m_stateManager->GetContext()->m_eventManager->RemoveCallback(StateType::Paused,"Key_P");
}

void State_Paused::Draw()
{
    sf::RenderWindow* wind = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    wind->draw(m_text);
    wind->draw(m_rect);
}