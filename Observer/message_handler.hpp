#pragma once
#include <unordered_map>
#include "communicator.hpp"
#include "../ECS/entity_message.hpp"
using Subscriptions = std::unordered_map<EntityMessage,Communicator>;


class MessageHandler
{
    public:
        bool Subscribe(const EntityMessage& l_type,Observer* l_observer)
        {
            return m_communicators[l_type].AddObserver(l_observer);
        }

        bool Unsubscribe(const EntityMessage& l_type, Observer* l_observer)
        {
            return m_communicators[l_type].RemoveObserver(l_observer);
        }   

        void Dispatch(const Message& l_message)
        {
            auto itr = m_communicators.find((EntityMessage)l_message.m_type);

            if(itr == m_communicators.end()) return;

            itr->second.BroadCast(l_message);
        }


    private:
        Subscriptions m_communicators;
};