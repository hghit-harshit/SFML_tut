#pragma once
#include "Window_System/window.hpp"
#include "State_System/state_manager.hpp"
#include "shared_context.hpp"
#include "Resource_System/texture_manager.hpp"
//#include "Entity_Component_System/entity_manager.hpp"
#include "ECS/Core/entity_manager.hpp"
#include "ECS/Core/system_manager.hpp"
class Game
{
    public:
        Game();
        ~Game();
 
        void Update();
        void Render();
        sf::Time GetElapsed();
        void RestartClock();
        Window* GetWindow();
        void LastUpdate();

    private:
        //void MoveLogo();
        Window m_window;
        SharedContext m_context;
        EntityManager m_entityManager;
        SystemManager m_systemManager;
        StateManager m_stateManager;
        TextureManager m_textureManager;
        sf::Clock m_clock;
        sf::Time m_elapsed;
};