#pragma once
#include "Window_System/window.hpp"
#include "State_System/state_manager.hpp"
class Game
{
    public:
        Game();
        ~Game();
 
        //void HadleInput();
        void Update();
        void Render();

        sf::Time GetElapsed();
        void RestartClock();

        Window* GetWindow();
        //void MoveLogo(EventDetails* l_details);

        void LastUpdate();

    private:
        //void MoveLogo();
        Window m_window;
        SharedContext m_context;
        std::unique_ptr<StateManager> m_stateManager;
        //sf::Texture m_logoTexture;
        //sf::Vector2u m_size;
        //sf::Sprite m_logo;
        //sf::Vector2f m_increment;
        
        sf::Clock m_clock;
        sf::Time m_elapsed;
};