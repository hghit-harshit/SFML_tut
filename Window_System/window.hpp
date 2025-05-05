#pragma once
#include <SFML/Graphics.hpp> 
#include "../Event_System/event_manager.hpp"
// ill tyr using the hungarian notation in this project

class Window
{
    public:
        Window();
        Window(const std::string& title, const sf::Vector2u& size);
        ~Window();

        void BeginDraw(); // clear window
        void EndDraw(); // display changesi

        void Update();

        bool IsDone();
        bool IsFullscreen();
        sf::Vector2u GetWindowSize();
        sf::RenderWindow* GetRenderWindow();
        //void ToggleFullscreen();

        void Draw(sf::Drawable& drawable);

        bool IsFocused();
        EventManager* GetEventManager();
        void ToggleFullscreen(EventDetails* l_details);
        void Close(EventDetails* l_details = nullptr);
        sf::FloatRect GetViewSpace();
    private:
        void Setup(const std::string& title, const sf::Vector2u& size);
        void Destroy();
        void Create();
        
        sf::RenderWindow m_window;
        sf::Vector2u m_windowSize;
        std::string m_windowTitle;
        bool m_isDone;
        bool m_isFullscreen;

        EventManager m_eventManager;
        bool m_isFocused;   

};