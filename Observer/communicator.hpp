#pragma once
#include "observer.hpp"
#include<algorithm>
#include <vector>


using ObserverContainer = std::vector<Observer*>;

class Communicator
{
    public:
        ~Communicator(){ m_observers.clear();}

        bool AddObserver(Observer* l_observer)
        {
            if(HasObserver(l_observer))return false;
            m_observers.emplace_back(l_observer);
            return true;
        }

        bool RemoveObserver(Observer* l_observer)
        {
            auto observer = std::find_if(m_observers.begin(),m_observers.end(),
            [&l_observer](Observer* o)
            {return o == l_observer;}); // do we need find if???

            if(observer == m_observers.end()) return false;

            m_observers.erase(observer);
            return true;
        }

        bool HasObserver(const Observer* l_observer)
        {
            return std::find_if(m_observers.begin(),m_observers.end(),
            [&l_observer](Observer* o)
            {return o == l_observer;}) != m_observers.end();
        }

        void BroadCast(const Message& l_message)
        {
            for(auto& itr : m_observers)itr->Notify(l_message);
        }


    private:
        ObserverContainer m_observers;
};