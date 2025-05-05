#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>

enum class EventType
{
    KeyDown       = sf::Event::KeyPressed,
    KeyUp         = sf::Event::KeyReleased,
    MButtonDown   = sf::Event::MouseButtonPressed,
    MButtonUp     = sf::Event::MouseButtonReleased,
    MouseWheel    = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus   = sf::Event::GainedFocus,
    LostFocus     = sf::Event::LostFocus,
    MouseEntered  = sf::Event::MouseEntered,
    MouseLeft     = sf::Event::MouseLeft,
    Closed        = sf::Event::Closed,
    TextEntered   = sf::Event::TextEntered,
    Keyboard      = sf::Event::Count + 1,Mouse,Joystick

    // We're setting up our own event, called Keyboard to 
    // the value of sf::Event::Count + 1. Because all the enumerations are essentially 
    // keywords pointing to integer values, the last row prevents any kind of identifier 
    // clashing and makes sure that anything added past this point is higher than the 
    // absolute maximum sf::Event::EventType enumeration value
};

struct EventInfo
{
    EventInfo(){m_code = 0;}
    EventInfo(int l_event){m_code = l_event;}

    union 
    {
        int m_code; 
        // In order to leave room for expansions, we're already 
        // using a union to store the event 
        // code.
    };
};

using Events = std::vector<std::pair<EventType,EventInfo>>;

struct EventDetails
{
   EventDetails(const std::string& l_bindName)
   :m_name(l_bindName)
   {Clear();}

    std::string m_name;

    sf::Vector2i m_size;
    sf::Uint32 m_textEntered;
    sf::Vector2i m_mouse;
    int m_mouseWheelDelta;
    int m_keyCode; // key code of a key

    void Clear()
    {
        m_size =sf::Vector2i(0,0);
        m_textEntered = 0;
        m_mouse = sf::Vector2i(0,0);
        m_mouseWheelDelta = 0;
        m_keyCode = -1;

    }
};


struct Binding
{
    Binding(const std::string& l_name)
    :m_name (l_name),m_details(l_name),c(0){}

    void BindEvent(EventType l_type, EventInfo l_info = EventInfo())
    {
        m_event.emplace_back(l_type,l_info);
    }

    Events m_event;
    std::string m_name;
    int c; // keep track of event that are happening

    EventDetails m_details;
};

using Bindings = std::unordered_map<std::string,Binding*>;

using CallbackContainer = std::unordered_map<std::string,std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager
{
    public:
        EventManager();
        ~EventManager();

        bool AddBinding(Binding* l_binding);
        bool RemoveBinding(const std::string& l_name);

        void SetFocus(const bool& l_focus);

        template <typename T>
        bool AddCallback(StateType l_type,const std::string& l_name,
        void(T::*l_func)(EventDetails*),T* l_instance)
        {
            auto itr = m_callbacks.emplace(l_type,CallbackContainer()).first;
            auto temp = std::bind(l_func,l_instance,std::placeholders::_1);
            //place holder will be replaced by an argument in the future
            std::cout << "Callback " << l_name << " Added\n";
            return itr->second.emplace(l_name,temp).second;
        }

        bool RemoveCallback(StateType l_type,const std::string& l_name)
        {
            auto itr1 =  m_callbacks.find(l_type);
            if(itr1 == m_callbacks.end()){return false;}
            auto itr2 = itr1->second.find(l_name);
            if(itr2 == itr1->second.end()){return false;}
            itr1->second.erase(l_name);
            return true;
        }

        void HandleEvent(sf::Event& l_event); // check event
        void Update();
        // update method, which can handle 
        // real-time input checking as well as the validating
        // and resetting of the states of the 
        // bindings.
        sf::Vector2i GetMousePosition(sf::RenderWindow* l_window = nullptr)
        {
            return (l_window ? sf::Mouse::getPosition(*l_window) : sf::Mouse::getPosition());

        }
        void SetCurrentState(StateType l_type){m_currentState = l_type;}
    private:
        void LoadBindings();

        Bindings m_bindings;
        Callbacks m_callbacks;
        bool m_hasFocus;
        StateType m_currentState;
        // for GetMousePositione to determine wether the 
        //window is in focus or not
};