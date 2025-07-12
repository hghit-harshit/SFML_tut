#pragma once


#include "state_manager.hpp"
#include <iostream>
#include "../Resource_System/texture_manager.hpp"

class State_Intro : public BaseState
{
    public:
        State_Intro(StateManager* l_stateManager);
        void OnCreate() override;
        void OnDestroy() override;
        
        void Activate() override{};
        void Deactivate() override{};

        void Update(const sf::Time& l_time) override;
        void Draw() override;

        void Continue(EventDetails* l_detais);
    private:    
        sf::Texture m_introTexture;
        sf::Sprite m_introSprite;
        sf::Text m_text;
        sf::Font m_font;
        float m_timePassed;

        
};

// do i want to have declaration and implementaion in the same file ??
//fuck it we ball 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

State_Intro::State_Intro(StateManager* l_stateManager): BaseState(l_stateManager)
{}

void State_Intro::OnCreate()
{
    // std::cout << "It gets inside on create\n";
    // m_timePassed = 0.0f;
    // auto context = m_stateManager->GetContext();
    // if (context == nullptr) std::cout << " the context is null\n";
    // //if (context->m_wind == nullptr)std::cout << "The window is null\n";
    // sf::Vector2u windowSize = m_stateManager->
    // GetContext()->m_wind->GetWindowSize();
    // // why the fuck is it retuning a null pointer though investigate the hell out of it!!!
    // //sf::Vector2u windowSize{ 800,600 };
    // // GetRenderWindow is returning null pointer

    // if (!m_introTexture.loadFromFile("resources/logo.png"))
    // {
    //     std::cout << "Could not load texture file!\n";
    // }
    // else std::cout << "Loads texture\n";
    // m_introSprite.setTexture(m_introTexture);

    // m_introSprite.setOrigin(m_introTexture.getSize().x/2.0f,
    // m_introTexture.getSize().y/2.0f);

    // m_introSprite.setPosition(windowSize.x/2.0f,0);

    // if (!m_font.loadFromFile("arial.ttf")) 
    // {
    //     std::cout << "Could not load font file!\n";
    // }
    // m_text.setFont(m_font);
    // m_text.setString("Hello World");
    // m_text.setCharacterSize(15);
    // sf::FloatRect textRect = m_text.getLocalBounds();
    // m_text.setOrigin(textRect.left + textRect.width / 2.0f, 
    // textRect.top + textRect.height/2.0f);
    
    // std::cout << "This gets to the end\n";
    // m_stateManager->GetContext()->m_eventManager->
    // AddCallback(StateType::Intro,"Intro_Continue",&State_Intro::Continue,this);

    sf::Vector2u windSize = m_stateManager->GetContext()->m_wind->GetRenderWindow()->getSize();

    TextureManager* textureMgr = m_stateManager->GetContext()->m_textureManager;
    textureMgr->RequireResource("Intro");
    
    m_introSprite.setTexture(*textureMgr->GetResource("Intro"));
    m_introSprite.setOrigin(textureMgr->GetResource("Intro")->getSize().x/2.0f,
    textureMgr->GetResource("Intro")->getSize().y/2.0f);
    m_introSprite.setPosition(windSize.x/2.0f,windSize.y/2.0f);

    m_font.loadFromFile("resources/arial.ttf");
    m_text.setFont(m_font);
    m_text.setString(sf::String("Press Space To Continue."));
    m_text.setCharacterSize(15);
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    m_text.setPosition(m_introSprite.getPosition().x, 
	m_introSprite.getPosition().y + textureMgr->GetResource("Intro")->getSize().y / 1.5f);

    m_stateManager->GetContext()->m_eventManager->
    AddCallback(StateType::Intro,"Intro_Continue",&State_Intro::Continue,this);
}

void State_Intro::OnDestroy()
{
    TextureManager* textureMgr = m_stateManager->GetContext()->m_textureManager;
    textureMgr->ReleaseResource("Intro");
    EventManager* evmgr = m_stateManager->GetContext()->m_eventManager;
    // ye krna jaruri h kya cant we just call the callback method in one line lik
    //m_stateManager->GetContext()->m_eventManager->RemoveCallback();
    evmgr->RemoveCallback(StateType::Intro,"Intro_Continue");
}

void State_Intro::Update(const sf::Time& l_time)
{}

void State_Intro::Draw()
{
    sf::RenderWindow* window = m_stateManager->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_introSprite);
    
    window->draw(m_text);
    
}

void State_Intro::Continue(EventDetails* l_details)
{
    
    m_stateManager->SwitchTo(StateType::MainMenu);
    m_stateManager->Remove(StateType::Intro);
    
}