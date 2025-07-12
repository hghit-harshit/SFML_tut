#pragma once
#include "base_state.hpp"
#include "state_type.hpp"
#include "../Window_System/window.hpp"
#include "../Event_System/event_manager.hpp"
#include <functional>
#include <vector>
#include "../shared_context.hpp"

//container for states
using StateContainer = std::vector<std::pair<StateType,BaseState*>>;
using TypeContainer = std::vector<StateType>;
// pair of type and the fucntion that outputs the object of the state type
using StateFactory = std::unordered_map<StateType,std::function<BaseState*(void)>>;

//class BaseState;
class State_Intro;
class State_MainMenu;
class State_Game;
class State_Paused;

class StateManager
{
    public:
        StateManager(SharedContext* l_shared);
        ~StateManager();

        void Update(const sf::Time& l_time);
        void Draw();

        void ProcessRequest();

        SharedContext* GetContext();
        bool HasState(const StateType& l_type);

        void SwitchTo(const StateType& l_type);
        void Remove(const StateType& l_type);

    private:
        //methods
        void CreateState(const StateType& l_type);
        void RemoveState(const StateType& l_type);

        template <typename T>
        void RegisterState(const StateType& l_type)
        {
            m_stateFactory[l_type] = [this]()->BaseState*
            {return new T(this);};
        }

        //members
        SharedContext* m_shared;
        StateContainer m_states;
        TypeContainer m_toRemove;
        StateFactory m_stateFactory;
};