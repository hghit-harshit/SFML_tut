#pragma once
#include <queue>

using EventId = unsigned int;

class EventQueue
{
    public:
        void AddEvent(const EventId& l_event){m_queue.push(l_event);}

        bool ProcessEvents(EventId& l_id)
        {
            if(m_queue.empty()) return false;

            l_id = m_queue.front();
            m_queue.pop();
            return true;
        }

        void Clear()
        {
            while(!m_queue.empty())m_queue.pop();
        }
    private:
        std::queue<EventId> m_queue;
};